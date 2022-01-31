#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_now.h"
#include "esp_system.h"
#include "esp_sleep.h"

#include "../../config/mario_kart_config.h"

//BIG BRDB:   3c:61:05:7d:e0:88
//SMALL BRDB: 3c:61:05:7d:dd:a4

#define GPIO_INPUT_0 26
#define GPIO_INPUT_1 33
#define GPIO_INPUT_2 23
#define GPIO_INPUT_3 22
#define GPIO_INPUT_PIN_SELECT ((1ULL<<GPIO_INPUT_0)|(1ULL<<GPIO_INPUT_1)|(1ULL<<GPIO_INPUT_2)|(1ULL<<GPIO_INPUT_3))

// static xQueueHandle gpio_event_q = NULL;
static EventGroupHandle_t s_evt_group;

// static void gpio_event(void* args){
// 	for(;;){
// 		printf("up: %d, down: %d, left: %d, right: %d\n", gpio_get_level(GPIO_INPUT_0), gpio_get_level(GPIO_INPUT_1), gpio_get_level(GPIO_INPUT_2), gpio_get_level(GPIO_INPUT_3));
// 	}
// }

void package_data(packet_t* packet){
	packet->up = (bool)gpio_get_level(GPIO_INPUT_0);
	packet->down = (bool)gpio_get_level(GPIO_INPUT_1);
	packet->left = (bool)gpio_get_level(GPIO_INPUT_2);
	packet->right = (bool)gpio_get_level(GPIO_INPUT_3);
}

static void send_info(void* args){
	packet_t* packet = malloc(sizeof(packet_t));
	esp_err_t err;
	const uint8_t DEST_MAC[] = CAR_MAC_ADDR;
	for(;;){
		package_data(packet);
		if((err = esp_now_send(DEST_MAC, (uint8_t*)packet, sizeof(packet_t))) != ESP_OK){
			printf("Error sending packet: %x\n", err);
		}
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		// EventBits_t bits = xEventGroupWaitBits(s_evt_group, BIT(ESP_NOW_SEND_SUCCESS) | BIT(ESP_NOW_SEND_FAIL), pdTRUE, pdFALSE, 2000 / portTICK_PERIOD_MS);
		// if(!(bits & BIT(ESP_NOW_SEND_SUCCESS))){
		// 	if(bits & BIT(ESP_NOW_SEND_FAIL)){
		// 		ESP_LOGE("Controller", "Send Error");
		// 		break;
		// 	}
		// }
	}
}

void packet_sent_cb(const uint8_t* mac_addr, esp_now_send_status_t status){
	if(mac_addr==NULL){
		ESP_LOGE("Controller", "Send cb mac error");
		return;
	}
	printf(status==ESP_NOW_SEND_SUCCESS ? "ESP NOW Success\n" : status==ESP_NOW_SEND_FAIL ? "ESP NOW Fail\n" : "Unknown error occurred when sending packet\n");
	xEventGroupSetBits(s_evt_group, BIT(status));
}

static void initialize_esp_now_controller(void){
	// init NVS (storage) for wifi
	esp_err_t ret = nvs_flash_init();
	if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND){
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	ESP_ERROR_CHECK(esp_netif_init());
	ESP_ERROR_CHECK(esp_event_loop_create_default());  // check what this is for
	const wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));  // set it to station and access point
	ESP_ERROR_CHECK(esp_wifi_start());


	ESP_ERROR_CHECK(esp_now_init());
	ESP_ERROR_CHECK(esp_now_register_send_cb(packet_sent_cb));
	ESP_ERROR_CHECK(esp_now_set_pmk((uint8_t*)CONFIG_ESPNOW_PMK)); // maybe dont need it since we're not encrypting packets

	const esp_now_peer_info_t dest_peer = {
		.peer_addr = CAR_MAC_ADDR,
		.channel = 1,
		.ifidx = ESP_IF_WIFI_STA
	};
	ESP_ERROR_CHECK(esp_now_add_peer(&dest_peer));
}

void app_main(void) {
	
	gpio_config_t io_conf;
	io_conf.intr_type = GPIO_INTR_DISABLE;//GPIO_INTR_POSEDGE;
	io_conf.pin_bit_mask = GPIO_INPUT_PIN_SELECT;
	io_conf.mode = GPIO_MODE_INPUT;
	io_conf.pull_down_en = 1;
	io_conf.pull_up_en = 0;
	gpio_config(&io_conf);

	// gpio_event_q = xQueueCreate(10, sizeof(uint32_t));
	// xTaskCreate(gpio_event, "gpio_event", 1000, NULL, 10, NULL);
	// ERROR: missing configuration for init functions
	
	initialize_esp_now_controller();
	s_evt_group = xEventGroupCreate();
	xTaskCreate(send_info, "Send_info_from_controller", 2048, NULL, 1, NULL);
}