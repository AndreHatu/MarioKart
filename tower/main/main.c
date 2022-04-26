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

#define NCHECKPOINTS 5

static xQueueHandle recv_q;
static xQueueHandle modifier_q;

bool start_game;
//hash map Definition for tag information
StrMap *sm; 	 // address of the start point of the string map
char value[4]; // buffer to copy the value of a certain key
int current_time;
int start_time;

// Car_Status Car1_status = { .checkpoint = 0, .lap_min = 0, .lap_sec = 0, .lap_ms = 0, .curr_lap = 0 };
// Car_Status Car2_status = { .checkpoint = 0, .lap_min = 0, .lap_sec = 0, .lap_ms = 0, .curr_lap = 0 };
// const uint8_t car1_mac[MAC_LEN] = CAR1_MAC_ADDR;
// const uint8_t car2_mac[MAC_LEN] = CAR2_MAC_ADDR;

Start_pack Start_information = { .car1_start_time = 0,.car2_start_time=0, .user_num = 0, .lap_num = 0 };

Race race;

int64_t millis() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + (tv.tv_usec / 1000LL));
}


// void set_start_time(int8_t user, int8_t lap){
// 	start_time = millis();
// 	Start_information.start_time = start_time;
//     Start_information.lap_num = lap;
// 	Start_information.user_num = user;
// }

void reset_race_stat(int8_t user){
	// free(race.car1_times);
	// if(user > 1){
	// 	free(race.car2_times);
	// }
	start_game = false;
	printf("[Race Stoped] Reset Races Statistics\n");
}

// call this function whenever the user clicks the "start" button on screen
// initializes the race struct which contains information on lap
void start_race(int8_t user, int8_t lap){
	int i;
	int time_array_size = NCHECKPOINTS * Start_information.lap_num + 1;
	start_time = millis();
	Start_information.car1_start_time = -1;
	Start_information.car2_start_time = -1;
    Start_information.lap_num = lap;
	Start_information.user_num = user;

	race.car1.checkpoint = 0;
	race.car1.curr_lap = 0;
	for (i = 0; i < time_array_size; ++i)
    	race.car1_times[i] = 0;
	race.car1.lap_min = 0;
	race.car1.lap_sec = 0;
	race.car1.lap_ms = 0;
	race.car1.race_end = false;
	race.car1.win = false;
	race.car1.modifier = 5;

	if(user > 1){
		race.car2.checkpoint = 0;
		race.car2.curr_lap = 0;
		for (i = 0; i < time_array_size; ++i)
    		race.car2_times[i] = 0;	
		race.car2.lap_min = 0;
		race.car2.lap_sec = 0;
		race.car2.lap_ms = 0;
		race.car2.race_end = false;
		race.car2.win = false;
		race.car2.modifier = 5;
	}
	start_game = true;
	printf("start information updated\n");
}

uint8_t random_modifier(){
	//return values: 
	//	0: power up
	//	1: power down
	//	2: reverse control
	//	3: stop
	//return (uint8_t) (esp_random() % 4);
	return 0;
}

void update_checkpoint(uint8_t car_id, uint8_t checkpoint, uint64_t time){
	printf("checkpoint tagged: %d\n", checkpoint);
	Car_Status* this_car;
	Car_Status* other_car;
	uint64_t * time_array;
	uint64_t* car_start_time;
	if (car_id == 1){
		printf("Car 1: \n	Checkpoint Update\n");
		this_car = &race.car1;
		other_car = &race.car2;
		time_array = race.car1_times;
		car_start_time = &Start_information.car1_start_time;
	}
	else if (car_id == 2){
		printf("Car 2: \n	Checkpoint Update\n");
		this_car = &race.car2;
		other_car = &race.car1;
		time_array = race.car2_times;
		car_start_time = &Start_information.car2_start_time;
	}
	else {
		return;
	}

	// When Passing the Start Line
	if (*car_start_time == -1){
		if (checkpoint == 0){
			printf("	Start Line passed!/n");
			*car_start_time = time;
			time_array[0] = 0;
			this_car->curr_lap += 1;
		}
		else{
			printf("	You did not passed the start line!\n");
			return;
		}
	}
	else if (this_car->race_end) { // When Player passed the Finish Line
		printf("[USER 1]RACE ALREADY ENDED\n");
		return;
	}
	else{ // When Player is in between the race
		if (((this_car->checkpoint + 1) % NCHECKPOINTS) == checkpoint){
			printf("	Correct checkpoint passed \n");
			uint64_t lap_time;
			uint8_t lap = this_car->curr_lap;
			this_car->checkpoint = checkpoint;

			if (checkpoint == 0){ // when starting new lap
				printf("		Checkpoint is 0\n		NEW LAP!\n");
				lap_time = time - *car_start_time - time_array[NCHECKPOINTS*(lap-1)];
				this_car->curr_lap += 1;
				lap += 1;
				time_array[checkpoint + NCHECKPOINTS * (lap-1)] = time - *car_start_time;
			}
			else{
				printf("		Checkpoint is %d\n", checkpoint);
				time_array[checkpoint + NCHECKPOINTS * (lap-1)] = time - *car_start_time;
				lap_time = time - *car_start_time - time_array[NCHECKPOINTS*(lap-1)];
			}


			if (lap > Start_information.lap_num){ // when race ends
				printf("	End Line Passed! \n");
				this_car->race_end = true;
				this_car->curr_lap = Start_information.lap_num;
				if (Start_information.user_num == 1){
					this_car->win = true;
					race.winner = true;
				}
				else if (!(other_car->win)){
						this_car->win = true;
				}
				else{
					if (race.car1_times[5*Start_information.lap_num] > race.car2_times[5*Start_information.lap_num]){
						race.winner = true;
					}
				}
				lap_time = time - *car_start_time;
			}
			else{
				printf("time array lap start time : %lld\n", time_array[NCHECKPOINTS*(lap-1)]);
			}
			this_car->lap_min = lap_time/60000;
			this_car->lap_sec = (lap_time%60000)/1000;
			this_car->lap_ms = lap_time%61000;
		}
	}
}

