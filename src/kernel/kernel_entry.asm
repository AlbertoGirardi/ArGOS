;db "aaaaaaa"
;;;;ENTRY POINT TO THE KERNEL
[bits 32]

[extern main]

cli
call main


db "AAAAAAAAA"
