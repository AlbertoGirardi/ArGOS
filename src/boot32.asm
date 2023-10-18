






;;;SECOND STAGE OF THE BOOTLOADER,  

msg_welcome2: db ENDL, "STAGE 2 OF THE BOOTLOADER", ENDL,"Benvenuti! Alcuni test in assembly",ENDL, ENDL ,0


BOOTLOADER32:                       ;second stage entry point

    mov si, msg_welcome2
    call print





;;;END OF BOOTLOADER
.end:
    jmp CLOSURE





load_check: dw 3571                     ;MUST STAY AT THE END OF THE PROGRAM to check if everything is loaded

times (((STAGE_2_SECTORS+1)*512)-($-$$)) db 0