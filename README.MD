# ArGOS OPERATING SYSTEM


Fatto da Alberto Girardi, a San Vito, Friuli, Italia

Ad gloriam humanitatis

12/09/2023

GOAL: building an OS totally from scratch. Have fun along the way.
Learning assembly language, low level management of memory and execution, C language implementation and low level usage, kernel architectures and abstraction layers.

To be used on qemu, (booting as a flat binary for now).  
Totally insecure. Complete possibility of memory acces.  
in developement

[![wakatime](https://wakatime.com/badge/user/018b48bf-8d51-471d-b870-e93a045be5f7/project/018b48cb-4e1e-4b4e-b36b-06f53912c64f.svg)](https://wakatime.com/badge/user/018b48bf-8d51-471d-b870-e93a045be5f7/project/018b48cb-4e1e-4b4e-b36b-06f53912c64f)

## HOW TO COMPILE AND RUN and USE

#### REQUIREMENTS:
* nasm
* qemu
* make




compile:

    make

makefile targets:

    make tclean    ;deletes build directory
    make clean     ;deletes other tmp build files

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


### CURRENT PLAN

* keyboard input /
* reboot /
* reading disk and 2 stage bootloader/
* kernel loader
* cross compiler and c running
* asm c wrappers
* interrupts handling
* screen vga drivers
* printf
* hardware abstraction layer
* disk drivers
* keyboard drivers
