








;;;SECOND STAGE OF THE BOOTLOADER,  


%define Video_Buffer 0xb8000


;;;GDT


GDT_start:

    null_descriptor:
        dq 0    

    code_descriptor:                            ;32 bit code segment offset: 08h
        dw 0FFFFh
        dw 0
        db 0

        db 10011010b
        db 11001111b
        db 0

    data_descriptor:                            ;32 bit data segment offese: 10h
        dw 0FFFFh
        dw 0
        db 0

        db 10010010b
        db 11001111b
        db 0
GDT_end:

GDT_descriptor: 
    dw GDT_end - GDT_start - 1 ;size 
    dd GDT_start



CODE_SEGMENT equ code_descriptor - GDT_start
DATA_SEGMENT equ data_descriptor - GDT_start



;CHECKING A20 LINE


; Function: check_a20
;
; Purpose: to check the status of the a20 line in a completely self-contained state-preserving way.
;          The function can be modified as necessary by removing push's at the beginning and their
;          respective pop's at the end if complete self-containment is not required.
;
; Returns: 0 in ax if the a20 line is disabled (memory wraps around)
;          1 in ax if the a20 line is enabled (memory does not wrap around)
 
check_a20_lineBIOS:
	pushf
	push si
	push di
	push ds
	push es
	cli
 
	mov ax, 0x0000					;	0x0000:0x0500(0x00000500) -> ds:si
	mov ds, ax
	mov si, 0x0500
 
	not ax						;	0xffff:0x0510(0x00100500) -> es:di
	mov es, ax
	mov di, 0x0510
 
	mov al, [ds:si]					;	save old values
	mov byte [.BufferBelowMB], al
	mov al, [es:di]
	mov byte [.BufferOverMB], al
 
	mov ah, 1
	mov byte [ds:si], 0
	mov byte [es:di], 1
	mov al, [ds:si]
	cmp al, [es:di]					;	check byte at address 0x0500 != byte at address 0x100500
	jne .exit
	dec ah



.exit:
	mov al, [.BufferBelowMB]
	mov [ds:si], al
	mov al, [.BufferOverMB]
	mov [es:di], al
	shr ax, 8					;	move result from ah to al register and clear ah
	sti

    cmp ax, 1
    je .check_a20__exitOK

    cmp ax, 0
    je .check_a20__exitFAIL


.check_a20__exitFAIL:
    mov si, msg_a20_testFAIL
    call print
    jmp .exit2


.check_a20__exitOK:
    mov si, msg_a20_testOK
    call print
    jmp .exit2


.exit2:
	pop es
	pop ds
	pop di
	pop si
	popf
	ret
 
	.BufferBelowMB:	db 0
	.BufferOverMB:	db 0

;;;;

 



;COLOR TEST





;GLOBALS

msg_welcome2: db ENDL, "STAGE 2 OF THE BOOTLOADER", ENDL,"Benvenuti! Alcuni test in assembly",ENDL, ENDL ,0
msg_a20_testOK: db "A20 line eneable: OK (tested from BIOS)", ENDL, 0
msg_a20_testFAIL: db "A20 line disabled", ENDL, 0



;end of globals




BOOTLOADER2:                       ;second stage entry point

    mov si, msg_welcome2
    call print


    call check_a20_lineBIOS            ;test that A20 line is open

    

    
    ;SWITCHING FROM 32 BIT MODE


    cli
    lgdt [GDT_descriptor]               ;load GDT

    mov eax, cr0
    or eax, 1
    mov cr0, eax                        ;change CPU mode to protected mode

    jmp CODE_SEGMENT:BOOTLOADER_32BITS


;;32 bits code from here



; Check A20 line FROM PM
; Returns to caller if A20 gate is cleared.
; Continues to A20_on if A20 line is set.
; Written by Elad Ashkcenazi 
 
[bits 32]
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