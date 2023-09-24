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


print_number:           ;print decimal number given in si, autoconverts from binary

    pusha

    mov dx, 0
    mov ax, si                      ;prep registers for divisions
    mov bx, 10
    mov cx, 0                       ;prep counter

  


.pn_divloop:
    mov dx, 0
    div bx
    push dx
    
    mov si,dx
    call print_digit
   
    inc cx

    cmp ax, bx
    jl .pn_postdiv
    
    jmp .pn_divloop


.pn_postdiv:
    mov dx, 0
    div bx
    push dx
    
    mov si,dx
    call print_digit
    inc cx

    mov si, cx
    call nl
    call print_digit
   
    

    ;mov si, cx
    ;call print_digit
    


.pn_readloop:
    ;movzx si, cl
    ;call print_digit
    ;jmp .pn_end

.pn_end:
    call nl
    call nl
    popa
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



    times 2 call  nl


    mov si, 3510

    call print_number

    

    






   


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