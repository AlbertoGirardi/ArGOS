//KERNEL OF ARGOS OPERATING SYSTEM


#include "lib/vga_driver.h"
#include "lib/common.h"
#include "lib/screen.h"






extern void main(void)                                  //MAIN KERNEL FUNCTION
{

    unsigned char cc = 'R';
    unsigned char cc1 = '0';


    vga_printchar(cc ,240,  VGA_COLOR_GREEN , VGA_COLOR_WHITE );

    
    screen_initialize();

    vga_printchar(cc ,240,  VGA_COLOR_GREEN , VGA_COLOR_WHITE );

    test();

    


    return;
}