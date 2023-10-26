#include "vga_driver.h"


void funtest(){

    char sttt[20] = "SSSSSSSSSSS";

    int n = 0xb8080+20*2;
    for (char *p = (char *)0xb8080; p < (char *)n; p += 1)
    {
        *p = (char)'Z';
        p++;
        *p = (char)0x3D;
    }



    int b = 1;
}