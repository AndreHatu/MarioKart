/* file to put shared data structures, functions and definitions*/
#ifndef MARIO_KART_CONFIG
#define MARIO_KART_CONFIG

#include <inttypes.h>
#include <stdbool.h>

#define CONFIG_ESPNOW_PMK "pmk1234567890"
#define MAC_LEN 6

#define CONTROLLER_MAC_ADDR {0x1c, 0x9d, 0xc2, 0x35, 0xa8, 0xf4}
#define CAR_MAC_ADDR {0x3c, 0x61, 0x05, 0x7d, 0xe0, 0x88}
#define TOWER_MAC_ADDR {0x3c, 0x61, 0x05, 0x7d, 0xdd, 0xa4}


typedef struct __attribute__((packed)) {
	bool up;
	bool down;
	bool left;
	bool right;
} packet_t;

typedef struct {
	uint8_t sender_mac_addr[6];
	packet_t data;
} recv_packet_t;

//send data struct(car->tower) :: NFC tag information
typedef struct __attribute__((packed)) {
	uint8_t src_mac[6];
	uint8_t dest_mac[6];
	uint8_t tag_id[5];
} packet_tag;

typedef struct {
	uint8_t sender_mac_addr[6];
	packet_tag data;
} recv_packet_tag;

//send data struct(tower->car) :: modifier information
typedef struct __attribute__((packed)) {
	uint8_t src_mac[6];
	uint8_t dest_mac[6];
	uint8_t modifier[5];
} packet_modifier;

typedef struct {
	uint8_t sender_mac_addr[6];
	packet_modifier data;
} recv_packet_modifier;

#endif