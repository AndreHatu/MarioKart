/* file to put shared data structures, functions and definitions*/
#ifndef MARIO_KART_CONFIG
#define MARIO_KART_CONFIG

#include <inttypes.h>
#include <stdbool.h>
#include <time.h>

#define CONFIG_ESPNOW_PMK "pmk1234567890"
#define MAC_LEN 6
#define TAG_LEN 5

// NOTE: might have to define AP and STA mac addresses for sending and receiving
#define CONTROLLER1_MAC_ADDR {0x1c, 0x9d, 0xc2, 0x35, 0xa8, 0xf4}
#define 	   CAR1_MAC_ADDR {0x3c, 0x61, 0x05, 0x7d, 0xe0, 0x88}
#define	CONTROLLER2_MAC_ADDR {0x1c, 0x9d, 0xc2, 0x35, 0xa9, 0x64}
#define 	   CAR2_MAC_ADDR {0x1c, 0x9d, 0xc2, 0x35, 0xa9, 0x18}
#define 	  TOWER_MAC_ADDR {0x3c, 0x61, 0x05, 0x7d, 0xdd, 0xa4}

//Struct for packets being sent from controller to car
typedef struct __attribute__((packed)) {
	uint8_t checkpoint;
	int64_t lap_time;
} Car_Status;


//Struct for packets being sent from controller to car
typedef struct __attribute__((packed)) {
	bool up;
	bool down;
	bool left;
	bool right;
	bool mod;
} controls_packet;

//struct for packet received by car from controller
typedef struct __attribute__((packed)) {
	uint8_t sender_mac_addr[MAC_LEN];
	controls_packet data;
} recv_controls_packet;

//send data struct(car->tower) :: NFC tag information
typedef struct __attribute__((packed)) {
	uint8_t src_mac[MAC_LEN];
	uint8_t tag_id[TAG_LEN + 1];
	int64_t lap_time;
} tag_packet;

//struct for packet received by tower from car
typedef struct __attribute__((packed)) {
	uint8_t sender_mac_addr[MAC_LEN];
	tag_packet data;
} recv_tag_packet;

//send data struct(tower->car) :: modifier information
typedef struct __attribute__((packed)) {
	uint8_t target_mac_addr[MAC_LEN];
	uint8_t modifier;
} modifier_packet;

//struct for packet received by car from tower
typedef struct __attribute__((packed)) {
	uint8_t sender_mac_addr[MAC_LEN];
	modifier_packet data;
} recv_modifier_packet;



#endif