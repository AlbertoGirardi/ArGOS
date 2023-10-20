OS_image := ArGOS.iso
bootloader := boot.asm
bootloader2stage := boot2.asm
bootloader32bits := boot32.asm 

total_bootloader:= bootloader.asm

qemu := qemu-system-x86_64



all:  build/$(OS_image)

build: 
	mkdir build


build/$(OS_image): build/$(total_bootloader)  			#assembles files
	
	@echo "assemblying..."
	nasm build/$(total_bootloader) -f bin  -o build/$(OS_image)
	@echo "assembled"


build/$(total_bootloader): src/$(bootloader) src/$(bootloader2stage) src/$(bootloader32bits) build #stiches together files
																											
	@echo stiching together asm files								
	cat src/$(bootloader) src/$(bootloader2stage) src/$(bootloader32bits) > build/$(total_bootloader)
	@echo ok

run:  build/$(OS_image)			#runs on QEMU	
	$(qemu) build/$(OS_image)

clear:							#removes tmp files
	rm build/$(total_bootloader)

totclear: 						#removes everything in the build folder
	rm -r build

