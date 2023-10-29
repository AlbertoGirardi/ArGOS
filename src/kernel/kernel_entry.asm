;db "aaaaaaa"
;;;;ENTRY POINT TO THE KERNEL
[bits 32]

[extern main]

[global _start]

_start:

;cli
;pop eax

mov esp, 0x7c00


call main               ;calls main function

cli

.endend
jmp $
jmp .endend

