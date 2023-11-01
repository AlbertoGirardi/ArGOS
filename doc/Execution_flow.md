# EXECUTION FLOW DURING BOOTING 


## 16 BITS Real Mode


### STAGE 1: boot.asm
* BIOS loads stage1
* stage1 loads stage2
* jumps to stage 2

## STAGE 2: boot2.asm

* performs tests on a20 line
* loads to ram stage 3 and kernel (currently 60 sectors, until 0x7800)  
* loads gdt
* SWITCHES TO PROTECTED MODE
* jumpes to 32 bit code 3 stage



## 32 BITS Protected Mode

#### STAGE 3: boot32.asm
* stage 3 performs tests on A20 line
* sets up segments registers to the data segment selector of the GDT
* and jumps to kernel entry code


kernel entry: file linked with the kernel, jumps to the kernel main function
#### kernel entry: kernel_entry.asm
*   clears bss
* sets up stack to 0x7c00

#### KERNEL: Argos_kernel.c

loads the libs (drives)


# MEMORY


    (IVT and BIOS)
    .... 
    STACK
    0x7C00: bootloader
    ....
    0x7E00: second stage and tird stage
    ....
    0x8c00: kernel loader
    ....
    ....
    ....
    ....
    0x9FC00:start of bios data area (NOT OVERWRITE)


everything is in the first MEG of memory to avoid using disk drivers, because we can only load memory in 16 bit mode, and there the max memory addressable is 1 meg. We still have ~600 kb of memory, plenty enough, and around ~20 k for the stack


the disk is a binary image. 

1) The first part is a single continuos asm file output, formed from stiching together the /boot files. All labels from each file are accessible in each other (attention not to call 16 bit function from 32 bit mode)  
STICHED TOGETHER TO (with cat and 0s spacing)
2) KERNEL:EVERYTHING LIKED TOGETHER, entry, main and libs
3) 0s at the end for padding

