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






//defining states for the printf state machine

//states for printing
#define printf_normal 0
#define printf_lenght 2
#define printf_specifier 1

//states for lenght selection
#define printf_num_int 0
#define printf_num_long 1
#define printf_num_longlong 2






int printf(const char *fmt, ...)
{

/*
IMPLEMENTATION OF PRINTF FUNCTION by Alberto Girardi

supported features: 
    - lenght selections for intger: long and long long (l and ll)
    -x, X, d, c, s specifiers
    x only uppercase hex


    returns the number of characters written, 
* * INCLUDING \n and \r and such!

*/

    va_list ap;                                 //gets parameters list

    va_start(ap, fmt);

    int written = 0;                        //char written
    int state = printf_normal;              //printing state
    int num_print_state = printf_num_int;   //number printning state
    bool go_on = false;                     //go on to the next character to print (used when there is info before type specifier to keep looping and)

    while (*fmt != '\0')                    //if the string isn't ended
    {

        go_on = false;

        if (*fmt == '%')                    //if % go into lenght state, looking for it
        {
            state = printf_lenght;
            fmt++;
        }

        while (!go_on)                      //if going from lenght to type specifier don't return to the main loop
        {
            
        switch (state)
        {

        case printf_lenght:                //get info about lenght of the intefer

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

            state= printf_specifier;                    //go into printing state
            break;

        case printf_specifier:                          //look for type specifier
            int skip = 0;

            while (*fmt)
            {
                // printf("FMTDET");
                switch (*fmt)
                {
                case 'c':
                    
                    //print a character
                    char c = (char)va_arg(ap, int);
                    print_r(&c, 1);
                    written++;
                    skip++;
                    break;

                case 's':

                    //print a string
                    const char *stringp = va_arg(ap, const char *);
                    size_t slen = strlen(stringp);

                    print_r(stringp, slen);
                    written += slen;
                    skip++;
                    break;

                case 'd':

                    //prints an integer in decimal rappresentation
                    char strint[number_str_buffer_lenght];
                    memset(strint, 0, number_str_buffer_lenght);            //prepare buffer string of appropriate lenght and zero it out
                    char *pstr = &strint[0];

                    switch (num_print_state)                    //depending on the required lenght
                    {

                    case printf_num_int:                        //print int
                        int integer = va_arg(ap, int);   
                        int_to_stringDEC(integer, pstr);

                        break;
                    case printf_num_long:                       //long
                        long integerl = va_arg(ap, long);
                        int_to_stringDEC(integerl, pstr);
                        break;
                    case printf_num_longlong:                   //long long
                        long long integerll = va_arg(ap, long long);   
                        int_to_stringDEC(integerll, pstr);

                        break;
                    default:
                        break;
                    }


                    slen = strlen(pstr);
                    print_r(pstr, slen);
                                                            //print the rappresentation of the number
                    written += slen;                        
                    skip++;

                    break;

                case 'X':                   //PRINTS hex number
                    //continues to the x case
                case 'x':                     //like d but for hex

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

                    slen = strlen(pstrx);
                    print_r(pstrx, slen);
                    written += slen;
                    skip++;

                    break;

                case '%':                   //if %% in the string print %

                    print_r("%", 1);
                    skip++;
                    written++;
                    break;

                default:
                    break;
                }

                fmt++;
                if (skip)
                {
                    break;          //get of the specifier lookuing state and return to normale
                }
            }
            state = printf_normal;
            go_on = true;
            break;


        case printf_normal:             //print a character from the fmt string

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
    terminal_draw_buffer();

    return written;                 //return amout of written chars
}


