#include "terminal.h"
#include "screen.h"



int print(char* str){

    /*currently wrapper for screen write*/


    int written = screen_write(str);

    return written;
}