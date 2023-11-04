## [vga driver](../src/kernel/lib/vga_driver.c):

Low level management of the vga hardware mapped memory, function to print a chat at cursor pos.
Abstracts away touching memory

## [screen management](../src/kernel/lib/screen.c)

Manages screen, printing strings, managing lines, blanking screen

## terminal
manages the terminal part of the screen, scrolling and saving old lines, 

printf has effect only on the terminal, but fprintf can be used everywhere


## [general use c functions](../src/kernel/lib/libc_argos.c)

Function that usually one would find in libc (like stdio, stdlib), but have to be rewritten in a freestanding environment