#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "libc_argos.h"
#include "screen.h"
#include "stdio.h"


size_t strlen(const char* str){

    size_t len = 0;

    while (str[len])
    {
        len ++;
    }
    
    return len;
}



/* mem functions implementations from OSDEV meaty skeleton*/

 
void* memmove(void* dstptr, const void* srcptr, size_t size) {

/*SAFELY moves data in memory from source to destination*/

	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	if (dst < src) {
		for (size_t i = 0; i < size; i++)
			dst[i] = src[i];
	} else {
		for (size_t i = size; i != 0; i--)
			dst[i-1] = src[i-1];
	}
	return dstptr;
}

 
int memcmp(const void* aptr, const void* bptr, size_t size) {
	const unsigned char* a = (const unsigned char*) aptr;
	const unsigned char* b = (const unsigned char*) bptr;
	for (size_t i = 0; i < size; i++) {
		if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
	}
	return 0;
}



void* memcpy(void*  dstptr, const void* restrict srcptr, size_t size) {
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}


void* memset(void* bufptr, int value, size_t size) {
	unsigned char* buf = (unsigned char*) bufptr;
	for (size_t i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;
}


int get_esp(void);




//character lists for hex and decimal
const char hex_digits[16]= {'0', '1', '2', '3','4', '5', '6', '7','8', '9', 'A', 'B','C', 'D', 'E', 'F'};
const char dec_digits[10]= {'0', '1', '2', '3','4', '5', '6', '7','8', '9'};





char* int_to_strBASE(long long int n, int base, char * strpf){

/*from a integer n puts into the given pointer a string that is the rappresentation of the integer in the given base, if it is supported
currently supports decimal, hex*/

    bool isneg = false;

    if (n<0)                            //if number is negative flip it 
    {
        n = -n;
        isneg = true;
    }
    

    int len = 1;
    long long n0 = n;                       //stores initial numbers

    const char* digits;

    char strpv[number_str_buffer_lenght];       //buffer for string 
    char *strp = &strpv[number_str_buffer_lenght];          //pointer to the end of the string
    char *strp1 =  &strpv[0];                               //pointer to the start of the buffer
    strp[-1] = '\0';


    if (base == 10)                         //select correct set of digits (useless but i wrote it )
    {
        digits = &dec_digits[0];
		//screen_write("(dec)");
    }
    else if (base == 16)
    {
        digits = &hex_digits[0];
		//screen_write("0x");

    }

    else
    {
        screen_werror("\n\rbase not supported!only 10 and hex\n\r");
        return strpf;
    }
    

    int g = -1;

    do
    {

        //* * DIVISION ALGORITHM TO GET AND STORE the digits of the numbers

        strp[g] = digits[n % base] ;

        n /= base;
        len++;      //lengt of the string

		//print_char(strp[g]);
        g--;                //magic pointer


    } while (n>=base);

        //screen_write("\n\r");


    int i = 0;

    if (isneg)                  //if is negative append - to the start
    {
        strpf[i] = '-';
        i++;
        len++;
        
    }
    

    if (n0>(base-1))                            //* * REVERSES THE ORDER OF THE STRING
    {
        //print_char(n+48);
        strp[g] =  digits[n % base];                // adds last digit
	    //print_char(strp[g]);
        //screen_write("\n\r");
        for (i; i <(len); i++)
        {
            strpf[i] = strp1[number_str_buffer_lenght-len+i];
            //print_char(strpf[i]);

        }

       // screen_write("\n\r");

        strpf[i] = '\0';

    }
    else{
        // if there is only one digit

        //screen_write("one digit\n");
        //print_char(*strpf);

        strpf[i] = digits[n0 % base];
        i++;
        strpf[i] = '\0';
    }
    
    //screen_write("\n\r");
	//screen_write(strpf);

    if (base == 16)     //puts 0x before hex strings
    {
        memmove(strpf+2, strpf, number_str_buffer_lenght-2);
        strpf[0]= '0';
        strpf[1]= 'x';
        

    }
    

    return strpf;

}




void int_to_stringDEC( long long int n, char* str){

    /*
    makes the given string pointer point to a string with the given number in base 10
    */

    int_to_strBASE(n,10 ,str);


}




void int_to_stringHEX( long long int n, char* str){

    /*
    makes the given string pointer point to a string with the given number in base 16
    */

   if (n<0)     
   {
    screen_werror("\n\rcant't print negative hex\n\r");
   }
   
   else
   {
    int_to_strBASE(n,16 ,str);
    
   }
   

}



void   teststack(void){


    char al[] = "xabcdefghijklmnopqrstuvwxyz";
    char *alp = &al[0];

    for (int i = 0; i < strlen(al); i++)
    {
        print_char(*(al+i));
    }

    
    screen_write("\n\r");

}




void print_esp(){


    //prints the value of the ESP

    int espv = get_esp();

    screen_printIntHex(espv);
    screen_write("\n\r");
    return;
}



/*

* * ASM FUNCTIONS TO INTERFACE WITH PORTS

from kernel dev guide of jamesmolloy

*/


void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8_t inb(uint16_t port)
{
   uint8_t ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

uint16_t inw(uint16_t port)
{
   uint16_t ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}