db "KERNELARGOS"
;;;;ENTRY POINT TO THE KERNEL
[bits 32]

[extern ArGOS_MAIN]

[global _start]

extern __bss_start
extern __bss_end
section .text
_start:

;cli
;pop eax

mov esp, 0x7c00                 ;set up stack 
mov ebp, 0x7c00

mov edi, __bss_start            ;clears the bss
mov ecx, __bss_end
sub ecx, edi
mov al, 0
cld
rep stosb

cli                             ;disables interrupts because IDT isn't set yet
push esp
call ArGOS_MAIN               ;calls main function

mov ecx, 3


.endend:
jmp $
jmp .endend


