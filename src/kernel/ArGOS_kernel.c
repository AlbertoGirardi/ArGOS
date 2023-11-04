//KERNEL OF ARGOS OPERATING SYSTEM


#include "lib/vga_driver.h"
#include "lib/screen.h"
#include "stdint.h"
#include "lib/libc_argos.h"



const char* msg_kernel_welcome = "\n\t\t\t\t\t\t\t\t\tArGOS\r\n\nOS KERNEL\n\rmain, in C\r\n\n" ;
const char * msg_helloc = "Hello from C!";

int neg = -100;


const char* nl = "\n\r";


extern void ArGOS_MAIN(uint32_t css)                                  //MAIN KERNEL FUNCTION
{

    screen_blank(VGA_COLOR_BLUE);
    set_screen_color( VGA_COLOR_WHITE, VGA_COLOR_BLUE);


    screen_write(msg_kernel_welcome);                                   //printing hello messages
    screen_write("Alberto Girardi\n\r");

    screen_write(msg_helloc);
    
    screen_write("\r\nGloria al C!!!Glory to C!!!\n\r");
    screen_printIntDec(3);
    screen_write(nl);
    screen_printIntDec(-5);
    screen_write(nl);

    screen_printIntDec(-583887755);
    screen_write(nl);
    screen_printIntDec(35199997777);
    screen_write(nl);

    screen_printIntHex(-0x123aabbccdd);

    screen_write(nl);

    char n1[30];
    char* num = &n1;
    
    int_to_stringDEC(333, num);

    screen_write(num);






    return;
}