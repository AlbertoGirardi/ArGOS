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



;;;;;;;;;;;;

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


;;;;;;;;;

print_digit: 


             ;print a single number value given in si,
    push si
    push ax
    push bx

    

    mov ax, si
    mov bx, 48

    add ax, bx
    
 

    mov ah, 0x0e
    int 0x10


    pop bx
    pop ax
    pop si

    ret
    

;;;;;;;

read_array:          ;function to print the values of array at si

    push si
    push bx
    push ax

    mov ah, 1

    jmp .ra_loop



.ra_loop:

    mov si, [bx]
    call print_digit
    
    cmp ah, 8
    je .ra_end

    inc bx
    inc ah
    jmp .ra_loop

.ra_end:

    pop ax
    pop bx
    pop si
    ret

;;;;;;;;;;;;

write_array:      ;writes incrementing numbers to array in bx 

    push si
    push bx
    push ax

    mov ah, 0

    jmp .wa_loop



.wa_loop:

    mov [bx], ah
   
    
    cmp ah, 7
    je .wa_end

    inc bx
    inc ah
    jmp .wa_loop

.wa_end:

    pop ax
    pop bx
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


    mov ax, 8                                  ;clear registers for division and prepare operands
    mov bx, 4
    mov dx, 0

    
    push ax                                     ;save ax to stack

    div bx                                      ;divide

    mov si, ax  
    call print_digit                            ;print quotient
    call nl
    mov si, dx                                  ;print remainder
    call print_digit

    times 2 call nl
                                                ;8 bit division
    
                                                  ;clear registers for division and prepare operands
    pop ax                                          ;recover ax value

    ;mov bl, 4
    mov dx, 0


    div bl

    movzx si, al
    call print_digit                            ;print quotient
    call nl
    movzx si, ah                                  ;print remainder
    call print_digit

    times 2 call  nl

   
    mov bx, array

    call read_array
    call nl

    call write_array

    call read_array

    call nl

    push 1
    push 2
    push 3

    pop si
    call print_digit
    pop si
    call print_digit
    pop si
    call print_digit
    

    

    






   


end:
var: db 1
msg_ARGOS: db "                 ArGOS", 0
msg: db "BOOTLOADER. OS booting start", ENDL,"Benvenuti! Alcuni test in assembly",ENDL,0

array: db 1,1,0,2,0,5,0,0
array2:  db 0,0,0,0,0,0,0,0

newline: db 10, 13, 0



.halt:
  
   
    jmp .halt

times 510 -  ($-$$)  db 0

db 0x55, 0xaa