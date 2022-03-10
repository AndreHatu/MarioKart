#include "display.h"

#define MEM_DL_STATIC (EVE_RAM_G_SIZE - 4096) /* 0xff000 - start-address of the static part of the display-list, upper 4k of gfx-mem */
#define LAYOUT_Y1 66
uint32_t num_dl_static; /* amount of bytes in the static part of our display-list */
uint8_t tft_active = 0;
uint16_t num_profile_a, num_profile_b;

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


void display_init(){
    EVE_init_spi();
    EVE_init();
    EVE_init_dma();
}

void display_menu(){
    EVE_cmd_dl(CMD_DLSTART); /* Start the display list */

    EVE_cmd_dl(TAG(0)); /* do not use the following objects for touch-detection */

    EVE_cmd_bgcolor(PINK); /* light grey */

    EVE_cmd_dl(VERTEX_FORMAT(0)); /* reduce precision for VERTEX2F to 1 pixel instead of 1/16 pixel default */

    /* draw a rectangle on top */
    EVE_cmd_dl(DL_BEGIN | EVE_RECTS);
    EVE_cmd_dl(LINE_WIDTH(1*16)); /* size is in 1/16 pixel */

    EVE_cmd_dl(DL_COLOR_RGB | BLUE_1);
    EVE_cmd_dl(VERTEX2F(0,0));
    EVE_cmd_dl(VERTEX2F(EVE_HSIZE,LAYOUT_Y1-2));
    EVE_cmd_dl(DL_END);

    /* display the logo */
    // EVE_cmd_dl(DL_COLOR_RGB | WHITE);
    // EVE_cmd_dl(DL_BEGIN | EVE_BITMAPS);
    // EVE_cmd_setbitmap(MEM_LOGO, EVE_ARGB1555, 56, 56);
    // EVE_cmd_dl(VERTEX2F(EVE_HSIZE - 58, 5));
    // EVE_cmd_dl(DL_END);

    /* draw a black line to separate things */
    EVE_cmd_dl(DL_COLOR_RGB | BLACK);
    EVE_cmd_dl(DL_BEGIN | EVE_LINES);
    EVE_cmd_dl(VERTEX2F(0,LAYOUT_Y1-2));
    EVE_cmd_dl(VERTEX2F(EVE_HSIZE,LAYOUT_Y1-2));
    EVE_cmd_dl(DL_END);


    EVE_cmd_text(EVE_HSIZE/2, 15, 29, EVE_OPT_CENTERX, "EVE Demo");


    /* add the static text to the list */
#if defined (EVE_DMA)
    EVE_cmd_text(10, EVE_VSIZE - 65, 26, 0, "Bytes:");
#endif
    EVE_cmd_text(10, EVE_VSIZE - 50, 26, 0, "DL-size:");
    EVE_cmd_text(10, EVE_VSIZE - 35, 26, 0, "Time1:");
    EVE_cmd_text(10, EVE_VSIZE - 20, 26, 0, "Time2:");

    EVE_cmd_text(105, EVE_VSIZE - 35, 26, 0, "us");
    EVE_cmd_text(105, EVE_VSIZE - 20, 26, 0, "us");

    while (EVE_busy()) {};

    num_dl_static = EVE_memRead16(REG_CMD_DL);

    EVE_cmd_memcpy(MEM_DL_STATIC, EVE_RAM_DL, num_dl_static);
    while (EVE_busy()) {};
}

void display_counter(int i, char* buffer){
    EVE_cmd_dl(CMD_DLSTART); // tells EVE to start a new display-list
    EVE_cmd_dl(DL_CLEAR_RGB | PINK); // sets the background color
    EVE_cmd_dl(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG);
    // EVE_color_rgb(10000);
    // buffer = itoa(i, buffer, 10);
    // EVE_cmd_text(EVE_HSIZE/2, 50, 28, EVE_OPT_CENTER, buffer);

    // EVE_cmd_dl(DL_COLOR_RGB | 0x0000ff);
    // EVE_cmd_dl(POINT_SIZE(20*16));
    // EVE_cmd_dl((DL_BEGIN | EVE_POINTS));
    // EVE_cmd_dl(VERTEX2F((16*i)%7300, (16*i)%7300));
    EVE_cmd_dl(DL_END);
}

void display_green(){
    EVE_cmd_dl(CMD_DLSTART); // tells EVE to start a new display-list
    EVE_cmd_dl(DL_CLEAR_RGB | GREEN); // sets the background color
    EVE_cmd_dl(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG);
    EVE_cmd_dl(DL_END);
}

void display_blue(){
    EVE_cmd_dl(CMD_DLSTART); // tells EVE to start a new display-list
    EVE_cmd_dl(DL_CLEAR_RGB | BLUE); // sets the background color
    EVE_cmd_dl(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG);
    EVE_cmd_dl(DL_END);
}

void display_black(){
    EVE_cmd_dl(CMD_DLSTART); // tells EVE to start a new display-list
    EVE_cmd_dl(DL_CLEAR_RGB | BLACK); // sets the background color
    EVE_cmd_dl(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG);
    EVE_cmd_dl(DL_END);
}

void display_test(){
    int i = 0;
	uint32_t touchValue, touchX, touchY;
	uint32_t prev_touchX, prev_touchY;
    char* buffer = malloc(sizeof(char) * 15);
    prev_touchX = 1023;
    prev_touchY = 1023;
    uint32_t posX, posY;
    posX = 0;
    posY = 0;
	for(;;){
        if(prev_touchY < 50){
            display_black();
        }
        else if(prev_touchX < 300){
            display_green();
        }
        else if(prev_touchX < 699){
            display_blue();
        }
        else if (prev_touchY > 50){
            display_counter(i, buffer);
        }
        else{
            display_black();
        }
        
        EVE_cmd_dl(CMD_DLSTART); // tells EVE to start a new display-list
        EVE_color_rgb(10000);
        buffer = itoa(i, buffer, 10);
        EVE_cmd_text(EVE_HSIZE/2, 50, 28, EVE_OPT_CENTER, buffer);

        EVE_cmd_dl(DL_COLOR_RGB | 0x0000ff);
        EVE_cmd_dl(POINT_SIZE(20*16));
        EVE_cmd_dl((DL_BEGIN | EVE_POINTS));
        posX = (16*i)%7300;
        posY = posX;
        EVE_cmd_dl(VERTEX2F((16*i)%7300, (16*i)%7300));
		// printf("Count: %d\n", i);
		i++;
		while(EVE_busy());
		touchValue = EVE_memRead32(REG_TOUCH_DIRECT_XY);
		touchX = (touchValue>>16) & 0x03FF; /* raw Touchscreen Y coordinate */
		touchY = touchValue & 0x03FF;
        if(touchY != 1023 || touchX != 1023){
            prev_touchX = touchX;
            prev_touchY = touchY;
        }
		buffer = itoa(touchX, buffer, 10);
		EVE_cmd_text((EVE_HSIZE/2) - 50, 70, 28, EVE_OPT_CENTER, buffer);
		buffer = itoa(touchY, buffer, 10);
		EVE_cmd_text((EVE_HSIZE/2) + 50, 70, 28, EVE_OPT_CENTER, buffer);

		EVE_cmd_dl(DL_DISPLAY); // put in the display list to mark its end
		EVE_cmd_dl(CMD_SWAP); // tell EVE to use the new display list

		vTaskDelay(100 / portTICK_PERIOD_MS);
		
	}
}