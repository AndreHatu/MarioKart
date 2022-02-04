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

static xQueueHandle ctrl_recv_q;
static xQueueHandle tag_q;
static xQueueHandle tower_recv_q;


void print_packet(controls_packet packet){
	printf(packet.left ? "left |" : "     |");
	printf(packet.right ? "right |" : "      |");
	printf(packet.up ? "up |" : "   |");
	printf(packet.down ? "down \n" : "     \n");
}

//send data to tower process
// static void send_info(void* args){
// 	if((err = esp_now_send(DEST_MAC, (uint8_t*)packet, sizeof(packet_tag))) != ESP_OK){
// 			printf("Error sending packet: %x\n", err);
// 	}
// 	vTaskDelay(5000 / portTICK_PERIOD_MS);
// }

static void queue_send_task(void *p) // sending rfid tag info to central tower
{
	tag_packet* packet = NULL;
	const uint8_t DEST_MAC[] = TOWER_MAC_ADDR;
	while(1)
	{
		if (xQueueReceive(tag_q, packet, portMAX_DELAY) == pdTRUE){
			if(esp_now_send(DEST_MAC, (uint8_t*)packet, sizeof(tag_packet)) != ESP_OK){
				ESP_LOGE("Car", "Error sending packet to tower\n");
			}
		}
		else{
			taskYIELD();
		}
	}
}

// receive controls process
static void ctrl_queue_process_task(void *p)
{
    controls_packet recv_packet;
    ESP_LOGI("Car", "Listening_to_controls");
    for(;;)
    {
        if(xQueueReceive(ctrl_recv_q, &recv_packet, portMAX_DELAY) == pdTRUE)
        {
            print_packet(recv_packet);
        }        
    }
}

// receive modifiers process
static void tower_queue_process_task(void *p)
{
    modifier_packet recv_packet;
    ESP_LOGI("Car", "Listening_to_modifiers");
    for(;;)
    {
        if(xQueueReceive(tower_recv_q, &recv_packet, portMAX_DELAY) == pdTRUE)
        {
            // print_packet(recv_packet);
			printf("Received modifier\n");
        }        
    }
}

void recv_cb(const uint8_t * mac_addr, const uint8_t *data, int len) {

	ESP_LOGI("Car", "%d bytes incoming from " MACSTR, len, MAC2STR(mac_addr));

	if(len == sizeof(controls_packet)){
		static controls_packet recv_packet;
		memcpy(&recv_packet, data, len);
		if (xQueueSend(ctrl_recv_q, &recv_packet, 0) != pdTRUE) {
			ESP_LOGW("Car", "Controls Queue full, discarded");
			return;
		}
	}
	else if (len == sizeof(modifier_packet)){
		static modifier_packet recv_packet;
		memcpy(&recv_packet, data, len);
		if (xQueueSend(tower_recv_q, &recv_packet, 0) != pdTRUE) {
			ESP_LOGW("Car", "Modifiers Queue full, discarded");
			return;
		}
	}
	else{
		ESP_LOGE("Car", "Unrecognized packet size");
		return;
	}
}

void packet_sent_cb(const uint8_t* mac_addr, esp_now_send_status_t status){
	if(mac_addr==NULL){
		ESP_LOGE("Controller", "Send cb mac error");
		return;
	}
	printf(status==ESP_NOW_SEND_SUCCESS ? "ESP NOW Success\n" : status==ESP_NOW_SEND_FAIL ? "ESP NOW Fail\n" : "Unknown error occurred when sending packet\n");
	// xEventGroupSetBits(s_evt_group, BIT(status));
}

//Initialize esp32 to enable send and receive
static void initialize_esp_now_car(void){
	// init NVS (storage) for wifi
	esp_err_t ret = nvs_flash_init();
	if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND){
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	// init wifi
	ESP_ERROR_CHECK(esp_netif_init());
	ESP_ERROR_CHECK(esp_event_loop_create_default());  // check what this is for
	const wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));  // set it to station and access point
	ESP_ERROR_CHECK(esp_wifi_start());

	// init ESP-NOW
	ESP_ERROR_CHECK(esp_now_init());
	ESP_ERROR_CHECK(esp_now_register_recv_cb(recv_cb));
	ESP_ERROR_CHECK(esp_now_register_send_cb(packet_sent_cb));
	ESP_ERROR_CHECK(esp_now_set_pmk((uint8_t*)CONFIG_ESPNOW_PMK)); // maybe dont need it since we're not encrypting packets

	// add tower as peer
	const esp_now_peer_info_t dest_peer = {
		.peer_addr = TOWER_MAC_ADDR,
		.channel = 2,
		.ifidx = ESP_IF_WIFI_STA
	};
	ESP_ERROR_CHECK(esp_now_add_peer(&dest_peer));
}

void tag_handler(uint8_t* serial_no){
	gpio_set_level(5, 1);
	for(int i = 0; i < 5; i++)
		printf("%#x ", serial_no[i]);

	printf("\n");
	gpio_set_level(5, 0);

	//NOTE: CANNOT FORGET TO FREE PACKET AFTER POPPING FROM QUEUE
	tag_packet* packet = malloc(sizeof(tag_packet));
	// const uint8_t DEST_MAC[] = TOWER_MAC_ADDR;
	// const uint8_t SRC_MAC[] = CAR2_MAC_ADDR;  // NOTE: must make it so we can choose car/ctrl 1 and 2
	// memcpy(packet->dest_mac, DEST_MAC, MAC_LEN);
	// memcpy(packet->src_mac, SRC_MAC, MAC_LEN);
	memcpy(packet->tag_id, serial_no, TAG_LEN); // read data from tag reader module
	xQueueSend(tag_q, packet, portMAX_DELAY);
}

void app_main(void) {
	const rc522_start_args_t start_args = {
		.miso_io = 25,
		.mosi_io = 23,
		.sck_io = 19,
		.sda_io = 22,
		.callback = &tag_handler
	};

	// const gpio_config_t pin_config = {
	// 	.pin_bit_mask = (1ULL << 5) | (1ULL << 10) | (1ULL << 18),
	// 	.mode = GPIO_MODE_INPUT,
	// 	.intr_type = GPIO_INTR_DISABLE,
	// 	.pull_down_en = 0,
	// 	.pull_up_en = 1
	// };
	// gpio_config(&pin_config);
	// gpio_set_level(18, 1);
	ctrl_recv_q = xQueueCreate(10, sizeof(controls_packet));
	tag_q = xQueueCreate(10, sizeof(tag_packet));
	tower_recv_q = xQueueCreate(10, sizeof(modifier_packet));
	rc522_start(start_args);

	initialize_esp_now_car();

	xTaskCreate(ctrl_queue_process_task, "Receive_from_controller", 2048, NULL, 1, NULL);
	xTaskCreate(queue_send_task, "Send_info_to_Tower", 2048, NULL, 3, NULL);
	xTaskCreate(tower_queue_process_task, "Receive_from_controller", 2048, NULL, 3, NULL);
	// xTaskCreate(send_info, "Send_info_to_Tower", 2048, NULL, 2, NULL);
}