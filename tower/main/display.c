#include "display.h"
#include "esp_log.h"

#define MEM_DL_STATIC (EVE_RAM_G_SIZE - 4096) /* 0xff000 - start-address of the static part of the display-list, upper 4k of gfx-mem */
#define LAYOUT_Y1 66
uint32_t num_dl_static; /* amount of bytes in the static part of our display-list */
uint8_t tft_active = 0;
uint16_t num_profile_a, num_profile_b;
uint16_t display_list_size = 0;
int8_t userNum = 1;
int8_t lapNum = 1;
bool game_active = false;



// Car_Status_display Car1_status = { .checkpoint = 0, .lap_time = 0, .curr_lap = 0 };
// Car_Status_display Car2_status = { .checkpoint = 0, .lap_time = 0, .curr_lap = 0 };

// void update_status(uint8_t car_id, uint8_t checkpoint, int64_t lap_time, int32_t curr_lap){
//     if (car_id == 1){
//         Car1_status.checkpoint = checkpoint;
//         Car1_status.curr_lap = curr_lap;
//         Car1_status.lap_time = lap_time;
//     }
//     else if (car_id == 2){
//         Car2_status.checkpoint = checkpoint;
//         Car2_status.curr_lap = curr_lap;
//         Car2_status.lap_time = lap_time;
//     }
// }

