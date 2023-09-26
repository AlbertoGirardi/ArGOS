[org 0x7C00]
BITS 16

%define ENDL  0X0d, 0x0a



jmp main


 


end:
var: db 1
msg_ARGOS: db "                         ArGOS", ENDL, "di Alberto Girardi", ENDL, 0
msg: db "BOOTLOADER. OS booting start", ENDL,"Benvenuti! Alcuni test in assembly",ENDL,0
msg_end : db "Used bytes: ",ENDL,0

array: db 1,1,0,2,0,5,0,0
array2:  db 0,0,0,0,0,0,0,0

newline: db 10, 13, 0





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

    

    mov ax, si                              ;sum the number to 48 to get character ascii code
    mov bx, 48

    add ax, bx
    
 

    mov ah, 0x0e                            ;print
    int 0x10


    pop bx
    pop ax
    pop si

    ret


    

;;;;;;;


print_number:           ;print decimal number given in si, autoconverts from binary, MAX = 65535

    pusha

    mov dx, 0
    mov ax, si                      ;prep registers for divisions
    mov bx, 10                      ;10 dividend
    mov cx, 0                       ;prep counter

  


.pn_divloop:
    mov dx, 0                           ;clear dx
    div bx                              ;divide ax/bx
    push dx                             ;push digit to stack
    
    mov si,dx
    ;call print_digit
   
    inc cx                              ;count digits

    cmp ax, bx                          ;if dividend less than 10 end
    jl .pn_postdiv
    
    jmp .pn_divloop


.pn_postdiv:
    mov dx, 0                              ;clear dx
    div bx                                  ;divide the number to get remeainder, the digit
    push dx                             ;save digit to stack
    
    mov si,dx                           ;store last digit
    ;call print_digit                   ;debug
    inc cx

    mov si, cx                          ;how many digits 
    call nl
    ;call print_digit                    ;debug
    call nl
   



.pn_readloop:
    pop si                              ;read digit from stack
    call print_digit                    ;print it
    dec cx
    cmp cx, 0
    je .pn_end                          ;end printing 

    jmp .pn_readloop

.pn_end:                                ;return from function
    call nl
    call nl
    popa
    ret






main:

    mov ax, 0                           ;set up data segment
    mov ds, ax
    mov es, ax


    times 3 call nl

    mov si, msg_ARGOS   ; welcome message
    call print

    times 2 call nl

    mov si, msg
    call print

    times 2 call nl



    times 2 call  nl


    mov si, 9874
    call print_number




    

    times 3 call nl


    mov si, msg_end
    call print

    mov si, ($-$$)
    call print_number

    

    






  


.halt:                              ;halt
  
   
    jmp .halt

times 510 -  ($-$$)  db 0

db 0x55, 0xaa           