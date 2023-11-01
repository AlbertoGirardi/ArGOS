db "aaaaaaa"
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

mov esp, 0x7c00
mov ebp, 0x7c00

mov edi, __bss_start            ;clears the bss
mov ecx, __bss_end
sub ecx, edi
mov al, 0
cld
rep stosb

cli
push ss
call ArGOS_MAIN               ;calls main function



.endend:
jmp $
jmp .endend
