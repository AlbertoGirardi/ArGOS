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

    mov bh, 0
    mov bl, 100
    mov ch, 48


    ;call nl

    ;jmp write
   


write:

    

    mov ah, 0x0e
    mov al, 32
    int 0x10


    inc bh

    mov ah, 0x0e
    mov al, ch
    int 0x10

    inc ch

   

    cmp bh, bl

    je end

    jmp write



end:






times 510 -  ($ - $$) db 0

db 0x55, 0xaa