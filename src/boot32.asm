

;;;SECOND STAGE OF THE BOOTLOADER,  

msg_welcome2: db  ENDL,"Benvenuti! Alcuni test in assembly",ENDL,"STAGE 2 OF THE BOOTLOADER",0


BOOTLOADER32:                       ;second stage entry point

    mov si, msg_welcome2
    call print



jmp CLOSURE

times 2048 db 0

