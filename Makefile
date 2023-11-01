#compilation and linking toolchain
Ccomp := i686-elf-gcc
cflags := -c --freestanding -m32 -g -mno-red-zone 



linker := i686-elf-gcc
linkflags := -nostdlib   -Tsrc/kernel/linker.ld -lgcc



#asm file for bootloader

#sources
b_fold := boot

bootloader := $(b_fold)/boot.asm 
bootloader2stage := $(b_fold)/boot2.asm 
bootloader32bits := $(b_fold)/boot32.asm  

#build files

total_bootloader:= bootloader.asm 
bootbin := boot.bin 
#binary bootloader image



#kernel files

kernel_f := src/kernel
#sources
krnc := $(kernel_f)/ArGOS_kernel.c 
krne := $(kernel_f)/kernel_entry.asm 

#object files
krnco := krnc.o 
krneo := krne.o 

kernelbin := krn.bin 
#kernel binary image


#libs files

libf := $(kernel_f)/lib
vgal := $(libf)/vga_driver.c

libsc := $(wildcard $(libf)/*.c)




#libs obj files
vgalo := vga.o


libso := $(patsubst $(libf)/%.c,build/%.o,$(libsc))

#OS IMAGE

OS_image := ArGOS.iso


GREEN2= \033[1;32m
green3 = \033[0;36m
GREEN= \033[1;36m
NC= \033[0m # No Color

qemu := qemu-system-x86_64



all:  build/$(OS_image) 



test:
	@echo $(libsc) $(libso)

build: 
	mkdir build
	



build/$(OS_image): build/$(bootbin) build/$(kernelbin)	build/zero.bin			#os image

	cat build/$(bootbin) build/$(kernelbin) build/zero.bin > build/$(OS_image) 
	@echo " $(GREEN2)\n\nDONE\n\n$(NC)"

build/zero.bin: build
	echo "times 8192 dd 0" > build/zero.asm
	nasm build/zero.asm -f bin -o build/zero.bin

build/$(bootbin): build/$(total_bootloader) 			#assembles files
	

	nasm build/$(total_bootloader) -f bin  -o build/$(bootbin)
	@echo  "$(GREEN)ASSEMBLED BOOTLOADER\n$(NC)"





build/$(total_bootloader): src/$(bootloader) src/$(bootloader2stage) src/$(bootloader32bits) build #stiches together files
																											
	@echo stiching together asm files								
	cat src/$(bootloader) src/$(bootloader2stage) src/$(bootloader32bits) > build/$(total_bootloader)
	@echo ok


build/$(krnco):  $(krnc) 								#kernel compilinh

	$(Ccomp)   $(krnc) -o build/$(krnco)  $(cflags)
		@echo  "$(GREEN)COMPILED KERNEL\n$(NC)"


build/$(krneo): $(krne)

	nasm $(krne) -f elf32 -o build/$(krneo)


build/$(kernelbin): build/$(krneo) build/$(krnco)  $(libso)

	@echo  "$(GREEN)COMPILED LIBS\n$(NC)"

	$(linker)  build/$(krneo) build/$(krnco) $(libso) -o build/$(kernelbin)  $(linkflags)
	@echo  "$(GREEN)LINKED\n$(NC)"




build/%.o: $(libf)/%.c

	$(Ccomp)  -c $< -o $@  $(cflags)
	@echo  "$(green3)compile lib $<$(NC)\n"





run:  build/$(OS_image)			#runs on QEMU	
	$(qemu) build/$(OS_image)    
	
####  -icount  6,align=on


recomp: tclean all

clean:							#removes tmp files
	rm build/*.asm
	rm build/*.o
	rm build/*.bin

tclean: 						#removes everything in the build folder
	rm -r build

