



;;;SECOND STAGE OF THE BOOTLOADER,  




B32:

    push 351

    call print_number
    call nl

    mov si, [var]
    push si

    call print_number


jmp CLOSURE