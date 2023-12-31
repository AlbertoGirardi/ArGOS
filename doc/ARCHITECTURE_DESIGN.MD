# GENERAL ARCHITECTURE

### boot.asm
1st sector
boots the system from the bios, then loads the rest and gives control to bootlaoder 2 (includes final routines for restarting)


#### DISK READING AND LOADING
Loads as many sectors as required at 0x7e00 (after the first sector)


#### Memory map

    (IVT and BIOS)
    .... 
    STACK
    0x7C00: bootloader
    ....
    0x7E00: second stage
    ....
    0x9000: kernel loaded here
    ....
    0x9FC00:start of bios data area (NOT OVERWRITE)


2 ways for memory loading to fail(fail mode indicated in error message)

* error in the disk (cf flag or number of sectors asked higher than anctual sectors)    (A)

* sectors asked too low, not everything loaded, control varible not loaded and detected by stage 1 (load_check = 3571)  (B)


only 1st sector





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

## GENERAL RULES:

 


### CALLING CONVENTION CDECL



pushing args from right to left

   All pushed to the stack is 32 bit
    So are function related stuff (return address, params)



function(arg1, arg2, arg3)

caller:

    push arg3
    push arg2
    push arg1
    call function

.


    bottom
    ...                            bp+4+4*n_param

    parameter 3                    bp+16
    parameter 2                    bp+12
    parameter 1                    bp+8
    return address                 bp+4
    old bp                         bp=0
    locals                         bp-4
    ...
    top


returning:

         ret 2*arg_num   ;return popping also all args


## GDT MEMORY SEGMENTS:

* code segment:  all the memory
* data segment:  all the memory

This nullfies the effects of the obsolete GDT, letting us access all the memory as if we were in 16 bit mode. Memory protection will be made with paging.


# VIDEO MEMORY
80 char lenght


2 bytes for each character

HIGH<-------<---------<----------LOW                               

| Header 1 | Header 2 | Header 3 |
|:--------:|:--------:|:--------:|
| 8 bits   | 4 bits   | 4 bits  |
| ASCII code  | background col  | char color   |

## \ escape sequences
for low level \n only does "line feed", \r is required for having a new line

at higher level (printf), \n is translated into \n\r





#### COLORS:
<table class="wikitable">
<tbody><tr>
<th>Dec
</th>
<th>Hex
</th>
<th>Binary
</th>
<th colspan="2">Color
</th></tr>
<tr>
<td>0
</td>
<td>0
</td>
<td><kbd>0000</kbd>
</td>
<td>Black
</td>
<td style="background-color: #000000">
</td></tr>
<tr>
<td>1
</td>
<td>1
</td>
<td><kbd>0001</kbd>
</td>
<td>Blue
</td>
<td style="background-color: #0000AA">
</td></tr>
<tr>
<td>2
</td>
<td>2
</td>
<td><kbd>0010</kbd>
</td>
<td>Green
</td>
<td style="background-color: #00AA00">
</td></tr>
<tr>
<td>3
</td>
<td>3
</td>
<td><kbd>0011</kbd>
</td>
<td>Cyan
</td>
<td style="background-color: #00AAAA">
</td></tr>
<tr>
<td>4
</td>
<td>4
</td>
<td><kbd>0100</kbd>
</td>
<td>Red
</td>
<td style="background-color: #AA0000">
</td></tr>
<tr>
<td>5
</td>
<td>5
</td>
<td><kbd>0101</kbd>
</td>
<td>Magenta
</td>
<td style="background-color: #AA00AA">
</td></tr>
<tr>
<td>6
</td>
<td>6
</td>
<td><kbd>0110</kbd>
</td>
<td>Brown
</td>
<td style="background-color: #AA5500">
</td></tr>
<tr>
<td>7
</td>
<td>7
</td>
<td><kbd>0111</kbd>
</td>
<td>Light Gray
</td>
<td style="background-color: #AAAAAA">
</td></tr>
<tr>
<td>8
</td>
<td>8
</td>
<td><kbd>1000</kbd>
</td>
<td>Dark Gray
</td>
<td style="background-color: #555555">
</td></tr>
<tr>
<td>9
</td>
<td>9
</td>
<td><kbd>1001</kbd>
</td>
<td>Light Blue
</td>
<td style="background-color: #5555FF">
</td></tr>
<tr>
<td>10
</td>
<td>A
</td>
<td><kbd>1010</kbd>
</td>
<td>Light Green
</td>
<td style="background-color: #55FF55">
</td></tr>
<tr>
<td>11
</td>
<td>B
</td>
<td><kbd>1011</kbd>
</td>
<td>Light Cyan
</td>
<td style="background-color: #55FFFF">
</td></tr>
<tr>
<td>12
</td>
<td>C
</td>
<td><kbd>1100</kbd>
</td>
<td>Light Red
</td>
<td style="background-color: #FF5555">
</td></tr>
<tr>
<td>13
</td>
<td>D
</td>
<td><kbd>1101</kbd>
</td>
<td>Light Magenta
</td>
<td style="background-color: #FF55FF">
</td></tr>
<tr>
<td>14
</td>
<td>E
</td>
<td><kbd>1110</kbd>
</td>
<td>Yellow
</td>
<td style="background-color: #FFFF55">
</td></tr>
<tr>
<td>15
</td>
<td>F
</td>
<td><kbd>1111</kbd>
</td>
<td>White
</td>
<td style="background-color: #FFFFFF">
</td></tr>


