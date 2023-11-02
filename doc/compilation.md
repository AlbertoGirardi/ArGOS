# COMPILATION FLOW:
The flat binary disk image is formed by two parts that are stiched together with cat, with no connection between each other except hardcoded
binary address.

### 1ST PART: BOOTLOADER
all before kernel entry. Asm files stiched together and then assembled.

### 2ND PART: KERNEL

kernel: kernel entry, main and libs, compiled and linked together

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