void reverse(char str[], int length){
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
char* itoa(int num, char* str, int base){
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

void display_countdown(int countdown){
    // ESP_LOGI("Tower", "In display_countdown");

    //char number[4];
    EVE_start_cmd_burst(); /* start writing to the cmd-fifo as one stream of bytes, only sending the address once */

    EVE_cmd_dl_burst(CMD_DLSTART); /* start the display list */
    EVE_cmd_dl_burst(DL_CLEAR_RGB | WHITE); /* set the default clear color to white */
    EVE_cmd_dl_burst(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG); /* clear the screen - this and the previous prevent artifacts between lists, Attributes are the color, stencil and tag buffers */
    EVE_cmd_dl_burst(TAG(0));

    EVE_cmd_dl_burst(VERTEX_FORMAT(0)); /* reduce precision for VERTEX2F to 1 pixel instead of 1/16 pixel default */

    /* draw a rectangle on top */
    EVE_cmd_dl_burst(DL_BEGIN | EVE_RECTS);
    EVE_cmd_dl_burst(LINE_WIDTH(1*16)); /* size is in 1/16 pixel */

    EVE_cmd_dl_burst(DL_COLOR_RGB | BLUE_1);
    EVE_cmd_dl_burst(VERTEX2F(0,0));
    EVE_cmd_dl_burst(VERTEX2F(EVE_HSIZE,LAYOUT_Y1-2));
    EVE_cmd_dl_burst(DL_END);

    /* draw a black line to separate things */
    EVE_cmd_dl_burst(DL_COLOR_RGB | BLACK);
    EVE_cmd_dl_burst(DL_BEGIN | EVE_LINES);
    EVE_cmd_dl_burst(VERTEX2F(0,LAYOUT_Y1-2));
    EVE_cmd_dl_burst(VERTEX2F(EVE_HSIZE,LAYOUT_Y1-2));
    EVE_cmd_dl_burst(DL_END);


    EVE_cmd_text_burst(EVE_HSIZE/2, 15, 30, EVE_OPT_CENTERX, "Mario Kart!");
    EVE_cmd_text_burst(680, EVE_VSIZE/2-80, 30, EVE_OPT_CENTERX, "READY?");
    EVE_cmd_text_burst(200, 100, 30, EVE_OPT_CENTERX, "User Number:");
    EVE_cmd_text_burst(200, 200, 30, EVE_OPT_CENTERX, "Lap Number:");
    
    // itoa(userNum, &number, 10);
    // EVE_cmd_text_burst(200, 150, 30, EVE_OPT_CENTERX, number);
    EVE_cmd_number_burst(200, 150, 30, EVE_OPT_CENTERX, userNum);

    // itoa(lapNum, &number, 10);
    // EVE_cmd_text_burst(200, 250, 30, EVE_OPT_CENTERX, number);
    EVE_cmd_number_burst(200, 250, 30, EVE_OPT_CENTERX, lapNum);

    // itoa(countdown, &number, 10);
    // EVE_cmd_text_burst(680, 250, 30, EVE_OPT_CENTERX, number);
    EVE_cmd_number_burst(680, 250, 30, EVE_OPT_CENTERX, countdown);
  

    //while (EVE_busy()) {};

    num_dl_static = EVE_memRead16(REG_CMD_DL);

    EVE_cmd_memcpy(MEM_DL_STATIC, EVE_RAM_DL, num_dl_static);
    EVE_cmd_dl_burst(DL_DISPLAY); /* instruct the co-processor to show the list */
    EVE_cmd_dl_burst(CMD_SWAP); /* make this list active */

    EVE_end_cmd_burst();

}

void menu_display(){
    //char number[4];
    // ESP_LOGI("Tower", "In menu_display");

    // uint16_t cmd_fifo_size;
    // cmd_fifo_size = EVE_dma_buffer_index*4; /* without DMA there is no way to tell how many bytes are written to the cmd-fifo */
    EVE_start_cmd_burst(); /* start writing to the cmd-fifo as one stream of bytes, only sending the address once */
    
    EVE_cmd_dl_burst(CMD_DLSTART); /* start the display list */
    EVE_cmd_dl_burst(DL_CLEAR_RGB | WHITE); /* set the default clear color to white */
    EVE_cmd_dl_burst(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG); /* clear the screen - this and the previous prevent artifacts between lists, Attributes are the color, stencil and tag buffers */
    EVE_cmd_dl_burst(TAG(0));

    EVE_cmd_dl_burst(VERTEX_FORMAT(0)); /* reduce precision for VERTEX2F to 1 pixel instead of 1/16 pixel default */

    //EVE_cmd_append_burst(MEM_DL_STATIC, num_dl_static); /* insert static part of display-list from copy in gfx-mem */
    
    /* draw a rectangle on top */
    EVE_cmd_dl_burst(DL_BEGIN | EVE_RECTS);
    EVE_cmd_dl_burst(LINE_WIDTH(1*16)); /* size is in 1/16 pixel */
    
    EVE_cmd_dl_burst(DL_COLOR_RGB | BLUE_1);
    EVE_cmd_dl_burst(VERTEX2F(0,0));
    EVE_cmd_dl_burst(VERTEX2F(EVE_HSIZE,LAYOUT_Y1-2));
    EVE_cmd_dl_burst(DL_END);
    
    /* draw a black line to separate things */
    EVE_cmd_dl_burst(DL_COLOR_RGB | BLACK);
    EVE_cmd_dl_burst(DL_BEGIN | EVE_LINES);
    EVE_cmd_dl_burst(VERTEX2F(0,LAYOUT_Y1-2));
    EVE_cmd_dl_burst(VERTEX2F(EVE_HSIZE,LAYOUT_Y1-2));
    EVE_cmd_dl_burst(DL_END);


    EVE_cmd_text_burst(EVE_HSIZE/2, 15, 30, EVE_OPT_CENTERX, "Mario Kart!");
    EVE_cmd_text_burst(680, EVE_VSIZE/2-80, 30, EVE_OPT_CENTERX, "Start Game?");
    EVE_cmd_text_burst(200, 100, 30, EVE_OPT_CENTERX, "User Number:");
    EVE_cmd_text_burst(200, 200, 30, EVE_OPT_CENTERX, "Lap Number:");
    
    // itoa(userNum, &number, 10);
    // EVE_cmd_text_burst(200, 150, 30, EVE_OPT_CENTERX, number);
    EVE_cmd_number_burst(200, 150, 30, EVE_OPT_CENTERX, userNum);
    // itoa(lapNum, &number, 10);
    // EVE_cmd_text_burst(200, 250, 30, EVE_OPT_CENTERX, number);
    EVE_cmd_number_burst(200, 250, 30, EVE_OPT_CENTERX, lapNum);
    
    /* display a button */
    EVE_cmd_dl_burst(DL_COLOR_RGB | WHITE);
    EVE_cmd_fgcolor_burst(0x00c0c0c0); /* some grey */


    EVE_cmd_dl_burst(TAG(1));
    EVE_cmd_button_burst(300, 150, 40, 40, 28, 0,"+");

    EVE_cmd_dl_burst(TAG(2));
    EVE_cmd_button_burst(100, 150, 40, 40, 28, 0,"-");
    

    EVE_cmd_dl_burst(TAG(3));
    EVE_cmd_button_burst(300, 250, 40, 40, 28, 0,"+");

    EVE_cmd_dl_burst(TAG(4));
    EVE_cmd_button_burst(100, 250, 40, 40, 28, 0,"-");
   

    EVE_cmd_dl_burst(TAG(5)); /* assign tag-value '10' to the button that follows */
    EVE_cmd_button_burst(600, 200, 170, 40, 30, 0,"START!");

    EVE_cmd_dl_burst(TAG(0)); /* no touch */

    // EVE_cmd_setbitmap_burst(MEM_PIC1, EVE_RGB565, 100, 100);
  
    //while (EVE_busy()) {};

    num_dl_static = EVE_memRead16(REG_CMD_DL);

    EVE_cmd_memcpy(MEM_DL_STATIC, EVE_RAM_DL, num_dl_static);
    EVE_cmd_dl_burst(DL_DISPLAY); /* instruct the co-processor to show the list */
    EVE_cmd_dl_burst(CMD_SWAP); /* make this list active */

    EVE_end_cmd_burst();
}

void race_display(){
    // ESP_LOGI("Tower", "In race_display");
    uint16_t divider = LAYOUT_Y1;
    char number[4];
    EVE_start_cmd_burst(); /* start writing to the cmd-fifo as one stream of bytes, only sending the address once */
    EVE_cmd_dl_burst(CMD_DLSTART); /* start the display list */
    EVE_cmd_dl_burst(DL_CLEAR_RGB | WHITE); /* set the default clear color to white */
    EVE_cmd_dl_burst(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG); /* clear the screen - this and the previous prevent artifacts between lists, Attributes are the color, stencil and tag buffers */
    EVE_cmd_dl_burst(TAG(0));
    EVE_cmd_dl_burst(VERTEX_FORMAT(0)); /* reduce precision for VERTEX2F to 1 pixel instead of 1/16 pixel default */

    EVE_cmd_append_burst(MEM_DL_STATIC, num_dl_static); /* insert static part of display-list from copy in gfx-mem */
    
    /* draw a rectangle on top */
    EVE_cmd_dl_burst(DL_BEGIN | EVE_RECTS);
    EVE_cmd_dl_burst(LINE_WIDTH(1*16)); /* size is in 1/16 pixel */
    EVE_cmd_dl_burst(DL_COLOR_RGB | BLUE_1);
    EVE_cmd_dl_burst(VERTEX2F(0,0));
    EVE_cmd_dl_burst(VERTEX2F(EVE_HSIZE,LAYOUT_Y1-2));
    EVE_cmd_dl_burst(DL_END);

    /* draw a black line to separate things */
    EVE_cmd_dl_burst(DL_COLOR_RGB | BLACK);
    EVE_cmd_dl_burst(DL_BEGIN | EVE_LINES);
    EVE_cmd_dl_burst(VERTEX2F(0,LAYOUT_Y1-2));
    EVE_cmd_dl_burst(VERTEX2F(EVE_HSIZE,LAYOUT_Y1-2));
    EVE_cmd_dl_burst(DL_END);

    EVE_cmd_text_burst(EVE_HSIZE/2, 15, 30, EVE_OPT_CENTERX, "Mario Kart!");

   
       
    // set line color to black
    EVE_cmd_dl_burst(DL_COLOR_RGB | BLACK);
    EVE_cmd_dl_burst(DL_BEGIN | EVE_LINES);
    EVE_cmd_dl_burst(VERTEX2F(0, LAYOUT_Y1+50));
    EVE_cmd_dl_burst(VERTEX2F(EVE_HSIZE, LAYOUT_Y1+50));
    EVE_cmd_dl_burst(DL_END);


    EVE_cmd_text_burst(0, LAYOUT_Y1, 30, 0, "Player");
    EVE_cmd_text_burst(100, LAYOUT_Y1, 30, 0, "Laps");
    EVE_cmd_text_burst(200, LAYOUT_Y1, 30, 0, "Lap Time");
    EVE_cmd_text_burst(350, LAYOUT_Y1, 30, 0, "Next Checkpoint");
   // while(EVE_busy()) {};

    // for(int i = 0; i < userNum; i++){
    //     divider += 50;
    //     /* draw a black line to separate things */
    //     EVE_cmd_dl_burst(DL_COLOR_RGB | BLACK);
    //     EVE_cmd_dl_burst(DL_BEGIN | EVE_LINES);
    //     EVE_cmd_dl_burst(VERTEX2F(0, divider+50));
    //     EVE_cmd_dl_burst(VERTEX2F(EVE_HSIZE, divider+50));
    //     EVE_cmd_dl_burst(DL_END);

    //     EVE_cmd_text_burst(0, divider, 30, 0, i);
    //     EVE_cmd_text_burst(100, divider, 30, 0, "y");
    //     EVE_cmd_text_burst(170, divider, 30, 0, "xx:xx:xx");

    // }

    //Car 1 status
    divider += 50;
    /* draw a black line to separate things */
    EVE_cmd_dl_burst(DL_COLOR_RGB | BLACK);
    EVE_cmd_dl_burst(DL_BEGIN | EVE_LINES);
    EVE_cmd_dl_burst(VERTEX2F(0, divider+50));
    EVE_cmd_dl_burst(VERTEX2F(EVE_HSIZE, divider+50));
    EVE_cmd_dl_burst(DL_END);

    EVE_cmd_text_burst(0, divider, 30, 0, "Car 1");
    itoa(Car1_status.curr_lap, &number, 10);
    EVE_cmd_text_burst(100, divider, 30, 0, number);
    EVE_cmd_text_burst(115, divider, 30, 0, "/5");

    itoa(Car1_status.lap_min, &number, 10);
    EVE_cmd_text_burst(200, divider, 30, 0, number);
    EVE_cmd_text_burst(220, divider, 30, 0, ":");
    itoa(Car1_status.lap_sec, &number, 10);
    EVE_cmd_text_burst(230, divider, 30, 0, number);
    EVE_cmd_text_burst(250, divider, 30, 0, ":");
    itoa(Car1_status.lap_ms, &number, 10);
    EVE_cmd_text_burst(260, divider, 30, 0, number);

    itoa(Car1_status.checkpoint, &number, 10);
    EVE_cmd_text_burst(350, divider, 30, 0, number);

    //Car 2 status
    divider += 50;
    EVE_cmd_dl_burst(DL_COLOR_RGB | BLACK);
    EVE_cmd_dl_burst(DL_BEGIN | EVE_LINES);
    EVE_cmd_dl_burst(VERTEX2F(0, divider+50));
    EVE_cmd_dl_burst(VERTEX2F(EVE_HSIZE, divider+50));
    EVE_cmd_dl_burst(DL_END);

    EVE_cmd_text_burst(0, divider, 30, 0, "Car 2");
    itoa(Car2_status.curr_lap, &number, 10);
    EVE_cmd_text_burst(100, divider, 30, 0, number);
    EVE_cmd_text_burst(115, divider, 30, 0, "/5");

    itoa(Car2_status.lap_min, &number, 10);
    EVE_cmd_text_burst(200, divider, 30, 0, number);
    EVE_cmd_text_burst(220, divider, 30, 0, ":");
    itoa(Car2_status.lap_sec, &number, 10);
    EVE_cmd_text_burst(230, divider, 30, 0, number);
    EVE_cmd_text_burst(250, divider, 30, 0, ":");
    itoa(Car2_status.lap_ms, &number, 10);
    EVE_cmd_text_burst(260, divider, 30, 0, number);

    itoa(Car2_status.checkpoint, &number, 10);
    EVE_cmd_text_burst(350, divider, 30, 0, number);


    EVE_cmd_dl_burst(TAG(11));
    EVE_cmd_button_burst(20, 15, 150, 40, 30, 0, "Back");
    EVE_cmd_dl_burst(TAG(0));


    //while (EVE_busy()) {};

    num_dl_static = EVE_memRead16(REG_CMD_DL);

    EVE_cmd_memcpy(MEM_DL_STATIC, EVE_RAM_DL, num_dl_static);
    EVE_cmd_dl_burst(DL_DISPLAY); /* instruct the co-processor to show the list */
    EVE_cmd_dl_burst(CMD_SWAP); /* make this list active */
    //while(EVE_busy()) {};

    EVE_end_cmd_burst();
}

void task_menu(void* args){
    // uint8_t counter = 0;
    // int start_time;
    // int current_time; 
    // int countdown;
    uint8_t tag = 0;
    // menu_display();
    for(;;){
        while(EVE_busy());
        tag = EVE_memRead8(REG_TOUCH_TAG); // how to read touched tag
        // vTaskSuspendAll();  // prevent context switching when sending commands to display
        //if(!game_active){  // race creation menu
            if (tag != 0){
                printf("tag value:%d game active %d\n", tag, game_active);
                switch(tag){
                    case 1:
                        userNum += 1;
                        break;
                    case 2:
                        userNum -= 1;
                        break;
                    case 3:
                        lapNum += 1;
                        break;
                    case 4:
                        lapNum -= 1;
                        break;
                    case 5:
                        set_start_time(userNum, lapNum);
                        for(int j = 5; j >=0 ; j--){
                            vTaskDelay(1000/portTICK_PERIOD_MS);
                            display_countdown(j);
                        }
                        game_active = true;
                        break;
                    case 11:// cancel race
                        game_active = false;
                        //display_countdown(0);
                        break;
                    default: 
                        break;
                }
                
            }
            if (!game_active){
                
                userNum = userNum > 4 ? 4 : userNum < 1 ? 1 : userNum;
                lapNum = lapNum > 10 ? 10 : lapNum < 1 ? 1 : lapNum;
                menu_display();
            }
            else{
                race_display();
            }

        vTaskDelay(150/portTICK_PERIOD_MS);
    }


}