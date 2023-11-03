
#include "libc_argos.h"
#include "screen.h"

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



void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size) {
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






const char hex_digits[16]= {'0', '1', '2', '3','4', '5', '6', '7','8', '9', 'A', 'B','C', 'D', 'E', 'F'};
const char dec_digits[10]= {'0', '1', '2', '3','4', '5', '6', '7','8', '9'};

#define number_str_buffer_lenght  30




char* int_strBASE(long long int n, int base ,char * strpf){

    //TODO implement negatives

    int c = 1;
    int n0 = n;

    const char* digits;

    char strpv[number_str_buffer_lenght];
    char *strp = &strpv[number_str_buffer_lenght];
    char *strp1 =  &strpv[0];
    strp[-1] = '\0';


    if (base == 10)
    {
        digits = &dec_digits[0];
		//screen_write("(dec)");
    }
    else if (base == 16)
    {
        digits = &hex_digits[0];
		screen_write("0x");

    }

    int g = -1;

    do
    {
        strp[g] = digits[n % base] ;

        n /= base;
        c++;

		//print_char(strp[g]);
        g--;


    } while (n>base);

    int i = 0;

    if (n % base != 0)
    {
        strp[g] =  digits[n % base];
	    //print_char(strp[g]);

        for (i; i <(c); i++)
        {
            strpf[i] = strp1[number_str_buffer_lenght-c+i];
        }

        strpf[i] = '\0';

    }
    else{
        //screen_write("one digit\n");
        //print_char(*strpf);

        strpf[0] = digits[n0 % base];
        strpf[1] = '\0';
    }
    
    //screen_write("\n\r");



    
    //screen_write("\n\r");

	//screen_write(strpf);
    return strpf;

}



void screen_printInt(long long int n, int b){

    char str[number_str_buffer_lenght];
    
    char *pstr = &str[0];

    int_strBASE(n,b ,pstr);

	screen_write(pstr);


	
}


void screen_printIntDec(long long int n){

    screen_printInt(n, 10);
    return;
}




void screen_printIntHex(long long int n){

    screen_printInt(n, 16);
    return;
}