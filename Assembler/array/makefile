arr: arr.o
	gcc -o arr arr.o -no-pie
arr.o: arr.asm 
	nasm -f elf64 arr.asm
