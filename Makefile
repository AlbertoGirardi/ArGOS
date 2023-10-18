OS_image := ArGOS.iso
bootloader := boot.asm
bootloader2stage := boot32.asm 

total_bootloader:= bootloader.asm




all:  build/$(OS_image)

build: 
	mkdir build


build/$(OS_image): build/$(total_bootloader)  
	
	@echo "assemblying..."
	nasm build/$(total_bootloader) -f bin  -o build/$(OS_image)
	@echo "assembled"


build/$(total_bootloader): src/$(bootloader) src/$(bootloader2stage) build

	@echo stiching together asm files
	cat src/$(bootloader) src/$(bootloader2stage) > build/$(total_bootloader)
	@echo ok

run:  build/$(OS_image)
	qemu-system-x86_64 build/$(OS_image)

clear:
	rm build/$(total_bootloader)

totclear: 
	rm -r build


