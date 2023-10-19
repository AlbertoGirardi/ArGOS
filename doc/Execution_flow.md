# EXECUTION FLOW DURING BOOTING 


## 16 BITS Real Mode
BIOS loads stage1

stage1 loads stage2, kernel loader and kernel into the first meg, after the first sector

## 32 BITS Protected Mode

stage2:                                 [TO DO]
* sets up GDT
* jumps to kenrel loader

kenel loader: loads kernel and jumps to it


# MEMORY


    (IVT and BIOS)
    .... 
    STACK
    0x7C00: bootloader
    ....
    0x7E00: second stage
    ....
    0x9FC00:start of bios data area (NOT OVERWRITE)