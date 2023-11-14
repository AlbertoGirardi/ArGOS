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
const char * msg_helloc = "Hello from C!";



const char* nl = "\n\r";


const char r[] = "TERMINAL STRING";

struct Terminal terminal;


void ArGOS_MAIN(uint32_t css)                                  //MAIN KERNEL FUNCTION
{

    screen_blankT(VGA_COLOR_BLUE, VGA_COLOR_WHITE);
    set_screen_color( VGA_COLOR_WHITE, VGA_COLOR_BLUE);


    screen_write(msg_kernel_welcome);                                   //printing hello messages
    screen_write("Alberto Girardi\n\r");

    screen_write(msg_helloc);
    
    screen_write("\r\nGloria al C!!!Glory to C!!!\n\r");
    
    printf("\n\r\n\rPRINTF!!!%d\nprova\n\n", 351);

    memmove(&terminal.lines_buffer[0], &r[0], strlen(&r[0]) );
   
    printf("%x\n\n", (&terminal.lines_buffer[0] - 0x9000) );

    memmove(&terminal.lines_buffer[0], (char*) 0xb8000 + 160*3 ,  (25*160));      //saves screen lines
    

    memset( (char*) 0xb8000, 0, 80*25*160);//blanks the screen brute force

    memmove( (char*) 0xb8000 ,&terminal.lines_buffer[0] , (25*160));      //restores old screeen

    //printf("%s", &terminal.lines_buffer[0]);
    printf("tutto ok :)");



    return;


}