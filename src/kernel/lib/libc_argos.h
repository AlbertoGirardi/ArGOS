#pragma once


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str);

extern void* memmove(void* dstptr, const void* srcptr, size_t size);
extern int memcmp(const void* aptr, const void* bptr, size_t size);
extern void* memcpy(void*  dstptr, const void* restrict srcptr, size_t size);
extern void* memset(void* bufptr, int value, size_t size);

extern char* int_to_strBASE(long long int n, int base, char * strpf);
extern void int_to_stringDEC( long long int n, char* str);
extern void int_to_stringHEX( long long int n, char* str);


extern void screen_printIntDec(long long int n);
extern void screen_printIntHex(long long int n);

