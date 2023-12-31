# ArGOS OPERATING SYSTEM


Fatto da Alberto Girardi, a San Vito, Friuli, Italia

Ad gloriam humanitatis

12/09/2023

GOAL: building an OS totally from scratch. Have fun along the way.
Learning assembly language, low level management of memory and execution, C language implementation and low level usage, kernel architectures and abstraction layers.

To be used on qemu, (booting as a flat binary for now).  
Totally insecure. Complete possibility of memory acces.  
in developement

Initial inspiration spark: [jdh's "Tetris OS"](https://www.youtube.com/watch?v=FaILnmUYS_U). First steps following [nanobyte OS](https://www.youtube.com/watch?v=9t-SPC7Tczc&list=PLFjM7v6KGMpiH2G-kT781ByCNC_0pKpPN&index=1) and [Making an OS (x86)](https://www.youtube.com/watch?v=MwPjvJ9ulSc&list=PLm3B56ql_akNcvH8vvJRYOc7TbYhRs19M)  
Extrely useful information from [osdev.org](https://wiki.osdev.org/Main_Page)

[![wakatime](https://wakatime.com/badge/user/018b48bf-8d51-471d-b870-e93a045be5f7/project/018b48cb-4e1e-4b4e-b36b-06f53912c64f.svg)](https://wakatime.com/badge/user/018b48bf-8d51-471d-b870-e93a045be5f7/project/018b48cb-4e1e-4b4e-b36b-06f53912c64f)

## HOW TO COMPILE AND RUN and USE

#### REQUIREMENTS:
* i686-elf cross compiler, GNU gcc and ld, with libgcc
* nasm
* qemu
* make




compile:

    make

makefile targets:

    make tclean    ;deletes build directory
    make clean     ;deletes other tmp build files, only final image remains
    make recomp    ;tclean and then compiles
    make odump     ;objdump of all .o files

boot:

    make run



reboot from inside: press "r"


## DOCUMENTATION

[doc file](doc/ARCHITECTURE_DESIGN.MD)  
[execution controll](doc/Execution_flow.md)


## HISTORY LOG


* FIRST CRUDE BOOTLOADER TEST: 12/09/2023 23:04
* in the following weeks
* first function: 21/9/2023
* print function, loops, arithmetic functions tests, playing around,  end of asm tests 2 22/09/2023
* function that prints a decimal number 24/09/2023
* Understanding of asm memory model, stack
* passing function argument to the stack 29/09/2023
* getting user input via keyboard 05/09/2023
* rebooting
* reading from the disk (crude test 14/10/2023)
* read from disk and load to memory function and stage 2 bootloader: 15/10/2023
* ENTER 32 BIT MODE (gdt, new segments)  19/10/2023
* 32 bit coding in the following days, reimplementing old functions
* c kernel working 25/10/2023
* kernel lib linking    
* vga drivers   27/10/2023
* problems with global variables
* problem solved 2/11/2023
* implemented integer and hex printing function 3/11/2023


### CURRENT PLAN

1. printf
2. terminal and scrolling, changing vga mode
3. interrupts

* keyboard input /
* reboot /
* reading disk and 2 stage bootloader/
* kernel loader/
* cross compiler and c running/
* asm c wrappers
* interrupts handling
* screen vga drivers/
* screen management/
* printf
* hardware abstraction layer
* disk drivers
* keyboard drivers
