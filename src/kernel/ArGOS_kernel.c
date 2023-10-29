//KERNEL OF ARGOS OPERATING SYSTEM


#include "lib/vga_driver.h"
#include "lib/common.h"
#include "lib/screen.h"






extern void main(void)                                  //MAIN KERNEL FUNCTION
{

    unsigned char cc = 'R';
    unsigned char cc1 = '0';


    vga_printchar(cc ,240,  VGA_COLOR_GREEN , VGA_COLOR_WHITE );

    
    blank_screen( VGA_COLOR_BLACK );

    vga_printchar(cc ,240,  VGA_COLOR_GREEN , VGA_COLOR_WHITE );

    test();


    return;
}