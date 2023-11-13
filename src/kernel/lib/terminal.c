#include "stdint.h"
#include <stdbool.h>
#include <stddef.h>
#include "stdarg.h"

#include "terminal.h"
#include "screen.h"



char rrrr[] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";


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
