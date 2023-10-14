



;;;SECOND STAGE OF THE BOOTLOADER,  


var2: dw 7653

B32:


    mov si, [var]
    push si

    call print_number

    call nl

    mov si, [var2]
    push si

    call print_number



jmp CLOSURE