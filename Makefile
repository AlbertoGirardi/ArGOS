


building:
	
	
	@echo "assemblying..."
	nasm src/boot.asm -f bin  -o build/boot.bin
	@echo "assembled"