# COMPILATION FLOW:



## CROSS COMPILER: i686-elf
using gcc for compilation and linking



## C COMPILATION flgas:

i686-elf-gcc

| flag| meaning |
|----------|----------|
--freestanding |freestanding c environment     
-m32 | 32 bit output, not really necessary
-g | debug symbols
-mno-red-zone | stack protection 

## LINKING FLAGS

i686-elf-gcc

| flag| meaning |
|----------|----------|
-nostdlib | not linking to standard lib
s-Wl,--oformat=binary| output format binary
-Ttext 0x1000|  basic linking information, where to put .text section
-lgcc| linking with libgcc
