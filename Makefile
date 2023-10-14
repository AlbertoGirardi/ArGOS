OS_image := ArGOS.iso
bootloader := boot.asm
bootloader2stage := boot32.asm 

all:  build/$(OS_image)

build: 
	mkdir build


build/$(OS_image): src/$(bootloader)  build
	
	@echo stiching together asm files
	cat src/$(bootloader) src/$(bootloader2stage) > build/bootloader.asm
	@echo ok
	@echo "assemblying..."
	nasm build/bootloader.asm -f bin  -o build/$(OS_image)
	@echo "assembled"


run:  build/$(OS_image)
	qemu-system-x86_64 build/$(OS_image)


totclear: 
	rm -r build


