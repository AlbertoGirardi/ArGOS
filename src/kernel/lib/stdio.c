#include "stdio.h"
#include "libc_argos.h"

void screen_printIntDec(long long int n){

    char str[number_str_buffer_lenght];
    
    char *pstr = &str[0];

    int_to_stringDEC(n,pstr);

	screen_write(pstr);


	
}





void screen_printIntHex(long long int n){

    char str[number_str_buffer_lenght];
    
    char *pstr = &str[0];

    int_to_stringHEX(n,pstr);

	screen_write(pstr);

}