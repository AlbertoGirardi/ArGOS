Ccomp := i686-elf-gcc


b_fold := boot


OS_image := ArGOS.iso
bootloader := $(b_fold)/boot.asm
bootloader2stage := $(b_fold)/boot2.asm
bootloader32bits := $(b_fold)/boot32.asm 

krnc := src/kernel/ArGOS_kernel.c

total_bootloader:= bootloader.asm
krno := kernel.o

qemu := qemu-system-x86_64



all:  build/$(OS_image)

build: 
	mkdir build


build/$(OS_image): build/$(total_bootloader) build/krn.bin 			#assembles files
	
	@echo "assemblying..."
	nasm build/$(total_bootloader) -f bin  -o build/$(OS_image)
	@echo "assembled"




build/$(total_bootloader): src/$(bootloader) src/$(bootloader2stage) src/$(bootloader32bits) build #stiches together files
																											
	@echo stiching together asm files								
	cat src/$(bootloader) src/$(bootloader2stage) src/$(bootloader32bits) > build/$(total_bootloader)
	@echo ok


build/$(krno):  $(krnc) build/krne

	$(Ccomp) --freestanding -m32 -g -c $(krnc) -o build/$(krno) -mno-red-zone

build/krne.o: src/kernel/kernel_entry.asm

	nasm src/kernel/kernel_entry.asm -f elf -o build/krne.o


build/krn.bin: build/krne.o build/$(krno)

	i686-elf-ld  build/$(krno) build/krne.o  -o krn.bin -nostdlib  


run:  build/$(OS_image)			#runs on QEMU	
	$(qemu) build/$(OS_image)

clear:							#removes tmp files
	rm build/$(total_bootloader)

totclear: 						#removes everything in the build folder
	rm -r build

