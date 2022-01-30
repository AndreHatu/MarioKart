#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"


#define GPIO_INPUT_0 26
#define GPIO_INPUT_1 33
#define GPIO_INPUT_2 36
#define GPIO_INPUT_3 37
#define GPIO_INPUT_PIN_SELECT ((1ULL<<GPIO_INPUT_0)|(1ULL<<GPIO_INPUT_1)|(1ULL<<GPIO_INPUT_2)|(1ULL<<GPIO_INPUT_3))


static xQueueHandle gpio_event_q = NULL;

static void gpio_event(void* args){
	for(;;){
		printf("up: %d, down: %d, left: %d, right: %d\n", gpio_get_level(GPIO_INPUT_0), gpio_get_level(GPIO_INPUT_1), gpio_get_level(GPIO_INPUT_2), gpio_get_level(GPIO_INPUT_3));
	}
}

void app_main(void) {
	gpio_config_t io_conf;
	io_conf.intr_type = GPIO_INTR_DISABLE;//GPIO_INTR_POSEDGE;
	io_conf.pin_bit_mask = GPIO_INPUT_PIN_SELECT;
	io_conf.mode = GPIO_MODE_INPUT;
	io_conf.pull_down_en = 1;
	io_conf.pull_up_en = 0;
	gpio_config(&io_conf);

	gpio_event_q = xQueueCreate(10, sizeof(uint32_t));
	xTaskCreate(gpio_event, "gpio_event", 1000, NULL, 10, NULL);


}