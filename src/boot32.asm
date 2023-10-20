
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
    jne A20_on        ;if not equivalent , A20 line is set.
    ret               ;if equivalent , the A20 line is cleared.
    
A20_on:

    mov edi, Video_Buffer+2

    mov al, "O"

    mov [edi], al
    inc edi
    mov [edi], byte 0x2F
    inc edi
    ret



  

BOOTLOADER_32BITS:
    [BITS 32]

    ;SETTING UP SEGMENT REGISTERS FOR 32 BIT MODE
    mov ax, DATA_SEGMENT
    mov ds, ax
    mov ss, ax

    sti    ;enable interrupts



    mov edi, Video_Buffer

    mov al, "a"

    mov [edi], al
    inc edi
    mov [edi], byte 0xf1
    inc edi

    ;;call check_a20_linePM to test if it is opened

    call check_a20_linePM



    jmp .end






;;;END OF BOOTLOADER
.end:

    cli
    jmp $
    








load_check: dw LOAD_INTEGRITY_CHECK                     ;MUST STAY AT THE END OF THE PROGRAM to check if everything is loaded

times (((STAGE_2_SECTORS+1)*512)-($-$$)) db 0