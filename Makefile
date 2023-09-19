all:  build/boot.bin

build: 
	mkdir build


build/boot.bin: src/boot.asm  build
	
	
	@echo "assemblying..."
	nasm src/boot.asm -f bin  -o build/boot.bin
	@echo "assembled"


run:  build/boot.bin
	qemu-system-x86_64 build/boot.bin
