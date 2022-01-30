#include <stdio.h>
#include "rc522.h"
#include "driver/gpio.h"


void tag_handler(uint8_t* serial_no){
	gpio_set_level(5, 1);
	for(int i = 0; i < 5; i++)
		printf("%#x ", serial_no[i]);

	printf("\n");
	gpio_set_level(5, 0);
}
void app_main(void) {
	const rc522_start_args_t start_args = {
		.miso_io = 25,
		.mosi_io = 23,
		.sck_io = 19,
		.sda_io = 22,
		.callback = &tag_handler
	};

	const gpio_config_t pin_config = {
		.pin_bit_mask = (1ULL << 5) | (1ULL << 10) | (1ULL << 18),
		.mode = GPIO_MODE_INPUT,
		.intr_type = GPIO_INTR_DISABLE,
		.pull_down_en = 0,
		.pull_up_en = 1
	};
	gpio_config(&pin_config);

	gpio_set_level(18, 1);
	rc522_start(start_args);
}