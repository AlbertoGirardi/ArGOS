#compilation and linking toolchain
Ccomp := i686-elf-gcc
cflags := -c --freestanding -m32  -mno-red-zone  #-g

assembler := nasm
asmflags := -f elf32

linker := i686-elf-gcc
linkflags := -nostdlib   -Tsrc/kernel/linker.ld -lgcc


#build folder
bf = build

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

libsc := $(wildcard $(libf)/*.c)
libsasm := $(wildcard $(libf)/*.asm)



#libs obj files


libso := $(patsubst $(libf)/%.c,$(bf)/%.o,$(libsc))
libsasmo := $(patsubst $(libf)/%.asm,$(bf)/%.o,$(libsasm))


#OS IMAGE

OS_image := ArGOS.iso


GREEN2= \033[1;32m
green3 = \033[0;36m
GREEN= \033[1;36m
NC= \033[0m # No Color

qemu := qemu-system-x86_64



all:  $(bf)/$(OS_image) 



test:
	@echo $(libsasm) $(libsasmo)

$(bf): 
	mkdir $(bf)
	



$(bf)/$(OS_image): $(bf)/$(bootbin) $(bf)/$(kernelbin)	$(bf)/zero.bin			#os image

	cat $(bf)/$(bootbin) $(bf)/$(kernelbin) $(bf)/zero.bin > $(bf)/$(OS_image) 
	@echo " $(GREEN2)\n\nDONE\n\n$(NC)"

$(bf)/zero.bin: $(bf)
	echo "times 8192 dd 0" > $(bf)/zero.asm
	$(assembler) $(bf)/zero.asm -f bin -o $(bf)/zero.bin

$(bf)/$(bootbin): $(bf)/$(total_bootloader) 			#assembles files
	

	$(assembler) $(bf)/$(total_bootloader) -f bin  -o $(bf)/$(bootbin)
	@echo  "$(GREEN)ASSEMBLED BOOTLOADER\n$(NC)"





$(bf)/$(total_bootloader): src/$(bootloader) src/$(bootloader2stage) src/$(bootloader32bits) $(bf) #stiches together files
																											
	@echo stiching together asm files								
	cat src/$(bootloader) src/$(bootloader2stage) src/$(bootloader32bits) > $(bf)/$(total_bootloader)
	@echo ok


$(bf)/$(krnco):  $(krnc) 								#kernel compilinh

	$(Ccomp)   $(krnc) -o $(bf)/$(krnco)  $(cflags)
		@echo  "$(GREEN)COMPILED KERNEL\n$(NC)"


$(bf)/$(krneo): $(krne)

	$(assembler) $(krne) $(asmflags) -o $(bf)/$(krneo)


$(bf)/$(kernelbin): $(bf)/$(krneo) $(bf)/$(krnco)  $(libso) $(libsasmo) src/kernel/linker.ld

	@echo  "$(GREEN)COMPILED LIBS\n$(NC)"

	$(linker)  $(bf)/$(krneo) $(bf)/$(krnco) $(libso) $(libsasmo) -o $(bf)/$(kernelbin)  $(linkflags)
	@echo  "$(GREEN)LINKED\n$(NC)"




$(bf)/%.o: $(libf)/%.c

	$(Ccomp)  $< -o $@  $(cflags)
	@echo  "$(green3)compile lib $<$(NC)\n"




$(bf)/%.o: $(libf)/%.asm
	$(assembler) $(asmflags) $< -o $@

run:  $(bf)/$(OS_image)			#runs on QEMU	
	$(qemu) $(bf)/$(OS_image)   




db:  $(bf)/$(OS_image)			#runs on QEMU	with debugging 
#! doesnt work
	$(qemu) -s -S $(bf)/$(OS_image)  
	
####  -icount  6,align=on

odump:  $(bf)/$(OS_image)

	objdump -t -h $(libso) $(bf)/$(krneo) $(bf)/$(krnco) $(libsasmo)



recomp: tclean all


clean:							#removes tmp files
	rm $(bf)/*.asm
	rm $(bf)/*.o
	rm $(bf)/*.bin

tclean: 						#removes everything in the $(bf) folder
	rm -r $(bf)

