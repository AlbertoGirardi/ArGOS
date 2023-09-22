[org 0x7C00]
BITS 16

jmp main

nl:
    
    mov ah, 0x0e
    mov al, 10
    int 0x10

    mov ah, 0x0e
    mov al, 13
    int 0x10
    
    ret


print:                 ;prints what is in ch
    mov ah, 0x0e
    mov al, cl
    int 0x10
    
    ret


main:


    mov ah, 0x0e
    mov al, 'A'
    int 0x10

    mov ah, 0x0e
    mov al, 'r'
    int 0x10

    mov ah, 0x0e
    mov al, 'G'
    int 0x10

    mov ah, 0x0e
    mov al, 'O'
    int 0x10

    
    mov ah, 0x0e
    mov al, 'S'
    int 0x10

 

    call nl
    call nl
    call nl
 
    mov bx, 48
    mov dx,2
    mov ax, 3

    mul dx

    add bx, ax
    


    mov cx, bx
    call print  ;print result






times 510 -  ($ - $$) db 0

db 0x55, 0xaa