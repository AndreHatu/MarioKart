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
#include "display.h"

static xQueueHandle recv_q;
static xQueueHandle modifier_q;

bool start_game;
//hash map Definition for tag information
StrMap *sm; 	 // address of the start point of the string map
char value[4]; // buffer to copy the value of a certain key
int current_time;
int start_time;

Car_Status Car1_status = { .checkpoint = 0, .lap_time = 0 };
Car_Status Car2_status = { .checkpoint = 0, .lap_time = 0 };

Start_pack Start_information = { .time_now = 0, .user_num = 0, .lap_num = 0 };

int64_t millis() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + (tv.tv_usec / 1000LL));
}


void set_start_time(int8_t user, int8_t lap){
	start_time = millis();
	Start_information.time_now = start_time;
    Start_information.lap_num = lap;
	Start_information.user_num = user;
}


uint8_t random_modifier(){
	//return values: 
	//	0: power up
	//	1: power down
	//	2: reverse control
	//	3: stop
	return (uint8_t) (esp_random() % 4);
	//return 0;
}

// assign random modifier based on tag or mark checkpoint
void tag_handler(tag_packet packet){
	//print the tag id
	printf("Received tag packet: %02x %02x %02x %02x %02x \n", packet.tag_id[0], packet.tag_id[1], packet.tag_id[2], packet.tag_id[3], packet.tag_id[4]);
	
	//Figure out which car sent the tag packet (to update car status)
	Car_Status my_car;
	//uint8_t car1[MAC_LEN] = CAR1_MAC_ADDR;
	uint8_t car1[MAC_LEN] = CAR1_MAC_ADDR;
	uint8_t car2[MAC_LEN] = CAR2_MAC_ADDR;
	uint8_t other_car[MAC_LEN];

	if (strcmp((char*)(car1), (char*)(packet.src_mac)) == 0){
		memcpy(&other_car, car2, MAC_LEN);
		my_car = Car1_status;
	}
	else{
		memcpy(&other_car, car2, MAC_LEN);	
		my_car = Car2_status;	
	}
	uint8_t id[TAG_LEN];
	memcpy(id, packet.tag_id, TAG_LEN);

	for (int i = 0; i < TAG_LEN; i++){
		if (id[i] > 0x7f){
			id[i] %= 0x7f;
		}
		if (id[i]<0x20){
			id[i] += 0x20;
		}
	}
	//Figure out whether tag is checkpoint or modifier
	char str[TAG_LEN+1];
	//size_t bufflen = sizeof(packet.tag_id);
    memcpy( str, id, TAG_LEN );
    str[TAG_LEN] = '\0'; // 'str' is now a string
	printf("%s\n", str);

	int result = sm_get(sm, str, value, sizeof(value));
	if (result == 0){	//if tag id sent is not saved in the map
		printf("key not found\n");
		return;
	}


	if (value[0] == 'M'){
			uint8_t mod = random_modifier(); // get random modifier
			printf("%02x\n", mod);
			//setup send packet
			modifier_packet* new_packet = malloc(sizeof(modifier_packet));
			new_packet->modifier = mod;

			//if powerup, send back to sender address, if not, send to the other car
			memcpy(&(new_packet->target_mac_addr), packet.src_mac, MAC_LEN);
			
			//add packet to queue
			if(xQueueSend(modifier_q, new_packet, portMAX_DELAY) != pdTRUE){
				ESP_LOGW("Tower", "Modifier Queue Full");
			}
			free(new_packet);
			printf("Send Success\n");
	}
			
	else if (value[0] == 'C'){
			//figure out which car status to modify
			printf("current checkpoint: %02x, lap time:%ld \n", my_car.checkpoint, (long)(my_car.lap_time));
			int val = value[1] - '0';
			if (val == (my_car.checkpoint%5)){

				my_car.lap_time += packet.lap_time;
				my_car.checkpoint++;
				if (my_car.checkpoint >= 5){
					my_car.checkpoint %= 5;
				}
			}
			//update lap status
			printf("car status updated\n");
			printf("new checkpoint: %02x, lap time:%ld \n", my_car.checkpoint, (long)(my_car.lap_time));
	}


	// modifier_packet* send_packet = malloc(sizeof(modifier_packet));
	// send_packet->modifier = 0xff;
	// if(xQueueSend(modifier_q, send_packet, portMAX_DELAY) != pdTRUE){
	// 	ESP_LOGW("Tower", "Modifier Queue Full");
	// }
}

