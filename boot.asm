jmp main


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






times 510 -  ($ - $$) db 0

db 0x55, 0xaa