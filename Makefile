OS_image := ArGOS.iso
bootloader := boot.asm

all:  build/$(OS_image)

build: 
	mkdir build


build/$(OS_image): src/$(bootloader)  build
	
	
	@echo "assemblying..."
	nasm src/$(bootloader) -f bin  -o build/$(OS_image)
	@echo "assembled"


run:  build/$(OS_image)
	qemu-system-x86_64 build/$(OS_image)
