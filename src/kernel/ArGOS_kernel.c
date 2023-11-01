//KERNEL OF ARGOS OPERATING SYSTEM


#include "lib/vga_driver.h"
#include "lib/screen.h"
#include "stdint.h"

static uint16_t c = 3;

uint32_t aaa = 3456;
uint32_t f =1;
uint32_t *g;

uint32_t yu;

//char o[50];

extern void ArGOS_MAIN(uint32_t css)                                  //MAIN KERNEL FUNCTION
{

    char ccc[]= "uuuuuuuuuuuuuuuuuuuu";

    f =1;
    g = &f;
    
    
    char *cp = &ccc;
    
    screen_initialize();
    blank_screen(VGA_COLOR_RED);
    set_screen_color( VGA_COLOR_BROWN , VGA_COLOR_CYAN);

  
    char t[]= "Hello from C!";
    char *v = &t;


    screen_write(v, 14);
    screen_write(v, 14);
    screen_write(v, 14);
    screen_write(v, 14);
    screen_write(cp, 20);


    
    
   
    



    return;
}