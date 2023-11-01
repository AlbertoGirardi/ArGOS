#ifndef SCREEN
#define SCREEN



#include "vga_driver.h"





extern void blank_screen( enum vga_color color_bkg  );
extern void test();
extern void screen_initialize(void);
extern void print_char_c(unsigned char c, enum vga_color color_char, enum vga_color color_bkg);
extern void print_char(unsigned char c );
extern void set_screen_color( enum vga_color color_char, enum vga_color color_bkg );
extern int screen_write(  char* stringw, size_t str_size);
extern int putchar(int ic , size_t n);

extern void ptr_test(int* b);

#endif