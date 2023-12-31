#ifndef SCREEN
#define SCREEN



#include "vga_driver.h"

#define VGA_TXT_ROWS 25
#define VGA_TXT_COLUMNS 80


static uint16_t const screen_rows = VGA_TXT_ROWS;
static uint16_t const screen_columns = VGA_TXT_COLUMNS;



extern void screen_blank( enum vga_color color_bkg  );
extern void screen_blankT(enum vga_color color_bkg, enum vga_color color_char);

extern void screen_initialize(void);
extern void print_char_c(unsigned char c, enum vga_color color_char, enum vga_color color_bkg);
extern void print_char(unsigned char c );

extern void set_screen_color( enum vga_color color_char, enum vga_color color_bkg );
extern void set_screen_text_color( enum vga_color color_char );
extern enum vga_color get_char_color();
extern enum vga_color get_bkg_color();


extern int screen_write_r(const  char* stringw, size_t str_size);
extern int screen_write(const  char* stringw);
extern void screen_werror(const char* stringe);


extern void set_cursor_pos_abs(size_t cursor);
extern void set_cursor_pos_colrow(size_t row, size_t col);
extern size_t get_current_cursor_pos();
extern size_t get_cursor_pos(size_t row, size_t col);






#endif