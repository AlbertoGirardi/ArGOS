#include "stdint.h"
#include <stdbool.h>
#include <stddef.h>
#include "stdarg.h"


#include "stdio.h"
#include "libc_argos.h"
#include "screen.h"
#include "terminal.h"





void screen_printIntDec(long long int n){

    /*prints a number in decimal rappresentation*/

    char str[number_str_buffer_lenght];
    
    char *pstr = &str[0];

    int_to_stringDEC(n,pstr);

	screen_write(pstr);


	
}





void screen_printIntHex(long long int n){

    /*prints a given number in hex rapresentation, only if it is positive*/

    char str[number_str_buffer_lenght];
    
    char *pstr = &str[0];

    int_to_stringHEX(n,pstr);

	screen_write(pstr);

}








#define printf_normal 0
#define printf_lenght 2
#define printf_specifier 1

#define printf_num_int 0
#define printf_num_long 1
#define printf_num_longlong 2






int printf(const char *fmt, ...)
{

    va_list ap;

    va_start(ap, fmt);
    int written = 0;

    int state = printf_normal;
    int num_print_state = printf_num_int;
    bool go_on = false;

    while (*fmt != '\0')
    {

        go_on = false;

        if (*fmt == '%')
        {
            state = printf_lenght;
            fmt++;
        }

        while (!go_on)
        {
            
        switch (state)
        {

        case printf_lenght:

            switch (*fmt)
            {
            case 'l':

                num_print_state = printf_num_long;
                fmt++;

                if (*fmt == 'l')
                {
                    fmt++;
                    num_print_state = printf_num_longlong;

                }
                
                break;
            
            default:
                //if no lenght is specified do nothing
                break;
            }

            state= printf_specifier;
            break;

        case printf_specifier:
            int skip = 0;

            while (*fmt)
            {
                // printf("FMTDET");
                switch (*fmt)
                {
                case 'c':

                    char c = (char)va_arg(ap, int);
                    print_r(&c, 1);
                    written++;
                    skip++;
                    break;

                case 's':

                    const char *stringp = va_arg(ap, const char *);
                    size_t slen = strlen(stringp);

                    print_r(stringp, slen);
                    written += slen;
                    skip++;
                    break;

                case 'd':


                    char strint[number_str_buffer_lenght];
                    memset(strint, 0, number_str_buffer_lenght);
                    char *pstr = &strint[0];

                    switch (num_print_state)
                    {

                    case printf_num_int:
                        int integer = va_arg(ap, int);   
                        int_to_stringDEC(integer, pstr);

                        break;
                    case printf_num_long:
                        long integerl = va_arg(ap, long);
                        int_to_stringDEC(integerl, pstr);
                        break;
                    case printf_num_longlong:
                        long long integerll = va_arg(ap, long long);   
                        int_to_stringDEC(integerll, pstr);

                        break;
                    default:
                        break;
                    }


                    print_r(pstr, strlen(pstr));
                    written += slen;
                    skip++;

                    break;

                case 'x':

                    char strintx[number_str_buffer_lenght];
                    char *pstrx = &strintx[0];

                    switch (num_print_state)
                    {

                    case printf_num_int:
                        int integerx = va_arg(ap, int);   
                        int_to_stringHEX(integerx, pstrx);

                        break;
                    case printf_num_long:
                        long integerlx = va_arg(ap, long);
                        int_to_stringHEX(integerlx, pstrx);
                        break;
                    case printf_num_longlong:
                        long long integerllx = va_arg(ap, long long);   
                        int_to_stringHEX(integerllx, pstrx);

                        break;
                    default:
                        break;
                    }


                    print_r(pstrx, strlen(pstrx));
                    written += slen;
                    skip++;

                    break;

                case '%':

                    print_r("%", 1);
                    skip++;
                    break;

                default:
                    break;
                }

                fmt++;
                if (skip)
                {
                    break;
                }
            }
            state = printf_normal;
            go_on = true;
            break;


        case printf_normal:

            if (*fmt == '\n')
            {
                print_r(fmt, 1);
                
                char* carriage_r;
                *carriage_r = '\r';
                print_r(carriage_r,1);
            }

            else
            {
                print_r(fmt, 1);
                
            }
            fmt++;
            written++;
            go_on = true;

            break;

        default:
            break;
        }
        }
        

    }

    va_end(ap);
    return written;
}


