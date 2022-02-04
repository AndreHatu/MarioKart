#include "rc522.h"
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
#include "mario_kart_config.h"

#include "../../config/mario_kart_config.h"

static xQueueHandle s_recv_queue;
static xQueueHandle modifier_queue;


void print_packet(packet_t packet){
	// packet_t* packet = (packet_t*)incomingData;

}


static void queue_process_task_send(void *p) // sending modifier to car
	while(1)
	{
		//if there are one or more data packets in the queue, send it to the car.
		if (xQueueReceive(modifier_queue, &packet_modifier, portMAX_DELAY)){
			esp_now_send(CAR_MAC_ADDR, (uint8_t*)packet);
		}
		//else yield to receive queue
		else{
			taskYIELD();
		}
	}
}

//receive data from car (NFC tag information)
static void queue_process_task(void *p)
{
    static packet_tag recv_packet;

    ESP_LOGI("Tower", "Listening");
    for(;;)
    {
        if(xQueueReceive(s_recv_queue, &recv_packet, portMAX_DELAY))
        {
            print_packet(recv_packet);
        }
        
    }
}

void recv_cb(const uint8_t * mac_addr, const uint8_t *data, int len) {
	static packet_tag recv_packet;

	ESP_LOGI("Tower", "%d bytes incoming from " MACSTR, len, MAC2STR(mac_addr));

	if(len != sizeof(packet_tag)){
		ESP_LOGE("Tower", "Unexpected packet size");
		return;
	}

    memcpy(&recv_packet, data, len);
    if (xQueueSend(s_recv_queue, &recv_packet, 0) != pdTRUE) {
        ESP_LOGW("Tower", "Queue full, discarded");
        return;
    }


}

//send data process:: from Tower to Car
static void send_info(void* args){
	if((err = esp_now_send(DEST_MAC, (uint8_t*)packet, sizeof(packet_modifier))) != ESP_OK){
			printf("Error sending packet: %x\n", err);
	}
	vTaskDelay(5000 / portTICK_PERIOD_MS);
}


void packet_sent_cb(const uint8_t* mac_addr, esp_now_send_status_t status){
	if(mac_addr==NULL){
		ESP_LOGE("Controller", "Send cb mac error");
		return;
	}
	printf(status==ESP_NOW_SEND_SUCCESS ? "ESP NOW Success\n" : status==ESP_NOW_SEND_FAIL ? "ESP NOW Fail\n" : "Unknown error occurred when sending packet\n");
	xEventGroupSetBits(s_evt_group, BIT(status));
}


//Initialize esp32 to enable send and receive
static void initialize_esp_now_tower(void){
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
	ESP_ERROR_CHECK(esp_now_register_recv_cb(recv_cb));
	ESP_ERROR_CHECK(esp_now_register_send_cb(packet_sent_cb));
	ESP_ERROR_CHECK(esp_now_set_pmk((uint8_t*)CONFIG_ESPNOW_PMK)); // maybe dont need it since we're not encrypting packets

	const esp_now_peer_info_t dest_peer = {
		.peer_addr = Car_MAC_ADDR,
		.channel = 2,
		.ifidx = ESP_IF_WIFI_STA
	};
	ESP_ERROR_CHECK(esp_now_add_peer(&dest_peer));
}

void modifier_handler(uint8_t* tag_ID){
	gpio_set_level(5, 1);
	for(int i = 0; i < 5; i++)
		printf("%#x ", tag_ID[i]);

	printf("\n");
	gpio_set_level(5, 0);

	packet_modifier* packet = malloc(sizeof(packet_modifier));
	esp_err_t err;
	const uint8_t DEST_MAC[] = CAR_MAC_ADDR;
	
	memcpy(packet->modifier, tag_ID, sizeof(uint8_t)*5); // read data from tag reader module
	xQueueSend(modifier_queue,&packet_modifier, portMAX_DELAY);
}

void app_main(void) {

	const gpio_config_t pin_config = {
		.pin_bit_mask = (1ULL << 5) | (1ULL << 10) | (1ULL << 18),
		.mode = GPIO_MODE_INPUT,
		.intr_type = GPIO_INTR_DISABLE,
		.pull_down_en = 0,
		.pull_up_en = 1
	};

	gpio_config(&pin_config);

	gpio_set_level(18, 1);
	rc522_start(start_args);

	s_recv_queue = xQueueCreate(10, sizeof(packet_tag));
	initialize_esp_now_tower();

	xTaskCreate(queue_process_task, "Receive_from_car", 2048, NULL, 1, NULL);
	xTaskCreate(send_info, "Send_info_to_car", 2048, NULL, 2, NULL);
}