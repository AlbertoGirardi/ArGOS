# ArGOS OPERATING SYSTEM


Fatto da Alberto Girardi, a San Vito, Friuli, Italia

Ad gloriam humanitatis

12/09/2023

GOAL: building an OS totally from scratch. Have fun along the way.
Learning assemblt language, low level management of memory and execution.

To be used on qemu, (booting as a flat binary for now) Totally insecure. Complete possibility of memory acces.
in developement


## HOW TO COMPILE AND RUN and USE

#### REQUIREMENTS:
* nasm
* qemu
* make




compile:

    make

makefile targets:

    make totclear  ;deletes build directory

boot:

    make run

reboot from inside: press "r"

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


### CURRENT PLAN

* keyboard input /
* reboot /
* reading disk and 2 stage bootloader
* cross compiler and c running