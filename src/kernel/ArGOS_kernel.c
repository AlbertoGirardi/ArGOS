//KERNEL OF ARGOS OPERATING SYSTEM


#include "lib/vga_driver.h"
#include "lib/screen.h"
#include "stdint.h"
#include "lib/libc_argos.h"



const char* msg_kernel_welcome = "\n\t\t\t\t\t\t\t\t\tArGOS\r\n\nOS KERNEL\r\n\n" ;
const char *t= "Hello from C!";



extern void ArGOS_MAIN(uint32_t css)                                  //MAIN KERNEL FUNCTION
{

    screen_blank(VGA_COLOR_BLUE);
    set_screen_color( VGA_COLOR_WHITE, VGA_COLOR_BLUE);



    
    screen_write(msg_kernel_welcome);                                   //printing hello messages
    screen_write("Alberto\n\r");

    screen_write(t);
    
    screen_write("\r\nGloria al C!!!Glory to C!!!\r\n\n");
    screen_blank(VGA_COLOR_BLUE);

    set_cursor_pos_abs(80);



    screen_write("awno");

    screen_write("\b\b");

    
    




    return;
}