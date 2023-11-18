#pragma once

#include "stdint.h"
#include <stdbool.h>
#include <stddef.h>

#include "vga_driver.h"
#include "screen.h"
#include "libc_argos.h"
#include "stdio.h"
#include "terminal.h"



#define terminal_line_buffer_lenght 100             //how many lines of the terminal to save to memory



struct Terminal
{
    int ts_start_row;               //starting screen row of the terminal
    int ts_end_row;                 //last screen row of the terminal

    int rows;              //calculated from the numbers before           
    //int terminal_columns;

    int  sc_cursor_row;
    int  sc_cursor_column;

    int cursor_line;
    
    int t_cursorC;
    int t_cursorR;

    char lines_buffer_char[VGA_TXT_COLUMNS*terminal_line_buffer_lenght];
    enum vga_color lines_buffer_colchar[VGA_TXT_COLUMNS*terminal_line_buffer_lenght];
    enum vga_color lines_buffer_colbkg[VGA_TXT_COLUMNS*terminal_line_buffer_lenght];


    enum vga_color terminal_color_char;
    enum vga_color terminal_color_bkg;


};



extern int print(const char* str);
extern int print_r(const char* str, size_t len);
extern void set_terminal(struct Terminal *_terminalp, int ts_start_row, int ts_end_row);

extern void terminal_printchar(unsigned char c);
extern void terminal_print_char_c(unsigned char c, enum vga_color color_char, enum vga_color color_bkg);
extern void terminal_draw_buffer();

extern int terminal_write_r(const  char* stringw, size_t str_size);