#### Segment selectors
08h -> protected mode code segment to jump to       CODE_SEGMENT
10h -> data segment, set  ds, es, ss to this        DATA_SEGMENT




###  SOME COMMANDS



to graph log

```
git log --graph --abbrev-commit --decorate --format=format:'%C(bold blue)%h%C(reset) - %C(bold green)(%ar)%C(reset) %C(white)%s%C(reset) %C(dim white)- %an%C(reset)%C(auto)%d%C(reset)' --all
lg2 = log --graph --abbrev-commit --decorate --format=format:'%C(bold blue)%h%C(reset) - %C(bold cyan)%aD%C(reset) %C(bold green)(%ar)%C(reset)%C(auto)%d%C(reset)%n''          %C(white)%s%C(reset) %C(dim white)- %an%C(reset)
```



to compile c

i686-elf-gcc --freestanding -m32 -g -c test.c -o test.o
  
    
      



<table border="2" cellpadding="4" cellspacing="0" style="margin-top:1em; margin-bottom:1em;; border:1px #aaa solid; border-collapse:collapse; &#123;&#123;&#123;1}}}">

<tr>
<th> start
</th>
<th> end
</th>
<th> size
</th>
<th> description
</th>
<th colspan="2"> type
</th></tr>
<tr>
<th colspan="6"> Real mode address space (the first MiB)
</th></tr>
<tr>
<td> 0x00000000
</td>
<td> 0x000003FF
</td>
<td> 1 KiB
</td>
<td> Real Mode IVT (Interrupt Vector Table)
</td>
<td rowspan="2"> unusable in real mode
</td>
<td rowspan="6"> 640 KiB RAM ("Low memory")
</td></tr>
<tr>
<td> 0x00000400
</td>
<td> 0x000004FF
</td>
<td> 256 bytes
</td>
<td> BDA (BIOS data area)
</td></tr>
<tr>
<td> 0x00000500
</td>
<td> 0x00007BFF
</td>
<td> 29.75 KiB
</td>
<td> Conventional memory
</td>
<td rowspan="3"> usable memory
</td></tr>
<tr>
<td> 0x00007C00
</td>
<td> 0x00007DFF
</td>
<td> 512 bytes
</td>
<td> Your OS BootSector
</td></tr>
<tr>
<td> 0x00007E00
</td>
<td> 0x0007FFFF
</td>
<td> 480.5 KiB
</td>
<td> Conventional memory
</td></tr>
<tr>
<td> 0x00080000
</td>
<td> 0x0009FFFF
</td>
<td> 128 KiB
</td>
<td> EBDA (Extended BIOS Data Area)
</td>
<td> partially used by the EBDA
</td></tr>
<tr>
<td> 0x000A0000
</td>
<td> 0x000BFFFF
</td>
<td> 128 KiB
</td>
<td> Video display memory
</td>
<td> hardware mapped
</td>
<td rowspan="4"> 384 KiB System / Reserved ("Upper Memory")
</td></tr>
<tr>
<td> 0x000C0000
</td>
<td> 0x000C7FFF
</td>
<td> 32 KiB (typically)
</td>
<td> Video BIOS
</td>
<td rowspan="3"> ROM and hardware mapped / Shadow RAM
</td></tr>
<tr>
<td> 0x000C8000
</td>
<td> 0x000EFFFF
</td>
<td> 160 KiB (typically)
</td>
<td> BIOS Expansions
</td></tr>
<tr>
<td> 0x000F0000
</td>
<td> 0x000FFFFF
</td>
<td> 64 KiB
</td>
<td> Motherboard BIOS
</td></tr></table>