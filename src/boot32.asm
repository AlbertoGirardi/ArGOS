








;;;SECOND STAGE OF THE BOOTLOADER,  


;;;GDT


GDT_start:

    null_descriptor:
        dq 0    

    code_descriptor:
        dw 0FFFFh
        dw 0
        db 0

        db 10011010b
        db 11001111b
        db 0

    data_descriptor:
        dw 0FFFFh
        dw 0
        db 0

        db 10010010b
        db 11001111b
        db 0





;CHECKING A20 LINE


; Function: check_a20
;
; Purpose: to check the status of the a20 line in a completely self-contained state-preserving way.
;          The function can be modified as necessary by removing push's at the beginning and their
;          respective pop's at the end if complete self-containment is not required.
;
; Returns: 0 in ax if the a20 line is disabled (memory wraps around)
;          1 in ax if the a20 line is enabled (memory does not wrap around)
 
get_a20_state:
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
	.BufferOverMB	db 0






msg_welcome2: db ENDL, "STAGE 2 OF THE BOOTLOADER", ENDL,"Benvenuti! Alcuni test in assembly",ENDL, ENDL ,0
msg_a20_testOK: db "A20 line open: OK (tested from BIOS)", ENDL, 0
msg_a20_testFAIL: db "A20 line closed", ENDL, 0



BOOTLOADER32:                       ;second stage entry point

    mov si, msg_welcome2
    call print


    call get_a20_state              ;test that A20 line is open

    
  




;;;END OF BOOTLOADER
.end:
    jmp CLOSURE





load_check: dw LOAD_INTEGRITY_CHECK                     ;MUST STAY AT THE END OF THE PROGRAM to check if everything is loaded

times (((STAGE_2_SECTORS+1)*512)-($-$$)) db 0