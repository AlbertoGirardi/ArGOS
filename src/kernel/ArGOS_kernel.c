//KERNEL OF ARGOS OPERATING SYSTEM
/***
 *                     _____  ____   _____ 
 *         /\         / ____|/ __ \ / ____|
 *        /  \   _ __| |  __| |  | | (___  
 *       / /\ \ | '__| | |_ | |  | |\___ \ 
 *      / ____ \| |  | |__| | |__| |____) |
 *     /_/    \_\_|   \_____|\____/|_____/ 
 *                                         
 *                                         
 */

#include "stdint.h"
#include <stdbool.h>
#include <stddef.h>

#include "lib/vga_driver.h"
#include "lib/screen.h"
#include "lib/libc_argos.h"
#include "lib/stdio.h"
#include "lib/terminal.h"





const char* msg_kernel_welcome = "\t\t\t\t\t\t\t\t\tArGOS\r\n\nOS KERNEL\n\rmain, in C\r\n\n" ;
const char* msg_kernel_welcome2 = "\r\n\nOS KERNEL\n\rmain, in C\r\n\n" ;

const char * msg_helloc = "Hello from C!\n\rprova\n\r\ta\n\r\t\ta";



const char* nl = "\n\r";

const char* ttt = "SSSSSSSSS\r\n\n\n\n\n\na\nb\n\nX";
const char r[] = "TERMINAL STRING";

struct Terminal terminal;


void ArGOS_MAIN(uint32_t css)                                  //MAIN KERNEL FUNCTION
{

    screen_blankT(VGA_COLOR_BLUE, VGA_COLOR_WHITE);
    set_screen_color( VGA_COLOR_WHITE, VGA_COLOR_BLUE);
    screen_write(msg_kernel_welcome);
    set_terminal(&terminal, 1, screen_rows, VGA_COLOR_WHITE, VGA_COLOR_BLUE);


    printf(msg_kernel_welcome2);
    printf("Alberto Girardi\n\r");

    printf(msg_helloc);
    terminal_set_tmp_color(VGA_COLOR_BLACK, VGA_COLOR_RED);
    printf("\r\nGloria al C!!!Glory to C!!!\n\r");
    
    printf("\n\r\n\rPRINTF!!!%d\nprova\n\n", 351);

    //printf("affjnaja\n\n\n\n\n\n\na\na\na");
    terminal_write_r(ttt, strlen(ttt));

    terminal_draw_buffer();

    for (int i = 0; i < 10; i++)
    {
    printf("\n%d",i);
    }
    

    return;


}




