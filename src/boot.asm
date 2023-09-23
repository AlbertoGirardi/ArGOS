[org 0x7C00]
BITS 16

%define ENDL  0X0d, 0x0a


jmp main


nl:
    push si
    mov si, newline
    call print

    pop si
    
    ret


print:                 ;prints what is in si
    push si
    push ax

.print_loop:

    lodsb               ;load the content of si

    or al, al
    jz .print_done

    mov ah, 0x0e
    int 0x10
    jmp .print_loop


.print_done:     

       ; return
    pop ax
    pop si
    ret


print_digit: 


             ;print a single number value given in bh,
    push si
    push ax
    push bx

    mov bx, 48
    add si, bx
    
    mov ax, si

    mov ah, 0x0e
    int 0x10


    pop bx
    pop ax
    pop si

    ret
    


main:

    mov ax, 0
    mov ds, ax
    mov es, ax


    times 3 call nl

    mov si, msg_ARGOS   ; welcome message
    call print

    times 2 call nl

    mov si, msg
    call print

    times 2 call nl

    mov bx, 3


    mov si, 5
   
    call print_digit
    call nl
    mov si, bx 
    call print_digit

    


  

   






msg_ARGOS: db "                 ArGOS", 0
msg: db "BOOTLOADER. OS booting start", ENDL,"Benvenuti! Alcuni test in assembly",ENDL,0

newline: db 10, 13, 0



.halt:
  
   
    jmp .halt

times 510 -  ($-$$)  db 0

db 0x55, 0xaa