[org 0x7C00]
BITS 16

%define ENDL  0X0d, 0x0a


jmp main


nl:
    
    mov si, newline
    call print
    
    ret


print:                 ;prints what is in si
    push si
    push ax

.print_loop:

    lodsb

    or al, al
    jz .print_done

    mov ah, 0x0e
    int 0x10
    jmp .print_loop


.print_done:
    pop ax
    pop si
    ret


main:

    mov ax, 0
    mov ds, ax
    mov es, ax


    call nl
    call nl
    call nl

    mov si, msg_ARGOS   ; welcome message
    call print

    call nl
    call nl


    mov si, msg
    call print

   






msg_ARGOS: db "         ArGOS", 0
msg: db "BOOTLOADER. OS booting start", ENDL,"benvenuti", 0

newline: db 10, 13, 0


.halt:
    jmp .halt

times 510 -  ($ - $$) db 0

db 0x55, 0xaa