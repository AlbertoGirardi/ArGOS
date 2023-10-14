



;;;SECOND STAGE OF THE BOOTLOADER,  


var2: dw 7653
var3: dw 7654
var4: dw 7655


B32:


    mov si, [var]
    push si

    call print_number

    call nl

    mov si, [var2]
    push si

    call print_number
    call nl

    mov si, [var2+2]
    push si

    call print_number
     call nl

    mov si, [var2+4]
    push si

    call print_number



jmp CLOSURE