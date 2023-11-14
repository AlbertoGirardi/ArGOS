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

    int terminal_rows;              //calculated from the numbers before           
    //int terminal_columns;

    // int  terminal_cursor_row;
    // int  terminal_cursor_column;

    int terminal_first_vrt_row;

    char lines_buffer[2*VGA_TXT_COLUMNS*terminal_line_buffer_lenght];

    

};



extern int print(const char* str);
extern int print_r(const char* str, size_t len);
