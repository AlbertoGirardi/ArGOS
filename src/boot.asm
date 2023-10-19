[org 0x7C00]
BITS 16

%define ENDL  0X0d, 0x0a
%define STAGE_2_SECTORS 4                       
%define LOAD_INTEGRITY_CHECK 3571



jmp MAIN  ;JUMP TO PROGRAM START


 


boot_disk: dw 100

msg_ARGOS: db "       ArGOS", ENDL, "di Alberto Girardi", ENDL, 0
msg: db "BOOTLOADER 16 bit",0
msg_end: db "Used bytes: ",ENDL,0
msg_to_restart: db "Press `r` to reboot  ", 0
msg_restart: db ENDL, ENDL, "RESTARTING",0
msg_loadok: db "Loaded stage 2 OK", ENDL, 0
msg_diskerror: db "Error in reading disk: ",0
msg_deA: db "A", ENDL, 0
msg_deB: db "B", ENDL, 0



newline: db 10, 13, 0





nl:
    push si
    mov si, newline
    call print

    pop si
    
    ret



;;;;;;;;;;;;

print:                 ;prints string what is referenced to by si, must terminate with 0
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


             ;print a single number value pushed on the stack
    push bp
    mov bp, sp      ;calling convention: saving old bp and setting new one to start of function

    push si
    push ax
    push bx


    
                                                ;get the number from the stack
    mov ax, [bp+4]                              ;sum the number to 48 to get character ascii code
    mov bx, 48

    add ax, bx
    
 

    mov ah, 0x0e                            ;print
    int 0x10


    pop bx
    pop ax
    pop si


    pop bp

    ret 2


    

;;;;;;;


print_number:           ;print decimal number in the stack, autoconverts from binary, MAX = 65535


    push bp
    mov bp, sp      ;calling convention: saving old bp and setting new one to start of function
    push dx
    pusha

    mov dx, 0
    mov ax, [bp+4]                      ;prep registers for divisions, get number to print from stack
    mov bx, 10                      ;10 dividend
    mov cx, 0                       ;prep counter

  


.pn_divloop:
    mov dx, 0                           ;clear dx
    div bx                              ;divide ax/bx
    push dx                             ;push digit to stack
    
    
    ;call print_digit
   
    inc cx                              ;count digits

    cmp ax, bx                          ;if dividend less than 10 end
    jl .pn_postdiv
    
    jmp .pn_divloop


.pn_postdiv:
    mov dx, 0                              ;clear dx
    div bx                                  ;divide the number to get remeainder, the digit
    push dx                             ;save digit to stack
    
    ;mov si,dx                           
    ;call print_digit                   ;debug
    inc cx

    ;push cx                    ;how many digits 
    ;call nl
    ;call print_digit                    ;debug
    ;call nl




.pn_readloop:


    call print_digit                    ;print it, getting it from the stack

    dec cx
    cmp cx, 0
    je .pn_end                          ;end printing 

    jmp .pn_readloop

.pn_end:                                ;return from function

    popa
    pop dx
    pop bp                          
  
    ret 2



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;FUNCTION TO READ FROM THE DISK using interrupts and loads 
;args: n_sectors : number of sectors to read,  address where to load them

load_disk: 


    push bp
    mov bp, sp      ;calling convention: saving old bp and setting new one to start of function
    pusha           ;save all regs to stack


    mov ax, 0
    mov es, ax
    mov ah, 2                           ;set to read from disk
    mov al, [bp+6]                      ;how many sectors to read
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, [boot_disk]

    
    mov bx, [bp+4]


    int 0x13                    ;read and load from the disk


    jc .read_errorA              ;if flags are set trigger error

    cmp al, [bp+6]              ;if the number of sectors read isn't correct trigger error
    jne .read_errorA


    mov ax, [load_check]         ;if the last variable of the second stage isn't loaded trigger error
    cmp ax, LOAD_INTEGRITY_CHECK
    jne .read_errorB

    
    mov si, msg_loadok          ;print successful load message
    call print

    popa            ;reload all saved regs from stack
    pop bp          ;restore bp to last saved value

    ret 4


.read_errorA:

    mov si, msg_diskerror
    call print

    mov si, msg_deA
    call print

    jmp CLOSURE


.read_errorB:

    mov si, msg_diskerror
    call print

    mov si, msg_deB
    call print

    jmp CLOSURE
;



;MAIN

    

MAIN:

    mov dh, 0
    mov [boot_disk], dx                ;saves boot disk number to a variable

    mov ax, 0                           ;set up data segment
    mov ds, ax
    mov es, ax

    mov ss, ax
    mov sp, 0x7c00                      ;set up stack

    times 3 call nl

    mov si, msg_ARGOS   ; welcome message
    call print

    times 2 call nl

    mov si, msg
    call print

    times 2 call nl

    

    push STAGE_2_SECTORS                       ;read  sectors
    push 0x7e00                     ;load the stage two after the boot sector in ram

    call load_disk                  ;loads from disks


    call BOOTLOADER2                        ;gives execution to second stage

    jmp CLOSURE








  
;;;;;;;;;;;;;;;;;;;;;;; END
CLOSURE:
    
    call nl
    call nl
    mov si, msg_end                 ;print end message
    call print

    jmp INSTREND

CLOSURE2:
    
    call print_number

    times 2 call nl

    mov si, msg_to_restart
    call print
  
CLOSURE3:
    mov ah, 0           ;wait for key press
    int 0x16

    mov bh, 114


    cmp al, bh              ; if key pressed is r (ASCII 114) then jump to reboot
    je reboot

    jmp CLOSURE3




reboot:                            ;reboot by jumping to bios start
    mov si, msg_restart
    call print
    db 0x0ea 
    dw 0x0000 
    dw 0xffff 



END_ALT:                        ; halt at the end
    jmp END_ALT


INSTREND:                        ;count the lenght of the program, and jump back to printing it

    push($-$$)
    jmp CLOSURE2
  
   


times 510 -  ($-$$)  db 0           ;fill first sector

db 0x55, 0xaa                       ;boot signature