// assign random modifier based on tag or mark checkpoint
void tag_handler(tag_packet packet){
	//print the tag id
	printf("Received tag packet: %02x %02x %02x %02x %02x \n", packet.tag_id[0], packet.tag_id[1], packet.tag_id[2], packet.tag_id[3], packet.tag_id[4]);
	
	//Figure out which car sent the tag packet (to update car status)
	uint8_t car_id;
	printf("Received mac addr: %02x %02x %02x %02x %02x %02x\n", packet.src_mac[0], packet.src_mac[1], packet.src_mac[2], packet.src_mac[3], packet.src_mac[4], packet.src_mac[5]);
	if (packet.src_mac[0] == 0x1c){
		car_id = 1;
	}
	else {
		car_id = 2;
	}
	
	uint8_t id[TAG_LEN + 1];
	id[TAG_LEN] = '\0';
	memcpy(id, packet.tag_id, TAG_LEN);
	// format tag so it fits within strmap constraints
	for (int i = 0; i < TAG_LEN; i++){
		if (id[i] > 0x7f){
			id[i] %= 0x7f;
		}
		if (id[i]<0x20){
			id[i] += 0x20;
		}
	}
	printf("%s\n", id);
	//Figure out whether tag is checkpoint or modifier
	int result = sm_get(sm, (char*)id, value, sizeof(value));
	if (result == 0){	//if tag id sent is not saved in the map
		printf("key not found\n");
		return;
	}

	// craft return packet according to whether it is a modifier or a checkpoint
	if (value[0] == 'M'){
			uint8_t mod = random_modifier(); // get random modifier
			printf("%02x\n", mod);
			//setup send packet
			modifier_packet new_packet; 
			new_packet.modifier = mod;
			// send it back to original car
			memcpy(new_packet.target_mac_addr, packet.src_mac, MAC_LEN);
			
			//add packet to queue
			if(xQueueSend(modifier_q, &new_packet, portMAX_DELAY) != pdTRUE){
				ESP_LOGW("Tower", "Modifier Queue Full");
			}
			// free(new_packet);
			switch(car_id){
				case 1: race.car1.modifier = mod; break;
				case 2: race.car2.modifier = mod; break;
				default: race.car2.modifier = 5; break;
			}

			printf("Modifier Send Success\n");
	}
			
	else if (value[0] == 'C'){
			//figure out which car status to modify
			//printf("startTime: %ld, packet laptime: %ld\n", (long)Start_information.start_time, (long)packet.lap_time);
			// printf("current checkpoint: %02x, lap time:%d:%d:%d \n", my_car.checkpoint, my_car.lap_min, my_car.lap_sec, my_car.lap_ms);
			uint8_t checkpoint = value[1] - '0'; // add 1 to make checkpoint counting start from 1
			update_checkpoint(car_id, checkpoint, packet.lap_time);

			// if (val == (my_car.checkpoint%5)){
			// 	//my_car.lap_time += packet.lap_time;
			// 	my_car.checkpoint++;
			// 	if (my_car.checkpoint >= 5){
			// 		my_car.checkpoint %= 5;
			// 		my_car.curr_lap += 1;
			// 	}
			// 	update_checkpoint(car_id, my_car.checkpoint, packet.lap_time);
			// 	// update_status(car_id, my_car.checkpoint, my_car.lap_time, my_car.curr_lap);
			// }
			// printf("new checkpoint: %02x, lap time:%d:%d:%d \n", my_car.checkpoint, my_car.lap_min, my_car.lap_sec, my_car.lap_ms);
			//update lap status
			printf("check point read\n");
			printf("car status updated\n");
			//printf("new checkpoint: %02x, lap time:%ld \n", my_car.checkpoint, (long)(my_car.lap_time));
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
	if (!start_game){
		taskYIELD();
	}
    tag_packet recv_packet;// = malloc(sizeof(tag_packet));

    ESP_LOGI("Tower", "Listening");
    for(;;)
    {
        if(xQueueReceive(recv_q, &recv_packet, portMAX_DELAY) == pdTRUE)
        {
			tag_handler(recv_packet);
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

	if(len == sizeof(used_mod_packet)){
		// NOTE: values here are hard coded for now
		switch(mac_addr[0]){
			case 0x1c: race.car1.modifier = 5; break;  // car 1
			case 0x78: race.car2.modifier = 5; break;  // car 2
		}
		return;
	}

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
	// uint8_t car[MAC_LEN] = CAR1_MAC_ADDR;
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

	start_game = false;
	sm = sm_new(51);
	if (sm == NULL){
		printf("string map not created \n");
	}
	
	//save modifier
	sm_put(sm, "r68;E", "M");
	sm_put(sm, ")$=N\\", "M");
	sm_put(sm, ")$8lY", "M");
	sm_put(sm, ")$/$ ", "M");
	sm_put(sm, ")$x;P", "M");
	sm_put(sm, ")$ 8+", "M");
	
	
	// Checkpoint 4
	sm_put(sm, ")$y(R", "C4");
	sm_put(sm, ")$&83", "C4");
	sm_put(sm, ")$|\"Q", "C4");
	sm_put(sm, ")$Lb#", "C4");
	sm_put(sm, ")$Jm(", "C4");
	sm_put(sm, ")$C/A", "C4");
	sm_put(sm, ")$+Vt", "C4");
	sm_put(sm, ")$c,d", "C4");
	sm_put(sm, ")$=l^", "C4");

	// Checkpoint 3
	sm_put(sm, ")$28+", "C3");
	sm_put(sm, ")$93\'", "C3");
	sm_put(sm, ")$>2#", "C3");
	sm_put(sm, ")$zW\"", "C3");
	sm_put(sm, ")$h^;", "C3");
	sm_put(sm, ")$&V ", "C3");
	sm_put(sm, ")$Y,X", "C3");
	sm_put(sm, ")$a:V", "C3");
	sm_put(sm, ")$ >3", "C3");

	// Checkpoint 2
	sm_put(sm, ")$OZ:", "C2");
	sm_put(sm, ")$=*8", "C2");
	sm_put(sm, ")$&KD", "C2");
	sm_put(sm, ")$<du", "C2");
	sm_put(sm, ")$>`Q", "C2");
	sm_put(sm, ")$?8*", "C2");
	sm_put(sm, ")$6>%", "C2");
	sm_put(sm, ")$#Q ", "C2");
	sm_put(sm, ")$I5Q", "C2");

	// Checkpoint 1
	sm_put(sm, ")$d/h", "C1");
	sm_put(sm, ")$>,=", "C1");
	sm_put(sm, ")$v-t", "C1");
	sm_put(sm, ")$Pl1", "C1");
	sm_put(sm, ")$4^e", "C1");
	sm_put(sm, ")$c*h", "C1");
	sm_put(sm, ")$V0w", "C1");
	sm_put(sm, ")$8e^", "C1");
	sm_put(sm, ")$0yd", "C1");


	// Checkpoint 0 Start line
	sm_put(sm, ")$7+1", "C0");
	sm_put(sm, ")$<~m", "C0");
	sm_put(sm, ")$u2h", "C0");
	sm_put(sm, ")$6rI", "C0");
	sm_put(sm, ")$%rZ", "C0");
	sm_put(sm, ")$G'M", "C0");
	sm_put(sm, ")$1(6", "C0");
	sm_put(sm, ")$6|e", "C0");
	sm_put(sm, ")$w \\", "C0");
}
void initialize_time_array(){
	int time_array_size = 5 * 10 + 1;
	for (int i = 0; i < time_array_size; ++i){
    	race.car1_times[i] = 0;
		race.car2_times[i] = 0;
	}
}

void app_main(void) {
	ESP_LOGI("Tower", "In main");
	recv_q = xQueueCreate(10, sizeof(tag_packet));
	modifier_q = xQueueCreate(10, sizeof(modifier_packet));
	initialize_esp_now_tower();

	//setup the hash map
	initialize_hash();
	initialize_time_array();
	xTaskCreate(queue_process_task, "Receive_from_car", 2048, NULL, 2, NULL);
	xTaskCreate(queue_send_task, "Send_info_to_car", 2048, NULL, 2, NULL);

	display_init();

	//xTaskCreate(touch_task, "handle_touches", 2048, NULL, 2, NULL);
	xTaskCreate(task_menu, "handle_touches", 2048, NULL, 2, NULL);
}