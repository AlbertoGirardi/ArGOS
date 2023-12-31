



;;;SECOND STAGE OF THE BOOTLOADER,  


%define Video_Buffer 0xb8000

;KERNEL LOADING INFORMATION
%define KERNEL_ADDRESS 0x9000
%define KERNEL_SECTORS    60

%define A20_TEST_MA 5




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
    mov [A20ok], word 0         ;pushes control value
    call print
    jmp .exit2


.check_a20__exitOK:
    mov si, msg_a20_testOK
    mov [A20ok], word A20_TEST_MA
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



print_ascii: 


             ;print a single ascii pushed on the stack
    push bp
    mov bp, sp      ;calling convention: saving old bp and setting new one to start of function

    push si
    push ax
    push bx


    
                                                ;get the number from the stack
    mov ax, [bp+4]                              ;sum the number to 48 to get character ascii code
    mov bx, 48

    add ax, 0
    
 

    mov ah, 0x0e                            ;print
    int 0x10


    pop bx
    pop ax
    pop si


    pop bp

    ret 2


    

ascii_test:

    mov si,0


.loop:
    push si

    call print_ascii
    inc si

    cmp si,256
    je .end
    jmp .loop


.end:
    ret
 







;GLOBALS

msg_welcome2: db ENDL, "STAGE 2 OF THE BOOTLOADER", ENDL,"Benvenuti! Alcuni test in assembly",ENDL, ENDL ,0
msg_a20_testOK: db "A20 line eneabled: OK (tested from BIOS)", ENDL, 0
msg_a20_testFAIL: db "A20 line disabled", ENDL, 0
A20ok: dd 0



;end of globals





BOOTLOADER2:                       ;second stage entry point

    mov si, msg_welcome2
    call print


    call check_a20_lineBIOS            ;test that A20 line is open

    mov ax, [A20ok]
    mov bx, A20_TEST_MA                           ;controls result of a20line test
    cmp ax, bx
    jne CLOSURE                         ;if closed ends program

    ;call ascii_test

    push STAGE_2_SECTORS + 1                              ;LOADING THE KERNEL
    push KERNEL_SECTORS                            ;SEGMENTS TO READ
    push KERNEL_ADDRESS                 ;ADDRESS

    call load_disk

    call nl 
    push sp
    call print_number
    call nl

    push DATA_SEGMENT
    call print_number



    
    ;SWITCHING FROM 32 BIT MODE


    mov eax, switch_32       ;jump only if sets (for debug)
    mov ebx, 1
    cmp eax, ebx
    jne CLOSURE

    push GDT_descriptor
    call print_number

    

    cli
    lgdt [GDT_descriptor]               ;load GDT

    mov eax, cr0
    or eax, 1
    mov cr0, eax                        ;change CPU mode to protected mode

    jmp CODE_SEGMENT:BOOTLOADER_32BITS  ;jump to protected mode codes





