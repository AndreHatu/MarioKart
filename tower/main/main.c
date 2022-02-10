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
#include "strmap.h"

#include "../../config/mario_kart_config.h"

static xQueueHandle recv_q;
static xQueueHandle modifier_q;
StrMap *sm;
char value[255];


uint8_t random_modifier(){
	//0: power up
	//1: power down
	//2: reverse control
	//3: stop
	return (uint8_t) (esp_random() % 4);
}

// assign random modifier based on tag or mark checkpoint
void tag_handler(tag_packet packet){
	printf("Received tag packet: %02x %02x %02x %02x %02x \n", packet.tag_id[0], packet.tag_id[1], packet.tag_id[2], packet.tag_id[3], packet.tag_id[4]);
	Car_Status my_car;
	uint8_t other_car[MAC_LEN];
	if (packet->src_mac[0] == CAR1_MAC_ADDR[0]){
		memcpy(&other_car, CAR1_MAC_ADDR, MAC_LEN);
		mycar = CAR1;
	}
	else{
		memcpy(&other_car, CAR2_MAC_ADDR, MAC_LEN);	
		mycar = CAR2;	
	}
	int result = sm_get(sm, packet.tag_id, buf, sizeof(buf));
	if (result == 0){
		return;
	}
	switch (value[0]){ //need to setup hashmap
		case 'M':
			uint8_t mod = random_modifier(); // get random modifier
			//setup send packet
			modifier_packet* send_packet = malloc(sizeof(modifier_packet));
			send_packet->modifier = mod;

			//if powerup, send back to sender address, if not, send to the other car
			if (mod == 0){ // power up
				memcpy(&(send_packet->target_mac_addr), packet.src_mac, MAC_LEN);	
			}
			else{
				memcpy(&(send_packet->target_mac_addr), other_car, MAC_LEN);	
			}

			//add packet to queue
			if(xQueueSend(modifier_q, send_packet, portMAX_DELAY) != pdTRUE){
				ESP_LOGW("Tower", "Modifier Queue Full");
			}
			free(send_packet);
			
		case 'C':
			//figure out which car status to modify
			int val = value[1] - '0';
			if (val == (my_car.checkpoint%5)+1){
				uint8_t sender_car = packet.src_mac;
				my_car.lap_time += packet.lap_time;
				my_car.checkpoint = val;
			}
			//update lap status
	}

	
	// TODO: add all logic for either choosing and sending out modifiers or marking checkpoints

}

//receive data from car (NFC tag information)
static void queue_process_task(void *p)
{
    tag_packet* recv_packet = malloc(sizeof(tag_packet));

    ESP_LOGI("Tower", "Listening");
    for(;;)
    {
        if(xQueueReceive(recv_q, recv_packet, portMAX_DELAY) == pdTRUE)
        {
			tag_handler(*recv_packet);
        }
		else{
			taskYIELD();
		}
        
    }
}

void recv_cb(const uint8_t * mac_addr, const uint8_t *data, int len) {
	static tag_packet recv_packet;

	ESP_LOGI("Tower", "%d bytes incoming from " MACSTR, len, MAC2STR(mac_addr));

	if(len != sizeof(tag_packet)){
		ESP_LOGE("Tower", "Unexpected packet size");
		return;
	}

    memcpy(&recv_packet, data, len);
    if (xQueueSend(recv_q, &recv_packet, 0) != pdTRUE) {
        ESP_LOGW("Tower", "Recv Queue full, discarded");
        return;
    }

}

//send data process:: from Tower to Car
static void queue_send_task(void* args){
	// const uint8_t DEST_MAC1[] = CAR1_MAC_ADDR;
	// const uint8_t DEST_MAC2[] = CAR2_MAC_ADDR;
	modifier_packet* packet = malloc(sizeof(modifier_packet));

	for(;;){
		if (xQueueReceive(modifier_q, packet, portMAX_DELAY) == pdTRUE){
			// NOTE: need to add some switching logic to figure out if we send packet to either car or both
			if(esp_now_send(packet->target_mac_addr, (uint8_t*)packet, sizeof(modifier_packet)) != ESP_OK){
				// if dest_mac is NULL, packet is broadcast to all peers
				ESP_LOGE("Car", "Error sending packet to tower\n");
			}
			// if(esp_now_send(DEST_MAC2, (uint8_t*)packet, sizeof(modifier_packet)) != ESP_OK){
			// 	ESP_LOGE("Car", "Error sending packet to tower\n");
			// }
		}
		else{
			taskYIELD();
		}
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
static void initialize_esp_now_tower(void){
	// init NVS (storage) for wifi
	ESP_LOGI("Tower", "Initializing NVS");
	esp_err_t ret = nvs_flash_init();
	if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND){
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	// init wifi
	ESP_LOGI("Tower", "Initializing wifi");
	ESP_ERROR_CHECK(esp_netif_init());
	ESP_ERROR_CHECK(esp_event_loop_create_default());  // check what this is for
	const wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));  // set it to station and access point
	ESP_ERROR_CHECK(esp_wifi_start());

	// init ESP_NOW
	ESP_LOGI("Tower", "Initializing ESP-NOW");
	ESP_ERROR_CHECK(esp_now_init());
	ESP_ERROR_CHECK(esp_now_register_recv_cb(recv_cb));
	ESP_ERROR_CHECK(esp_now_register_send_cb(packet_sent_cb));
	ESP_ERROR_CHECK(esp_now_set_pmk((uint8_t*)CONFIG_ESPNOW_PMK)); // maybe dont need it since we're not encrypting packets

	// add cars as peers
	const esp_now_peer_info_t dest_peer1 = {
		.peer_addr = CAR1_MAC_ADDR,
		.channel = 1,
		.ifidx = ESP_IF_WIFI_STA
	};
	const esp_now_peer_info_t dest_peer2 = {
		.peer_addr = CAR2_MAC_ADDR,
		.channel = 1,
		.ifidx = ESP_IF_WIFI_STA
	};
	ESP_LOGI("Tower", "Adding peers");
	ESP_ERROR_CHECK(esp_now_add_peer(&dest_peer1));
	ESP_ERROR_CHECK(esp_now_add_peer(&dest_peer2));
}

void initialize_hash(){

	sm = sm_new(10);
	//save checkpoint
	sm_put(sm, "", "C0");
	sm_put(sm, "", "C1");
	sm_put(sm, "", "C2");
	sm_put(sm, "", "C3");
	sm_put(sm, "", "C4");
	//save modifier
	sm_put(sm, "", "M1");
	sm_put(sm, "", "M2");
	sm_put(sm, "", "M3");
	sm_put(sm, "", "M4");
	sm_put(sm, "", "M1");
}


void app_main(void) {
	ESP_LOGI("Tower", "In main");
	recv_q = xQueueCreate(10, sizeof(tag_packet));
	modifier_q = xQueueCreate(10, sizeof(modifier_packet));
	initialize_esp_now_tower();

	//setup the hash map

	xTaskCreate(queue_process_task, "Receive_from_car", 2048, NULL, 2, NULL);
	xTaskCreate(queue_send_task, "Send_info_to_car", 2048, NULL, 2, NULL);
}