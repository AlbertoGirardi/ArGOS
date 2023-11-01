//KERNEL OF ARGOS OPERATING SYSTEM


#include "lib/vga_driver.h"
#include "lib/screen.h"
#include "stdint.h"

//uint32_t m = 512;
char u[]="dududududududududududududd";

static uint32_t f;
static uint32_t *g ;


//char o[50];

void init(){

    f =1;
    g = &f;
    
}

extern void ArGOS_MAIN(uint32_t css)                                  //MAIN KERNEL FUNCTION
{

    blank_screen(VGA_COLOR_LIGHT_CYAN);
    set_screen_color( VGA_COLOR_WHITE , VGA_COLOR_BLUE);

    
    //screen_write( 0x9c00 ,2500);
    



    init();
    const char t[]= "Hello from C!";
    const char *v = (const char *) &t;

    const char x1[] = "yyyyyyy";
    const char *x = (const char *) &x1 ;

    //screen_write(x, 14);
    //screen_write(v, 13);
    screen_write(0x8c00, 300);
    
    char * dp = 0xac00;
if (*dp == 'd')
{
    print_char('K');
}

    
    



    return;
}