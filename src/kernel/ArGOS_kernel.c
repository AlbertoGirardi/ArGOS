//KERNEL OF ARGOS OPERATING SYSTEM


#include "lib/vga_driver.h"
#include "lib/screen.h"
#include "stdint.h"
#include "lib/libc_argos.h"



const char* msg_kernel_welcome = "\n\t\t\t\t\t\t\t\t\tArGOS\r\n\nOS KERNEL\n\rmain, in C\r\n\n" ;
const char * msg_helloc = "Hello from C!";

const char *testmem = "   \0\0\0";

const char* nl = "\n\r";


extern void ArGOS_MAIN(uint32_t css)                                  //MAIN KERNEL FUNCTION
{
    const char *testmem2 = "   " ;

    screen_blank(VGA_COLOR_BLUE);
    set_screen_color( VGA_COLOR_WHITE, VGA_COLOR_BLUE);



    
    screen_write(msg_kernel_welcome);                                   //printing hello messages
    screen_write("Alberto Girardi\n\r");

    screen_write(msg_helloc);
    
    screen_write("\r\nGloria al C!!!Glory to C!!!\n\r");

   /* memset(testmem, 'd', 3);
    screen_write(testmem);
    
    memmove(testmem2, testmem, 3);
    screen_write(testmem2);
*/
    screen_printIntDec(1);
    screen_write(nl);
    screen_printIntDec(css);
    screen_write(nl);
  
    screen_printIntHex((long long)&nl);

    screen_write(nl);
    screen_printIntDec(123456789);
    screen_write(nl);


    




    return;
}