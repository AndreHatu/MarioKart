#ifndef DISPLAY_IF
#define DISPLAY_IF

#include "EVE.h"
#include "../../config/mario_kart_config.h"

#define RED     0xff0000UL
#define ORANGE  0xffa500UL
#define GREEN   0x00ff00UL
#define BLUE    0x0000ffUL
#define BLUE_1  0x5dade2L
#define YELLOW  0xffff00UL
#define PINK    0xff00ffUL
#define PURPLE  0x800080UL
#define WHITE   0xffffffUL
#define BLACK   0x000000UL


// extern Car_Status Car1_status;
// extern Car_Status Car2_status;

extern Race race;

// void update_status(uint8_t car_id, uint8_t checkpoint, int64_t lap_time, int32_t curr_lap);
void start_race(int8_t user, int8_t lap);
void display_init();
void menu_display();
void display_counter();
void display_test();
// void display_menu();
void display_green();
void display_black();
void display_blue();
void display_white();
void display_test2();
void task_menu(void* args);
void race_display();
#endif