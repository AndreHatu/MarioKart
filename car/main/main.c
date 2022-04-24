#include "rc522.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
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

#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"
#include "esp_attr.h"
#include "soc/rtc.h"
#include "pwm.h"

// NOTE: change accordingly
#define TOWER TOWER_MAC_ADDR
#define CONTROLLER CONTROLLER1_MAC_ADDR
#define ANOTHER_CAR	CAR2_MAC_ADDR
#define MY_CAR CAR1_MAC_ADDR
#define MOTOR_PIN_BW 14   // in3
#define MOTOR_PIN_FW 27   // in4
#define MOTOR_PIN_LEFT 33  // in2
#define MOTOR_PIN_RIGHT 25 // in1
//#define MOD 15 // in1

static xQueueHandle ctrl_recv_q;
static xQueueHandle tag_q;
static xQueueHandle tower_recv_q;
static xQueueHandle mod_q;
static xQueueHandle active_mod_q;
static bool mod_flag;
static bool rev;

int start_time;
int current_time;

int64_t millis() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + (tv.tv_usec / 1000LL));
}

void print_packet(controls_packet packet, bool rev){
	// printf(packet.left ? "left |" : "     |");
	// printf(packet.right ? "right |" : "      |");
	// printf(packet.up ? "up |" : "   |");
	// printf(packet.down ? "down \n" : "     \n");
	// printf(packet.mod ? "mod \n" : "     \n");
	if (!rev){
		gpio_set_level(MOTOR_PIN_FW, packet.up);
		gpio_set_level(MOTOR_PIN_BW, packet.down);
		gpio_set_level(MOTOR_PIN_LEFT, packet.left);
		gpio_set_level(MOTOR_PIN_RIGHT, packet.right);
	}
	else{	
		gpio_set_level(MOTOR_PIN_FW, packet.down);
		gpio_set_level(MOTOR_PIN_BW, packet.up);
		gpio_set_level(MOTOR_PIN_LEFT, packet.right);
		gpio_set_level(MOTOR_PIN_RIGHT, packet.left);
	}	
}


