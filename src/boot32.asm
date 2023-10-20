
;;32 BITS CODE PROTECTED MODE

[bits 32]





; Check A20 line FROM PM
; Returns to caller if A20 gate is cleared.
; Continues to A20_on if A20 line is set.
; Written by Elad Ashkcenazi 
 
check_a20_linePM:   
    
    
    pushad
    mov edi,0x112345  ;odd megabyte address.
    mov esi,0x012345  ;even megabyte address.
    mov [esi],esi     ;making sure that both addresses contain diffrent values.
    mov [edi],edi     ;(if A20 line is cleared the two pointers would point to the address 0x012345 that would contain 0x112345 (edi)) 
    cmpsd             ;compare addresses to see if the're equivalent.
    popad
    jne .A20_on        ;if not equivalent , A20 line is set.
    ret               ;if equivalent , the A20 line is cleared.
    
.A20_on:

    mov edi, Video_Buffer+2

    mov al, "O"

    mov [edi], al
    inc edi
    mov [edi], byte 0x2F
    inc edi
    ret
;;



;COLOR TEST

color_test:

    pushad
    mov edi, Video_Buffer+160
    mov ebx, 0
    mov cx, 0

.loop:
    mov al, 219

    mov [edi], al
    inc edi
    mov [edi], cx
    inc edi

    inc ebx
    cmp ebx, 15
    je .end

    inc cx

    jmp .loop

.end:
    popad
    ret

;;



print32:                        ;print string at addres pushed to stack   (char, char_col, bkg_col)


    push ebp
    mov ebp, esp      ;calling convention: saving old bp and setting new one to start of function
    pushad           ;save all regs to stack


    mov edi, [CURSOR_POS]

    mov ebx, 0
    mov esi, [ebp+8]



.print_loop:                    ;similar to print 16 bits


    mov al, [esi+ebx]

    inc ebx

    or al, al
    jz .print_done

    cmp al, 10                  ; check for \n
    je .nl

    cmp al, 13                  ;check for \r
    je .cr


    mov [edi], al                   ;print char
    inc edi
    mov [edi], byte 0xf1                ;chose color
    inc edi

    jmp .print_loop


.nl:                        ;goes one line down

    add edi, 160
    jmp .print_loop

    


.cr:                        ;calculates offset from line first char and goes to that
    pushad
    mov [CURSOR_POS], edi
    mov ebx, [CURSOR_POS]

    sub ebx, Video_Buffer

    mov edx, 0
    mov eax, EBX

    mov ecx, 160

    div ecx

    sub edi, edx
    mov [CURSOR_POS], edi

    popad

    mov edi, [CURSOR_POS]
    jmp .print_loop




.print_done:     

       ; return
    mov [CURSOR_POS], edi
    popad            ;reload all saved regs from stack
    pop ebp          ;restore bp to last saved value

    ret 4   ;return popping also all args



;GLOBALS


var1: db 123

msg_hello: db "Hello World from 32     AA",13, 10,"BITS        ",10, 13,"AGFNAJGNAGJAW" ,ENDL,0
msg_test: db "TEST TEST TEST        ",0
msg_test2: db "22222       ",0


CURSOR_POS: dd 0





;

BOOTLOADER_32BITS:
    [BITS 32]

    ;SETTING UP SEGMENT REGISTERS FOR 32 BIT MODE
    mov ax, DATA_SEGMENT
    mov ds, ax
    mov ss, ax

    sti    ;enable interrupts

    mov [CURSOR_POS], dword Video_Buffer



    mov edi, Video_Buffer

    mov al, "a"

    mov [edi], al
    inc edi
    mov [edi], byte 0xf1
    inc edi

    ;;call check_a20_linePM to test if it is opened

    call check_a20_linePM
    
    ;call color_test

    push msg_hello
    call print32

    push msg_test
    call print32


    jmp .end






;;;END OF BOOTLOADER
.end:

    cli
    jmp $
    


eeeeee:
    cli
    jmp $





load_check: dw LOAD_INTEGRITY_CHECK                     ;MUST STAY AT THE END OF THE PROGRAM to check if everything is loaded

times (((STAGE_2_SECTORS+1)*512)-($-$$)) db 0