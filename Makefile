build:
	@echo "assemblying..."
	nasm -f elf boot.asm
	@echo "assembled"
	@echo "linking"

	ld -m elf_i386 -s -o boot boot.o

	@echo "linked"
	rm boot.o
