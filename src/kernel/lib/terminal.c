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
    

    terminal_draw_buffer();
    return;


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

        }
        
    }
    

}




int print(const char* str){

    /*currently wrapper for screen write*/
//todo stub

    int written = terminal_write_r(str, strlen(str));
    terminal_draw_buffer();


    return written;
}




int print_r(const char* str, size_t len)
{

    /*currently wrapper for screen write*/


    int written = terminal_write_r(str, len);
    // screen_write("/");
    return written;
}




void terminal_print_char_c(unsigned char c, enum vga_color color_char, enum vga_color color_bkg)
{

    /*prints chat, allowing to specify color, in the screen*/

    uint16_t char_position = terminalp->t_cursorC  + (terminalp->t_cursorR + terminalp->cursor_line)* VGA_TXT_COLUMNS;

    terminalp->lines_buffer_char[char_position] = c;
    
    terminalp->lines_buffer_colchar[char_position] = color_char;
    terminalp->lines_buffer_colbkg[char_position] = color_bkg;


    vga_move_cursor(get_cursor_pos( terminalp->t_cursorR +  terminalp->ts_start_row,terminalp->t_cursorC+1));                  //moves cursor


    


    if ((terminalp->t_cursorC + 1) < VGA_TXT_COLUMNS)
    {
        terminalp->t_cursorC++;
    }

    else
    {

        terminal_scroll();
        

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



void terminal_scroll(){


        if ( terminalp->t_cursorR+1 < terminalp->rows )
        {
            
            terminalp->t_cursorR++;
            terminalp->t_cursorC = 0;
            
        }
        else
        {
            terminalp->t_cursorC = 0;
            terminalp->cursor_line++;
            


        }
        

    return;
}




int terminal_write_r(const  char* stringw, size_t str_size)
{

    /*prints a string given as a pointer to the screen,  requires it being given the lenght
    HANDLES \r \n \t \b 
    */

    uint16_t cursor_pos = 0;

    for (size_t i = 0; i < str_size; i++)
    {

        switch (stringw[i])
        {
        case '\n': // line feed

            terminal_scroll();            
            break;

        case '\r': // carriage return
            terminalp->t_cursorC = 0;
            break;

        case '\t':
            terminalp->t_cursorC = ((terminalp->t_cursorC / 4) + 1) * 4;
            break;

        case '\b':
        //todo set using rerminal
            set_cursor_pos_abs(get_current_cursor_pos() - 1);
            print_char(' ');
            set_cursor_pos_abs(get_current_cursor_pos() - 1);

            break;

        default:
            terminal_print_char_c(stringw[i],terminalp->terminal_color_char,terminalp->terminal_color_bkg); // prints character

            //cursor_pos = (uint16_t)get_current_cursor_pos(); // stores cursor position of last non blanck character

            break;
        }
    }

    //vga_move_cursor(cursor_pos);                  //moves cursor


    return 0;


}
