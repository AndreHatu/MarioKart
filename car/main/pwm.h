#include <stdint.h>
#include <stdio.h>
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_attr.h"
#include "soc/rtc.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"

#define MCPWM_GPIO_INIT 0    //select which function to use to initialize gpio signals
#define GPIO_PWM0A_OUT 15   //Set GPIO 15 as PWM0A
#define GPIO_PWM0B_OUT 17  //Set GPIO 17 as PWM0B
#define V0 100.0
#define VSPEED 75.0
#define VSLOW 45.0
#define VFRONT 90.0

void brushed_motor_a(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num , float duty_cycle);
void brushed_motor_b(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num , float duty_cycle);
void brushed_motor_stop(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num);
// void activate_mod(void);

void mcpwm_example_gpio_initialize(void);
void mcpwm_example_config(void * arg);