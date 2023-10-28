//KERNEL OF ARGOS OPERATING SYSTEM


#include "lib/vga_driver.h"
#include "lib/common.h"






extern void main()                                  //MAIN KERNEL FUNCTION
{

    *(char *)0xb8000 = 'C';

    for (char *p = (char *)0xb8002; p < (char *)0xb805F; p += 1)
    {
        *p = (char)'C';
        p++;
        *p = (char)0x1f;
    }

    unsigned char cc = 'R';
    unsigned char cc1 = 'A';

    vga_printchar(cc,241,  VGA_COLOR_GREEN , VGA_COLOR_WHITE );
    

    return;
}