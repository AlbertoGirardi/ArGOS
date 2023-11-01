#include "screen.h"


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static size_t screen_cursor_row;
static size_t screen_cursor_column;

static enum vga_color screen_color_char;
static enum vga_color screen_color_bkg;


static uint16_t const screen_rows = 25;
static uint16_t const screen_columns = 80;


void screen_initialize(void)
{
    /*
    Initializes the screen zeroing the cursor, blancks it with black
    */

    screen_cursor_column = 0;
    screen_cursor_row = 0;
    blank_screen(VGA_COLOR_BLACK);
}


void set_screen_color( enum vga_color color_char, enum vga_color color_bkg ){

    screen_color_bkg = color_bkg;
    screen_color_char = color_char;
}


void blank_screen(enum vga_color color_bkg)
{

    /*covers the screen with the indicated color*/

    unsigned char c = '0';
    // vga_printchar(c, cursor  , VGA_COLOR_GREEN, VGA_COLOR_RED );

    uint16_t cursor = 0;

    for (cursor = 0; cursor < (uint16_t)(screen_columns * screen_rows); cursor++)
    {

        vga_printchar(c, cursor, color_bkg, color_bkg);
    }

    return;
}

size_t get_cursor_pos(size_t row, size_t col)
{

    return (row) * 80 + col;
}




void print_char_c(unsigned char c, enum vga_color color_char, enum vga_color color_bkg)
{

    /*prints chat, allowing to specify color, in the screen*/

    vga_printchar(c, get_cursor_pos(screen_cursor_row, screen_cursor_column), color_char, color_bkg);

    if ((screen_cursor_column + 1) < screen_columns)
    {
        screen_cursor_column++;
    }

    else
    {
        screen_cursor_row++;
        screen_cursor_column = 0;

        // vga_printchar('Q', (500+screen_cursor_row), VGA_COLOR_BLUE, VGA_COLOR_RED );      //debug code
    }
}


void print_char(unsigned char c ){

    /*
    prints a character to the screen following the last one
    */

    print_char_c(c, screen_color_char, screen_color_bkg);
}


void ptr_test(int* b){

    if (*b == 3)
    {
        print_char('O');
    }
    



}

int screen_write(const  char* stringw, size_t str_size){


    for (size_t i = 0; i < str_size; i++)
    {
        print_char(stringw[i]);
    }

   /* char* u[2]= "aa";
    print_char(*u[0]);
    return str_size;
  return 0;*/
    
}

int putchar(int ic , size_t n){

    char c = (char) ic;
	screen_write(&c, n);
}



void test( int x, int *px){


    if (x == *px)
    {
        print_char('K');
    }
    
}