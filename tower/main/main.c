#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <sys/time.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "freertos/event_groups.h"
// #include "freertos/queue.h"
// #include "driver/gpio.h"
#include "driver/spi_master.h"
// #include "nvs_flash.h"
// #include "esp_netif.h"
// #include "esp_wifi.h"
// #include "esp_log.h"
// #include "esp_now.h"
// #include "esp_system.h"
// #include "esp_sleep.h"

#include "../../config/mario_kart_config.h"
// #define EVE_NHD_70
#include "EVE.h"
#define PINK (uint32_t)0xff00f2 

void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
		char buffer = *(str+start);
		*(str+start) = *(str+end);
		*(str+end) = buffer;
        // swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}
 
// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;
 
    /* Handle 0 explicitly, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}

void app_main(void) {
	EVE_init_spi();
	EVE_init();
	int i = 0;
	uint32_t touchValue, touchX, touchY;
	char* buffer = malloc(sizeof(char) * 15);
	for(;;){
		EVE_cmd_dl(CMD_DLSTART); // tells EVE to start a new display-list
		EVE_cmd_dl(DL_CLEAR_RGB | PINK); // sets the background color
		EVE_cmd_dl(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG);
		EVE_color_rgb(10000);
		buffer = itoa(i, buffer, 10);
		EVE_cmd_text(EVE_HSIZE/2, 50, 28, EVE_OPT_CENTER, buffer);

		EVE_cmd_dl(DL_COLOR_RGB | 0x0000ff);
        EVE_cmd_dl(POINT_SIZE(20*16));
        EVE_cmd_dl((DL_BEGIN | EVE_POINTS));
        EVE_cmd_dl(VERTEX2F((16*i)%7300, (16*i)%7300));
        EVE_cmd_dl(DL_END);

		printf("Count: %d\n", i);
		i++;
		while(EVE_busy());
		touchValue = EVE_memRead32(REG_TOUCH_DIRECT_XY);
		touchX = (touchValue>>16) & 0x03FF; /* raw Touchscreen Y coordinate */
		touchY = touchValue & 0x03FF;
		buffer = itoa(touchX, buffer, 10);
		EVE_cmd_text((EVE_HSIZE/2) - 50, 70, 28, EVE_OPT_CENTER, buffer);
		buffer = itoa(touchY, buffer, 10);
		EVE_cmd_text((EVE_HSIZE/2) + 50, 70, 28, EVE_OPT_CENTER, buffer);

		EVE_cmd_dl(DL_DISPLAY); // put in the display list to mark its end
		EVE_cmd_dl(CMD_SWAP); // tell EVE to use the new display list

		vTaskDelay(100 / portTICK_PERIOD_MS);
		
	}
		
		
}