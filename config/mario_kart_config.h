#ifndef MARIO_KART_CONFIG
#define MARIO_KART_CONFIG

#include <inttypes.h>
#include <stdbool.h>
#include <time.h>

#define CONFIG_ESPNOW_PMK "pmk1234567890"
#define MAC_LEN 6
#define TAG_LEN 5

// NOTE: might have to define AP and STA mac addresses for sending and receiving
#define CONTROLLER1_MAC_ADDR {0x1c, 0x9d, 0xc2, 0x2f, 0x1a, 0x00}  //new
#define 	   CAR1_MAC_ADDR {0x1c, 0x9d, 0xc2, 0x2f, 0x19, 0xf0} //new

#define	CONTROLLER2_MAC_ADDR {0x1c, 0x9d, 0xc2, 0x2f, 0x19, 0xb0}
#define 	   CAR2_MAC_ADDR {0x78, 0x21, 0x84, 0x34, 0xfe, 0x24}
//#define 	   CAR2_MAC_ADDR {0x1c, 0x9d, 0xc2, 0x35, 0xa9, 0x18}

//#define 	  TOWER_MAC_ADDR {0x3c, 0x61, 0x05, 0x7d, 0xdd, 0xa4}// old
#define 	  TOWER_MAC_ADDR {0x1c, 0x9d, 0xc2, 0x2f, 0x19, 0xbc}

//Struct for car status amid race
typedef struct __attribute__((packed)) {
	uint8_t checkpoint;
	uint8_t curr_lap;
	uint8_t lap_ms;
	uint8_t lap_sec;
	uint32_t lap_min;
} Car_Status;

// struct to hold checkpoint times during a race
typedef struct {
	Car_Status car1;
	uint64_t* car1_times;
	Car_Status car2;
	uint64_t* car2_times;
} Race;

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

typedef struct __attribute__((packed)) {
	uint8_t modifier;
} active_mod_packet;

typedef struct __attribute__((packed)) {
	uint64_t start_time;
	uint8_t user_num;
	uint8_t lap_num;
} Start_pack;

#endif