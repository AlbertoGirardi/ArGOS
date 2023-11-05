[bits 32]
[global get_esp]

db "ASMLIBS!"

;function that returns stack pointer
get_esp:

    mov eax, esp
    ret