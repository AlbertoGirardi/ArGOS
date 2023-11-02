//KERNEL OF ARGOS OPERATING SYSTEM


#include "lib/vga_driver.h"
#include "lib/screen.h"
#include "stdint.h"





extern void ArGOS_MAIN(uint32_t css)                                  //MAIN KERNEL FUNCTION
{

    screen_blank(VGA_COLOR_LIGHT_CYAN);
    set_screen_color( VGA_COLOR_WHITE , VGA_COLOR_BLUE);


    const char *t= "Hello from C!";

    

    screen_write("Alberto",7);

    set_screen_color( VGA_COLOR_GREEN, VGA_COLOR_LIGHT_MAGENTA);
    screen_write(t, 13);
    


    
    



    return;
}