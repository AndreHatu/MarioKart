#include "rc522.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
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

// NOTE: change accordingly
#define TOWER CONTROLLER2_MAC_ADDR
#define MOTOR_PIN_BW 12   // in3
#define MOTOR_PIN_FW 13   // in4
#define MOTOR_PIN_LEFT 4  // in2
#define MOTOR_PIN_RIGHT 9 // in1


static xQueueHandle ctrl_recv_q;
static xQueueHandle tag_q;
static xQueueHandle tower_recv_q;


void print_packet(controls_packet packet){
	// printf(packet.left ? "left |" : "     |");
	// printf(packet.right ? "right |" : "      |");
	// printf(packet.up ? "up |" : "   |");
	// printf(packet.down ? "down \n" : "     \n");
	gpio_set_level(MOTOR_PIN_FW, packet.up);
	gpio_set_level(MOTOR_PIN_BW, packet.down);
	gpio_set_level(MOTOR_PIN_LEFT, packet.left);
	gpio_set_level(MOTOR_PIN_RIGHT, packet.right);
}

static void tag_queue_send_task(void *p) // sending rfid tag info to central tower
{
	tag_packet* packet = malloc(sizeof(tag_packet));
	const uint8_t DEST_MAC[] = TOWER; // TOWER_MAC_ADDR, changed for testing
	esp_err_t err;
	while(1)
	{
		ESP_LOGI("Car", "Trying to send packet to tower");
		if (xQueueReceive(tag_q, packet, portMAX_DELAY) == pdTRUE){
			ESP_LOGI("Car", "Sending packet to tower");
			if((err = esp_now_send(DEST_MAC, (uint8_t*)packet, sizeof(tag_packet))) != ESP_OK){
				ESP_LOGE("Car", "Error sending packet to tower");
				printf("Error: %x\n", err);
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
		// ESP_LOGI("Car", "Trying to process controls packet");
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
		ESP_LOGI("Car", "Trying to process modifier packet");
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
		.peer_addr = TOWER,
		.channel = 1,
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

	//time when car run voer tag
	struct timeval tv_now;
	gettimeofday(&tv_now, NULL);
	int64_t time_us = (int64_t)tv_now.tv_sec * 1000000L + (int64_t)tv_now.tv_usec;

	tag_packet* packet = malloc(sizeof(tag_packet));
	const uint8_t SRC_MAC[] = CAR1_MAC_ADDR;  // NOTE: must make it so we can choose car/ctrl 1 and 2
	memcpy(packet->src_mac, SRC_MAC, MAC_LEN);
	memcpy(packet->tag_id, serial_no, TAG_LEN); // read data from tag reader module
	memcpy(packet->tag_id + TAG_LEN, '\0', 1); // read data from tag reader module
	memcpy(packet->lap_time, time_us, sizeof(int64_t));
	xQueueSend(tag_q, packet, portMAX_DELAY);
	free(packet);
}

// static void test_comm_task(void* p){
// 	static uint8_t i = 0;
// 	static tag_packet packet;
// 	for(;;){
// 		// tag_packet *packet = malloc(sizeof(tag_packet));
// 		packet.tag_id[0] = i;
// 		i++;
// 		xQueueSend(tag_q, &packet, portMAX_DELAY);
// 		vTaskDelay(35*portTICK_PERIOD_MS);
// 	}
// }

// void print_outputs(void* p){
// 	// bool alternate = true;
// 	for(;;){
// 		printf("Pin 12: %d, Pin 13: %d, Pin 4: %d, Pin 5: %d\n", gpio_get_level(MOTOR_PIN_FW),  gpio_get_level(MOTOR_PIN_BW),  gpio_get_level(MOTOR_PIN_LEFT),  gpio_get_level(MOTOR_PIN_RIGHT));
// 		// gpio_set_level(alternate ? MOTOR_PIN_BW : MOTOR_PIN_FW, 1);
// 		// gpio_set_level(alternate ? MOTOR_PIN_FW : MOTOR_PIN_BW, 0);
// 		// alternate = !alternate;
// 		vTaskDelay(500 / portTICK_PERIOD_MS);
// 	}
// }

void app_main(void) {

	const rc522_start_args_t start_args = {
		.miso_io = 25,
		.mosi_io = 23,
		.sck_io = 19,
		.sda_io = 22,
		.callback = &tag_handler
	};
	ESP_ERROR_CHECK(rc522_start(start_args));

	const gpio_config_t pin_config1 = {
		.pin_bit_mask = ((1ULL << MOTOR_PIN_BW) | (1ULL << MOTOR_PIN_FW) | (1ULL << MOTOR_PIN_LEFT) | (1ULL << MOTOR_PIN_RIGHT)),
		.mode = GPIO_MODE_OUTPUT, //GPIO_MODE_INPUTOUTPUT, // for debugging output pins
		.intr_type = GPIO_INTR_DISABLE,
		.pull_down_en = 0,
		.pull_up_en = 0
	};
	ESP_ERROR_CHECK(gpio_config(&pin_config1));

	ctrl_recv_q = xQueueCreate(20, sizeof(controls_packet));
	tag_q = xQueueCreate(10, sizeof(tag_packet));
	tower_recv_q = xQueueCreate(10, sizeof(modifier_packet));

	initialize_esp_now_car();

	xTaskCreate(ctrl_queue_process_task, "Receive_from_controller", 2048, NULL, 1, NULL);
	xTaskCreate(tag_queue_send_task, "Send_info_to_Tower", 2048, NULL, 3, NULL);
	xTaskCreate(tower_queue_process_task, "Receive_from_controller", 2048, NULL, 3, NULL);
	// xTaskCreate(test_comm_task, "Send_info_to_Tower", 2048, NULL, 2, NULL);
	// xTaskCreate(print_outputs, "Print_GPIO_outputs", 2048, NULL, 1, NULL);
}