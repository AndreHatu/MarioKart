#include "display.h"

#define MEM_DL_STATIC (EVE_RAM_G_SIZE - 4096) /* 0xff000 - start-address of the static part of the display-list, upper 4k of gfx-mem */
#define LAYOUT_Y1 66
uint32_t num_dl_static; /* amount of bytes in the static part of our display-list */
uint8_t tft_active = 0;
uint16_t num_profile_a, num_profile_b;
uint16_t display_list_size = 0;

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

    // EVE_cmd_inflate(MEM_LOGO, logo1, sizeof(logo1)); /* load logo into gfx-memory and de-compress it */
    // EVE_cmd_loadimage(MEM_PIC1, EVE_OPT_NODL, pic1, sizeof(pic1));
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

void display_button(uint64_t bg_color, int16_t x0, int16_t y0, int16_t w0, int16_t h0, int16_t font){
    uint16_t cmd_fifo_size;
    cmd_fifo_size = EVE_dma_buffer_index*4; /* without DMA there is no way to tell how many bytes are written to the cmd-fifo */
    EVE_start_cmd_burst(); /* start writing to the cmd-fifo as one stream of bytes, only sending the address once */
    EVE_cmd_dl_burst(CMD_DLSTART); /* start the display list */
    EVE_cmd_dl_burst(DL_CLEAR_RGB | bg_color); /* set the default clear color to white */
    EVE_cmd_dl_burst(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG); /* clear the screen - this and the previous prevent artifacts between lists, Attributes are the color, stencil and tag buffers */
    EVE_cmd_dl_burst(TAG(0));

    EVE_cmd_append_burst(MEM_DL_STATIC, num_dl_static); /* insert static part of display-list from copy in gfx-mem */
    /* display a button */
    EVE_cmd_dl_burst(DL_COLOR_RGB | WHITE);
    EVE_cmd_fgcolor_burst(0x00c0c0c0); /* some grey */
    EVE_cmd_dl_burst(TAG(10)); /* assign tag-value '10' to the button that follows */
    EVE_cmd_button_burst(x0, y0, w0, h0, font, 0,"Touch!");
    EVE_cmd_dl_burst(TAG(0)); /* no touch */

    // EVE_cmd_setbitmap_burst(MEM_PIC1, EVE_RGB565, 100, 100);

    #if defined (EVE_DMA)
    EVE_cmd_number_burst(100, EVE_VSIZE - 65, 26, EVE_OPT_RIGHTX, cmd_fifo_size); /* number of bytes written to the cmd-fifo */
    #endif
    EVE_cmd_number_burst(100, EVE_VSIZE - 50, 26, EVE_OPT_RIGHTX, display_list_size); /* number of bytes written to the display-list by the command co-pro */
    EVE_cmd_number_burst(100, EVE_VSIZE - 35, 26, EVE_OPT_RIGHTX|4, num_profile_a); /* duration in us of TFT_loop() for the touch-event part */
    EVE_cmd_number_burst(100, EVE_VSIZE - 20, 26, EVE_OPT_RIGHTX|4, num_profile_b); /* duration in us of TFT_loop() for the display-list part */

    EVE_cmd_dl_burst(DL_DISPLAY); /* instruct the co-processor to show the list */
    EVE_cmd_dl_burst(CMD_SWAP); /* make this list active */

    EVE_end_cmd_burst();

}

void touch_task(void* args){
    uint8_t counter = 0;
    display_button(WHITE, 20, 20, 80, 30, 28);
    for(;;){
        while(EVE_busy());
        uint8_t tag = EVE_memRead8(REG_TOUCH_TAG); // how to read touched tag
        if(tag==10){
            printf("Touched!\n");
            switch(counter){
                case 0: display_button(GREEN, 100, 100, 30, 30, 28); counter = 1; break;
                case 1: display_button(BLUE, 200, 200, 40, 40, 30); counter = 2; break;
                case 2: display_button(BLACK, 300, 300, 52, 35, 30);  counter = 3; break;
                case 3: display_button(YELLOW, 400, 400, 64, 35, 30); counter = 4; break;
                case 4: display_button(RED, 700, 400, 70, 30, 30); counter = 0; break;
                default: display_button(WHITE, 20, 20, 80, 30, 28); counter = 0; break;
            }
        }
        vTaskDelay(200/portTICK_PERIOD_MS);
    }


}

void display_green(){
    EVE_cmd_dl(CMD_DLSTART); // tells EVE to start a new display-list
    EVE_cmd_dl(DL_CLEAR_RGB | GREEN); // sets the background color
    EVE_cmd_dl(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG);
    EVE_cmd_dl(DL_END);
    // EVE_cmd_dl(DL_DISPLAY); // put in the display list to mark its end
    // EVE_cmd_dl(CMD_SWAP); // tell EVE to use the new display list
}

void display_blue(){
    EVE_cmd_dl(CMD_DLSTART); // tells EVE to start a new display-list
    EVE_cmd_dl(DL_CLEAR_RGB | BLUE); // sets the background color
    EVE_cmd_dl(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG);
    EVE_cmd_dl(DL_END);
    // EVE_cmd_dl(DL_DISPLAY); // put in the display list to mark its end
    // EVE_cmd_dl(CMD_SWAP); // tell EVE to use the new display list}
}

void display_black(){
    EVE_cmd_dl(CMD_DLSTART); // tells EVE to start a new display-list
    EVE_cmd_dl(DL_CLEAR_RGB | BLACK); // sets the background color
    EVE_cmd_dl(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG);
    EVE_cmd_dl(DL_END);
}

void display_white(){
    EVE_cmd_dl(CMD_DLSTART); // tells EVE to start a new display-list
    EVE_cmd_dl(DL_CLEAR_RGB | WHITE); // sets the background color
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
    // uint32_t posX, posY;
    // posX = 0;
    // posY = 0;
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
            display_button(WHITE, 20, 20, 20, 20, 20);
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
        // posX = (16*i)%7300;
        // posY = posX;
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