//receive data from car (NFC tag information)
static void queue_process_task(void *p)
{
	// if (!start_game){
	// 	taskYIELD();
	// }
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
	if (!start_game){
		return;
	}
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
	uint8_t car[MAC_LEN] = CAR2_MAC_ADDR;
	for(;;){
		if (xQueueReceive(modifier_q, packet, portMAX_DELAY) == pdTRUE){
			// NOTE: need to add some switching logic to figure out if we send packet to either car or both
			if(esp_now_send(car, (uint8_t*)packet, sizeof(modifier_packet)) != ESP_OK){
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
	start_game = false;
	sm = sm_new(51);
	if (sm == NULL){
		printf("string map not created \n");
	}
	//save checkpoint
	// uint8_t id [TAG_LEN] = {0x88, 0x4, 0x36, 0x72, 0xc8};
	// for (int i = 0; i < TAG_LEN; i++){
	// 	if (id[i] > 0x7f){
	// 		id[i] %= 0x7f;
	// 	}
	// 	if (id[i]<0x20){
	// 		id[i] += 0x20;
	// 	}
	// }
	// char str[TAG_LEN+1];
    // memcpy(str, id, TAG_LEN);
	// str[TAG_LEN] = '\0';
	// printf("add tag: %s \n", str);
	//printf("%s", "r68;E\0\n");
	//sm_put(sm, "r68;E", "C0");
	// sm_put(sm, "1", "C1");
	// sm_put(sm, "2", "C2");
	// sm_put(sm, "3", "C3");
	// sm_put(sm, "4", "C4");

	//save modifier
	sm_put(sm, "r68;E", "M");
	
    // sm_put(sm, ")$h^", "M");
	// sm_put(sm, ")$0yd", "M");
	// sm_put(sm, ")$&V", "M");
	// sm_put(sm, ")$ >3", "M");
	// sm_put(sm, ")$1(6", "M");
	// sm_put(sm, ")$Y,X", "M");
	// sm_put(sm, ")$G'M", "M");
	// sm_put(sm, ")$a:V", "M");
	// sm_put(sm, ")$6|e", "M");
	// sm_put(sm, ")$%%rZ", "M");

	// sm_put(sm, ")$=N\\", "M");
	// sm_put(sm, ")$8lY", "M");
	// sm_put(sm, ")$/$", "M");
	// sm_put(sm, ")$x;P", "M");
	// sm_put(sm, ")$ 8+", "M");
	// sm_put(sm, ")$Jm(", "M");
	// sm_put(sm, ")$C/A", "M");
	// sm_put(sm, ")$+Vt", "M");
	// sm_put(sm, ")$c,d", "M");
	// sm_put(sm, ")$=l^", "M");
	
	// sm_put(sm, ")$>`Q", "M");
	// sm_put(sm, ")$w \\", "M");
	// sm_put(sm, ")$?8*", "M");
	// sm_put(sm, ")$6>%%", "M");
	// sm_put(sm, ")$#Q", "M");
	// sm_put(sm, ")$I5Q", "M");
	// sm_put(sm, ")$4^e", "M");
	// sm_put(sm, ")$c*h", "M");
	// sm_put(sm, ")$V0w ", "M");

	// sm_put(sm, ")$y(R", "M");
	// sm_put(sm, ")$&83", "M");
	// sm_put(sm, ")$|""Q", "M");
	// sm_put(sm, ")$Lb#", "M");
	// sm_put(sm, ")$28+", "M");
	// sm_put(sm, ")$93'", "M");
	// sm_put(sm, ")$>2#", "M");
	// sm_put(sm, ")$zW""", "M");
	// sm_put(sm, ")$OZ", "M");
	// sm_put(sm, ")$=*8", "M");
	
	// sm_put(sm, ")$&KD", "M");
	// sm_put(sm, ")$<du", "M");
	// sm_put(sm, ")$d/h", "M");
	// sm_put(sm, ")$>,=", "M");
	// sm_put(sm, ")$v-t", "M");
	// sm_put(sm, ")$Pl1", "M");
	// sm_put(sm, ")$7+1", "M");
	// sm_put(sm, ")$<~m", "M");
	// sm_put(sm, ")$u2h", "M");
	// sm_put(sm, ")$6rI", "M");
}

void app_main(void) {
	ESP_LOGI("Tower", "In main");
	recv_q = xQueueCreate(10, sizeof(tag_packet));
	modifier_q = xQueueCreate(10, sizeof(modifier_packet));
	initialize_esp_now_tower();

	//setup the hash map
	initialize_hash();
	xTaskCreate(queue_process_task, "Receive_from_car", 2048, NULL, 2, NULL);
	xTaskCreate(queue_send_task, "Send_info_to_car", 2048, NULL, 2, NULL);

	display_init();
	//display_menu();
	//display_test();
	//display_button(WHITE);
	//xTaskCreate(touch_task, "handle_touches", 2048, NULL, 2, NULL);
	xTaskCreate(task_menu, "handle_touches", 2048, NULL, 2, NULL);
	//race_display();
}