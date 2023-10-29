//KERNEL OF ARGOS OPERATING SYSTEM


#include "lib/vga_driver.h"
#include "lib/common.h"






extern void main(uint32_t n)                                  //MAIN KERNEL FUNCTION
{

    unsigned char cc = 'R';
    unsigned char cc1 = '0';


    vga_printchar(cc ,240,  VGA_COLOR_GREEN , VGA_COLOR_WHITE );


    

    return;
}