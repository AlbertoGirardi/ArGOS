//KERNEL OF ARGOS OPERATING SYSTEM


#include "lib/vga_driver.h"
#include "lib/screen.h"
#include "stdint.h"
#include "lib/libc_argos.h"





extern void ArGOS_MAIN(uint32_t css)                                  //MAIN KERNEL FUNCTION
{

    screen_blank(VGA_COLOR_LIGHT_CYAN);
    set_screen_color( VGA_COLOR_WHITE, VGA_COLOR_BLUE);


    const char *t= "Hello from C!";

    

    screen_write("Alberto");

    screen_write(t);
    
    screen_write("\r\nGloria al C!!!Glory to C");




    return;
}