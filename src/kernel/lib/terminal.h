#pragma once


struct terminal
{
    int start_row;
    int end_row;

    int terminal_rows;
    int terminal_columns;

    int  terminal_cursor_row;
    int  terminal_cursor_column;

    

};



extern int print(const char* str);
extern int print_r(const char* str, size_t len);
