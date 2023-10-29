#ifndef SCREEN
#define SCREEN



#include "vga_driver.h"





extern void blank_screen( enum vga_color color_bkg  );
extern void test();
extern void screen_initialize(void);
extern void print_char_c(unsigned char c, enum vga_color color_char, enum vga_color color_bkg);


#endif