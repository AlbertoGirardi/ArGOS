build:
	@echo "assemblying..."
	nasm -f bin boot.asm -o boot.bin
	@echo "assembled"
