//KERNEL OF ARGOS OPERATING SYSTEM


#include "lib/vga_driver.h"
#include "lib/common.h"
#include "lib/screen.h"






extern void main(void)                                  //MAIN KERNEL FUNCTION
{

    unsigned char cc = 'R';
    unsigned char cc1 = '0';



    
    screen_initialize();

    vga_printchar(cc ,340,  VGA_COLOR_GREEN , VGA_COLOR_WHITE );

    for (int i = 0; i < 300; i++)
    {
            print_char('A', VGA_COLOR_DARK_GREY, VGA_COLOR_RED);

    }
    





    return;
}