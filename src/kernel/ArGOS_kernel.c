//KERNEL OF ARGOS OPERATING SYSTEM


#include "lib/vga_driver.h"
#include "lib/screen.h"
#include "stdint.h"


static uint32_t f=2;
static uint32_t *g ;
char * o= "tttttttttttttttttttttttttttt";


extern void ArGOS_MAIN(uint32_t css)                                  //MAIN KERNEL FUNCTION
{

    blank_screen(VGA_COLOR_LIGHT_CYAN);
    set_screen_color( VGA_COLOR_WHITE , VGA_COLOR_BLUE);


    const char *t= "Hello from C!";

    

    screen_write("Alberto",7);
    screen_write(t, 13);
    screen_write(o,28);

    if (f == 1)
    {
        print_char('K');
    }
    


    
    



    return;
}