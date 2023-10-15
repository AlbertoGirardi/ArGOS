

;;;SECOND STAGE OF THE BOOTLOADER,  

msg_welcome2: db ENDL, "STAGE 2 OF THE BOOTLOADER", ENDL,"Benvenuti! Alcuni test in assembly",ENDL, ENDL ,0


BOOTLOADER32:                       ;second stage entry point

    mov si, msg_welcome2
    call print


    var:dd 12
    var2: dd 12
    var3:dd 12



    mov ax, var
    push ax
    call print_number
    call nl


    
    mov ax, var2
    push ax
    call print_number
    call nl


    
    mov ax, var3
    push ax
    call print_number
    call nl


jmp CLOSURE

times 2048 db 0

load_check: dw 3571                     ;MUST STAY AT THE END OF THE PROGRAM to check if everything is loaded

times 1024 db 0