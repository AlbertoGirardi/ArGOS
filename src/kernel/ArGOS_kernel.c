//KERNEL OF ARGOS OPERATING SYSTEM


#include "lib/vga_driver.h"
#include "lib/screen.h"






extern void main(void)                                  //MAIN KERNEL FUNCTION
{

    unsigned char cc = 'R';
    unsigned char cc1 = '0';



    
    screen_initialize();
    set_screen_color( VGA_COLOR_BROWN , VGA_COLOR_CYAN);
    


    for (int i = 0; i < 300; i++)
    {
            print_char('A');

    }
    
    set_screen_color( VGA_COLOR_RED , VGA_COLOR_CYAN);
    


    for (int i = 0; i < 300; i++)
    {
            print_char('A');

    }
    




    return;
}