#include "stdint.h"
#include <stdbool.h>
#include <stddef.h>
#include "stdarg.h"

#include "terminal.h"
#include "screen.h"



struct Terminal *terminalp;


void set_terminal(struct Terminal *_terminalp, int ts_start_row, int ts_end_row)
{

    /*
    sets the terminal pointer to the terminal struct created
    */
    terminalp = _terminalp;

    terminalp->ts_start_row = ts_start_row;
    terminalp->ts_end_row = ts_end_row;

    terminalp->rows = terminalp->ts_end_row - terminalp->ts_start_row;

    terminalp->sc_cursor_row = 0;
    terminalp->sc_cursor_column = 0;
    terminalp->cursor_line = 0;

    terminalp->t_cursorC = 0;
    terminalp->t_cursorR = 0;


//TODO set also colors
    terminalp->terminal_color_bkg = VGA_COLOR_GREEN;
    terminalp->terminal_color_char = VGA_COLOR_WHITE;

    for (int i = 0; i < VGA_TXT_COLUMNS*terminal_line_buffer_lenght; i++)
    {
        terminalp->lines_buffer_colchar[i] = terminalp->terminal_color_char;
        terminalp->lines_buffer_colbkg[i] = terminalp->terminal_color_bkg;
    }
    




}



void tscreen_printchar(unsigned char c, enum vga_color color_char, enum vga_color color_bkg)
{

    /*wrapper for  print char from screen library*/

    print_char_c(c,color_char, color_bkg);

    return;
}


void terminal_draw_buffer()
{


    for (int r = terminalp->ts_start_row; r < terminalp->ts_end_row; r++)
    {
        for (int c = 0; c < VGA_TXT_COLUMNS; c++)
        {
            set_cursor_pos_colrow(r,c);

            int cursore = 80*(r- terminalp->ts_start_row + terminalp->cursor_line )+c;
            tscreen_printchar(terminalp->lines_buffer_char[cursore],terminalp->lines_buffer_colchar[cursore], terminalp->lines_buffer_colbkg[cursore]);

            //terminalp->terminal_color_char, terminalp->terminal_color_bkg
        }
        
    }
    

}




int print(const char* str){

    /*currently wrapper for screen write*/
//todo stub

    int written = screen_write(str);

    return written;
}




int print_r(const char* str, size_t len)
{

    /*currently wrapper for screen write*/


    int written = screen_write_r(str, len);
    // screen_write("/");
    return written;
}




void terminal_print_char_c(unsigned char c, enum vga_color color_char, enum vga_color color_bkg)
{

    /*prints chat, allowing to specify color, in the screen*/

//todo also change colors

    terminalp->lines_buffer_char[ terminalp->t_cursorC  + terminalp->t_cursorR* VGA_TXT_COLUMNS] = c;



    if ((terminalp->t_cursorC + 1) < VGA_TXT_COLUMNS)
    {
        terminalp->t_cursorC++;
    }

    else
    {

        terminalp->t_cursorR++;
        terminalp->t_cursorC = 0;
        
        
        

        // vga_printchar('Q', (500+screen_cursor_row), VGA_COLOR_BLUE, VGA_COLOR_RED );      //debug code
    }


    return;
}

// void print_char(unsigned char c)
// {

//     /*
//     prints a character to the screen following the last one
//     */

//     print_char_c(c, screen_color_char, screen_color_bkg);
//     return;
// }