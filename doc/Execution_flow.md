# EXECUTION FLOW DURING BOOTING 


## 16 BITS Real Mode
BIOS loads stage1

stage1 loads stage2, and stage 3
stage 2 performs tests and SWITCHES TO PROTECTED MODE

stage2:                                
* sets up GDT
* jumps to STAGE 3


## 32 BITS Protected Mode

stage 3 performs tests and jumps to kernel code





kenel loader: loads kernel and jumps to it


# MEMORY


    (IVT and BIOS)
    .... 
    STACK
    0x7C00: bootloader
    ....
    0x7E00: second stage and tird stage
    0x8400: kernel loader
    ....
    ....
    ....
    ....
    0x9FC00:start of bios data area (NOT OVERWRITE)