# GENERAL ARCHITECTURE

### boot.asm
1st sector
boots the system from the bios, then loads the rest and gives control to bootlaoder 2 (includes final routines for restarting)


#### DISK READING AND LOADING
Loads as many sectors as required at 0x7e00 (after the first sector)


Memory:

    (IVT and BIOS)
    .... 
    STACK
    0x7C00: bootloader
    ....
    0x7E00: second stage
    ....
    0x9FC00:start of bios data area (NOT OVERWRITE)


2 ways for memory loading to fail:

* error in the disk (cf flag or number of sectors asked higher than anctua sectors)

* sectors asked too low, not everything loaded, control varible not loaded and detected by stage 1 (load_check = 3571)


only 1st sector




### boot32.asm
Second stage of the bootloader

switches to protected mode
loads the kernel and calls it

### kernel
os kernels


# REAL MODE 16 BITS


## COMPILING

Stiches together stage 1 and 2 bootloader, then assembles them and coverts to .iso



## MEMORY MODEL

tiny memory model:

     SS = DS = ES = 0

stack starts at 0x7c00 (and grows downwards as usal)


### GLOBAL ALLOCATION
Be CAREFUL to allocate the exact amount of bytes, if used 16 bit register alloccate a word, not a byte

dw 123    ; 16 bit integer


## ASM CALLING CONVENTION: 

temp: si parameter register


### CALLEE CLEANUP

0. parameters pushed on the stack before calling(from LEFT to right) 

1. bp saved in the stack

2. parameters accessed using [bp-offset]

3. old bp popped

4. return, dropping the parameters added (ret [num of bytes of parmeteres])

#### STACK EXAMPLE

    bottom
    ...                            bp+4+2*n_param

    parameter 1                    bp+8
    parameter 2                    bp+6
    parameter 3                    bp+4
    return address                 bp+2
    old bp                         bp=0
    locals                         bp-2
    ...
    top


#### function snippet

function(arg1, arg2, arg3)

caller:

    push arg1
    push arg2
    push arg3
    call function


callee:

    function:

        push bp
        mov bp, sp      ;calling convention: saving old bp and setting new one to start of function
        pusha           ;save all regs to stack

        ;;; DO STUFF

        jmp function_end
   



    function_end:
        popa            ;reload all saved regs from stack
        pop bp          ;restore bp to last saved value

        ret 2*arg_num   ;return popping also all args





# PROTECTED MODE 32 BITS








to graph log

```
git log --graph --abbrev-commit --decorate --format=format:'%C(bold blue)%h%C(reset) - %C(bold green)(%ar)%C(reset) %C(white)%s%C(reset) %C(dim white)- %an%C(reset)%C(auto)%d%C(reset)' --all
lg2 = log --graph --abbrev-commit --decorate --format=format:'%C(bold blue)%h%C(reset) - %C(bold cyan)%aD%C(reset) %C(bold green)(%ar)%C(reset)%C(auto)%d%C(reset)%n''          %C(white)%s%C(reset) %C(dim white)- %an%C(reset)
```



