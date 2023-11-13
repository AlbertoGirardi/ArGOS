#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "libc_argos.h"

#include "screen.h"




static size_t screen_cursor_row;
static size_t screen_cursor_column;

static enum vga_color screen_color_char;
static enum vga_color screen_color_bkg;




void screen_initialize(void)
{
    /*
    Initializes the screen zeroing the cursor, blancks it with black
    */

    screen_cursor_column = 0;
    screen_cursor_row = 0;
    screen_blank(VGA_COLOR_BLACK);
}


enum vga_color get_char_color(){

    return screen_color_char;
}



enum vga_color get_bkg_color(){

    return screen_color_bkg;
}

void set_screen_color( enum vga_color color_char, enum vga_color color_bkg ){

    /*sets the color of the characters and of the background*/

    screen_color_bkg = color_bkg;
    screen_color_char = color_char;
}




void set_screen_text_color( enum vga_color color_char ){

    /*sets only the color of the text*/
    
    screen_color_char = color_char;
}


void screen_blank(enum vga_color color_bkg)
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

    /*gets the cursor position from the row and col number*/

    return (row) * 80 + col;
}



size_t get_current_cursor_pos()
{

    /*gets the current cursor position from the row and col number*/

    return  get_cursor_pos( screen_cursor_row, screen_cursor_column );
}


void set_cursor_pos_colrow(size_t row, size_t col){

    /*sets the screen col and row number to the specified values*/

    if (row < screen_rows && col < screen_columns)
    {
        screen_cursor_column = col;
        screen_cursor_row = row;
    }
    

    

    return;


}


void set_cursor_pos_abs(size_t cursor)

{
    /*sets the col and row from the absolute cursor position*/

    if (cursor < (screen_rows*screen_columns))
    {
        
    screen_cursor_row = cursor / screen_columns;
    screen_cursor_column = cursor % screen_columns;

    }
    
    return ;


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

        if (screen_cursor_row+1 < screen_rows  )
        {
            
        screen_cursor_row++;
        screen_cursor_column = 0;
        }
        

        // vga_printchar('Q', (500+screen_cursor_row), VGA_COLOR_BLUE, VGA_COLOR_RED );      //debug code
    }

    return;
}


void print_char(unsigned char c ){

    /*
    prints a character to the screen following the last one
    */

    print_char_c(c, screen_color_char, screen_color_bkg);
    return;
}






int screen_write_r(const  char* stringw, size_t str_size){

    /*prints a string given as a pointer to the screen,  requires it being given the lenght
    HANDLES \r \n \t \b 
    */

    uint16_t cursor_pos = 0;

    for (size_t i = 0; i < str_size; i++)
    {

        switch (stringw[i])
        {
        case '\n': // line feed

            if (screen_cursor_row + 1 < screen_rows)                        //avoiding terminal overflow
            {
                screen_cursor_row++;
            }
            break;

        case '\r': // carriage return
            screen_cursor_column = 0;
            break;

        case '\t':
            screen_cursor_column = ((screen_cursor_column / 4) + 1) * 4;
            break;

        case '\b':
            set_cursor_pos_abs(get_current_cursor_pos() - 1);
            print_char(' ');
            set_cursor_pos_abs(get_current_cursor_pos() - 1);

            break;

        default:
            print_char(stringw[i]); // prints character

            cursor_pos = (uint16_t)get_current_cursor_pos(); // stores cursor position of last non blanck character

            break;
        }
    }

    vga_move_cursor(cursor_pos-1);                  //moves cursor

    return 0;


}

int screen_write(const  char* stringw){

    /*prints a given string to the screen, after the text before that
    returns written character number*/

    screen_write_r(stringw, strlen(stringw));
    return strlen(stringw);
}



void screen_werror(const char* stringe){

    /*prints given error message to the screen changing the color to red*/

    int char_col = get_char_color();

    set_screen_text_color(VGA_COLOR_RED);

    screen_write(stringe);

    set_screen_text_color(char_col);
}
