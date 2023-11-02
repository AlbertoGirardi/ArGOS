
#include "libc_argos.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


size_t strlen(const char* str){

    size_t len = 0;

    while (str[len])
    {
        len ++;
    }
    
    return len;
}
