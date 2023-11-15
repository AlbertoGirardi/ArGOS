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
    terminalp->cursor_line_vrt = 0;

    terminalp->terminal_color_bkg = VGA_COLOR_LIGHT_GREEN;
    terminalp->terminal_color_char = VGA_COLOR_RED;




}



void tscreen_printchar(unsigned char c)
{

    print_char_c(c,terminalp->terminal_color_char ,terminalp->terminal_color_bkg);

    return;
}


void terminal_draw_buffer()
{


    for (int r = terminalp->ts_start_row; r < terminalp->ts_end_row; r++)
    {
        for (int c = 0; c < VGA_TXT_COLUMNS; c++)
        {
            set_cursor_pos_colrow(r,c);

            int cursore = 80*(r- terminalp->ts_start_row)+c;
            tscreen_printchar(terminalp->lines_buffer_char[cursore]);
        }
        
    }
    

}


int print(const char* str){

    /*currently wrapper for screen write*/


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
