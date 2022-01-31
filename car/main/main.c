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

#include "../../config/mario_kart_config.h"

static xQueueHandle s_recv_queue;


void print_packet(packet_t packet){
	// packet_t* packet = (packet_t*)incomingData;
	printf(packet.up ? "up " : "   |");
	printf(packet.down ? "down " : "     |");
	printf(packet.left ? "left " : "     |");
	printf(packet.right ? "right " : "      \n");
}

static void queue_process_task(void *p)
{
    packet_t recv_packet;

    ESP_LOGI("Car", "Listening");
    for(;;)
    {
        if(xQueueReceive(s_recv_queue, &recv_packet, portMAX_DELAY))
        {
            print_packet(recv_packet);
        }
        
    }
}

void recv_cb(const uint8_t * mac_addr, const uint8_t *data, int len) {
	static packet_t recv_packet;

	ESP_LOGI("Car", "%d bytes incoming from " MACSTR, len, MAC2STR(mac_addr));

	if(len != sizeof(packet_t)){
		ESP_LOGE("Car", "Unexpected packet size");
		return;
	}

    memcpy(&recv_packet, data, len);
    if (xQueueSend(s_recv_queue, &recv_packet, 0) != pdTRUE) {
        ESP_LOGW("Car", "Queue full, discarded");
        return;
    }

}

static void initialize_esp_now_car(void){
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
	ESP_ERROR_CHECK(esp_now_set_pmk((uint8_t*)CONFIG_ESPNOW_PMK)); // maybe dont need it since we're not encrypting packets

	// const esp_now_peer_info_t dest_peer = {
	// 	.peer_addr = CAR_MAC_ADDR,
	// 	.channel = 1,
	// 	.ifidx = ESP_IF_WIFI_STA
	// };
	// ESP_ERROR_CHECK(esp_now_add_peer(&dest_peer));
}

void tag_handler(uint8_t* serial_no){
	gpio_set_level(5, 1);
	for(int i = 0; i < 5; i++)
		printf("%#x ", serial_no[i]);

	printf("\n");
	gpio_set_level(5, 0);
}

void app_main(void) {
	const rc522_start_args_t start_args = {
		.miso_io = 25,
		.mosi_io = 23,
		.sck_io = 19,
		.sda_io = 22,
		.callback = &tag_handler
	};

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

	s_recv_queue = xQueueCreate(10, sizeof(packet_t));
	initialize_esp_now_car();

	xTaskCreate(queue_process_task, "Receive_from_controller", 2048, NULL, 2, NULL);
}