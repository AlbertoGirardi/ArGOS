build:
	@echo "assemblying..."
	nasm -f elf helloWorld.asm
	@echo "assembled"
	@echo "linking"

	ld -m elf_i386 -s -o hello helloWorld.o

	@echo "linked"
