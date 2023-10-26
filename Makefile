#compilation and linking toolchain
Ccomp := i686-elf-gcc
link := i686-elf-ld



#asm file for bootloader

#sources
b_fold := boot

bootloader := $(b_fold)/boot.asm
bootloader2stage := $(b_fold)/boot2.asm
bootloader32bits := $(b_fold)/boot32.asm 

#build files

total_bootloader:= bootloader.asm
bootbin := boot.bin        							#binary bootloader image



#kernel files

kernel_f := src/kernel
#sources
krnc := $(kernel_f)/ArGOS_kernel.c
krne := $(kernel_f)/kernel_entry.asm

#object files
krnco := krnc.o
krneo := krne.o

kernelbin := krn.bin								#kernel binary image


#libs files
libf := $(kernel_f)/lib
vgal := $(libf)/vga_driver.c


#libs obj files
vgalo := vga.o



#OS IMAGE

OS_image := ArGOS.iso




qemu := qemu-system-x86_64



all:  build/$(OS_image)

build: 
	mkdir build
	



build/$(OS_image): build/$(bootbin) build/$(kernelbin)	build/zero.bin			#os image

	cat build/$(bootbin) build/$(kernelbin) build/zero.bin > build/$(OS_image) 
	@echo "done"

build/zero.bin: build
	echo "times 8192 dd 0" > build/zero.asm
	nasm build/zero.asm -f bin -o build/zero.bin

build/$(bootbin): build/$(total_bootloader) 			#assembles files
	
	@echo "assemblying..."
	nasm build/$(total_bootloader) -f bin  -o build/$(bootbin)
	@echo "assembled"




build/$(total_bootloader): src/$(bootloader) src/$(bootloader2stage) src/$(bootloader32bits) build #stiches together files
																											
	@echo stiching together asm files								
	cat src/$(bootloader) src/$(bootloader2stage) src/$(bootloader32bits) > build/$(total_bootloader)
	@echo ok


build/$(krnco):  $(krnc) 

	$(Ccomp) --freestanding -m32 -g -c $(krnc) -o build/$(krnco) -mno-red-zone  

build/$(krneo): $(krne)

	nasm $(krne) -f elf -o build/$(krneo)


build/$(kernelbin): build/$(krneo) build/$(krnco)  build/$(vgalo)

	i686-elf-ld  build/$(krneo) build/$(krnco) build/$(vgalo) -o build/$(kernelbin)  -nostdlib   --oformat binary -Ttext 0x1000



build/$(vgalo): $(vgal)

	$(Ccomp) --freestanding -m32 -g -c $(vgal) -o build/$(vgalo) -mno-red-zone  








run:  build/$(OS_image)			#runs on QEMU	
	$(qemu) build/$(OS_image)

clear:							#removes tmp files
	rm build/$(total_bootloader)

totclear: 						#removes everything in the build folder
	rm -r build