static void tag_queue_send_task(void *p) // sending rfid tag info to central tower
{
	tag_packet packet;// = malloc(sizeof(tag_packet));
	const uint8_t DEST_MAC[] = TOWER; // TOWER_MAC_ADDR, changed for testing
	esp_err_t err;
	while(1)
	{
		ESP_LOGI("Car", "Trying to send packet to tower");
		if (xQueueReceive(tag_q, &packet, portMAX_DELAY) == pdTRUE){
			ESP_LOGI("Car", "Sending packet to tower");
			if((err = esp_now_send(DEST_MAC, (uint8_t*)&packet, sizeof(tag_packet))) != ESP_OK){
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
	rev = 0;
    ESP_LOGI("Car", "Listening_to_controls");
    for(;;){
		// ESP_LOGI("Car", "Trying to process controls packet");
        if(xQueueReceive(ctrl_recv_q, &recv_packet, portMAX_DELAY) == pdTRUE) {
			print_packet(recv_packet,rev);
			if (mod_flag){
				current_time = millis();
				if (current_time - start_time >= 3000){
					printf("Back to normal state\n");
					//printf("start time %d current time %d", start_time, current_time);
					brushed_motor_a(MCPWM_UNIT_0, MCPWM_TIMER_0, V0);
					mod_flag = 0;
					rev = 0;
				}
			}

			// User click modifier button
			else if (recv_packet.mod == true){
				printf("mod = 1\n");
				modifier_packet mod_pack;// = malloc(sizeof(modifier_packet));
				used_mod_packet used_mod;
				esp_err_t err;

				if (xQueueReceive(mod_q, &mod_pack, 0) == pdTRUE){
					printf("have something in mod queue\n");
					used_mod.modifier = mod_pack.modifier;
					const uint8_t TOWER_MAC[MAC_LEN] = TOWER_MAC_ADDR;
					if((err = esp_now_send(TOWER_MAC, (uint8_t*)&used_mod, sizeof(used_mod_packet))) != ESP_OK){
						ESP_LOGE("Car", "Error sending packet to tower");
						printf("Error: %x\n", err);
					}
					if (mod_pack.modifier == 0){
						start_time = millis();
						//current_time = start_time;
						printf("modifier: power up\n");
						brushed_motor_a(MCPWM_UNIT_0, MCPWM_TIMER_0, VSPEED);
						mod_flag = 1;
					}
					else 
					{
						//printf("modifier: something else\n");

						active_mod_packet act_pack;// = malloc(sizeof(active_mod_packet));
						act_pack.modifier = mod_pack.modifier;
						const uint8_t DEST_MAC[MAC_LEN] = ANOTHER_CAR;
						if((err = esp_now_send(DEST_MAC, (uint8_t*)&act_pack, sizeof(active_mod_packet))) != ESP_OK){
							ESP_LOGE("Car", "Error sending packet to tower");
							printf("Error: %x\n", err);
						}
						start_time = millis();
						mod_flag = 1;
					}
				}
				else{
					ESP_LOGI("car", "No Modifier Available");
				}
			}
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
			printf("Received modifier: %02x\n", recv_packet.modifier);
			xQueueSend(mod_q, &recv_packet, 0);
        }  
		else{
			taskYIELD();
		}   

    }
}

//activate the modifier!
static void active_mod_queue_process_task(void *p)
{
	active_mod_packet active_packet;
	ESP_LOGI("Car", "Activate the Modifier");
	for(;;)
    {
		ESP_LOGI("Car", "Active modifier");
        if(xQueueReceive(active_mod_q, &active_packet, portMAX_DELAY) == pdTRUE)
        {
            // print_packet(recv_packet);
			printf("Received Active modifier: %02x\n", active_packet.modifier);
			if (active_packet.modifier == 1){
				start_time = millis();
				//current_time = start_time;
				printf("modifier: power down\n");
				brushed_motor_a(MCPWM_UNIT_0, MCPWM_TIMER_0, VSLOW);
				mod_flag = 1;
			}

			else if (active_packet.modifier == 2){
				start_time = millis();
				//current_time = start_time;
				printf("modifier: reverse control\n");
				rev = 1;
				mod_flag = 1;
			}
						
			else if (active_packet.modifier == 3){
				start_time = millis()-2000;
				//current_time = start_time;
				printf("modifier: stop control\n");
				brushed_motor_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
				mod_flag = 1;
			}
        }  
		else{
			taskYIELD();
		}   

    }
}


void recv_cb(const uint8_t * mac_addr, const uint8_t *data, int len) {

	//ESP_LOGI("Car", "%d bytes incoming from " MACSTR, len, MAC2STR(mac_addr));

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
	else if (len == sizeof(active_mod_packet)){
		static active_mod_packet recv_packet;
		printf("recved activ mod: %02x\n", recv_packet.modifier);
		memcpy(&recv_packet, data, len);
		if (xQueueSend(active_mod_q, &recv_packet, 0) != pdTRUE) {
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
	const esp_now_peer_info_t dest_peer1 = {
		.peer_addr = TOWER,
		.channel = 1,
		.ifidx = ESP_IF_WIFI_STA
	};
	
	const esp_now_peer_info_t dest_peer2 = {
		.peer_addr = ANOTHER_CAR, // another car
		.channel = 1,
		.ifidx = ESP_IF_WIFI_STA
	};

	const esp_now_peer_info_t dest_peer3 = {
		.peer_addr = CONTROLLER, // my controller
		.channel = 1,
		.ifidx = ESP_IF_WIFI_STA
	};

	ESP_ERROR_CHECK(esp_now_add_peer(&dest_peer1));
	ESP_ERROR_CHECK(esp_now_add_peer(&dest_peer2));
	ESP_ERROR_CHECK(esp_now_add_peer(&dest_peer3));
}

void tag_handler(uint8_t* serial_no){
	gpio_set_level(5, 1);
	for(int i = 0; i < 5; i++)
		printf("%#x ", serial_no[i]);

	printf("\n");
	gpio_set_level(5, 0);

	//time when car run over tag

	int64_t time_us = millis();

	tag_packet packet;// = malloc(sizeof(tag_packet));
	const uint8_t SRC_MAC[MAC_LEN] = MY_CAR;  // NOTE: must make it so we can choose car/ctrl 1 and 2
	memcpy(&(packet.src_mac), SRC_MAC, MAC_LEN);
	memcpy(&(packet.tag_id), serial_no, TAG_LEN); // read data from tag reader module

	printf("packet with soruce addr and tag id and time %lld\n", time_us);
	//memcpy(packet->lap_time, &time_us, sizeof(struct timeval));
	packet.lap_time = time_us;
	xQueueSend(tag_q, &packet, portMAX_DELAY);
}




void app_main(void) {
	mod_flag =0;
	const rc522_start_args_t start_args = {
		.miso_io = 16,
		.mosi_io = 4,
		.sck_io = 18,
		.sda_io = 15,
		.callback = &tag_handler
	};
	// ESP_ERROR_CHECK(rc522_start(start_args));
	rc522_start(start_args);

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
 	mod_q = xQueueCreate(10, sizeof(modifier_packet));
	active_mod_q = xQueueCreate(10, sizeof(active_mod_packet));

	initialize_esp_now_car();
	mcpwm_example_gpio_initialize();

	xTaskCreate(ctrl_queue_process_task, "Receive_from_controller", 2048, NULL, 1, NULL);
	xTaskCreate(tag_queue_send_task, "Send_info_to_Tower", 2048, NULL, 3, NULL);
	xTaskCreate(tower_queue_process_task, "Receive_from_tower", 2048, NULL, 3, NULL);
	xTaskCreate(active_mod_queue_process_task, "Receive active modifier", 2048, NULL, 3, NULL);
	//xTaskCreate(test_comm_task, "Send_info_to_Tower", 2048, NULL, 2, NULL);
	//xTaskCreate(mcpwm_example_config, "mcpwm_example_config", 4096, NULL, 5, NULL);
	// xTaskCreate(print_outputs, "Print_GPIO_outputs", 2048, NULL, 1, NULL);
	//xTaskCreate(activate_mod, "activate_mod", 2048, NULL, 5, NULL);
}