#pragma once


#define terminal_line_buffer_lenght 100             //how many lines of the terminal to save to memory

struct terminal
{
    int ts_start_row;               //starting screen row of the terminal
    int ts_end_row;                 //last screen row of the terminal

    int terminal_rows;              //calculated from the numbers before           
    //int terminal_columns;

    // int  terminal_cursor_row;
    // int  terminal_cursor_column;

    int terminal_first_vrt_row;

    char lines_buffer[terminal_line_buffer_lenght][12];

    

};



extern int print(const char* str);
extern int print_r(const char* str, size_t len);
