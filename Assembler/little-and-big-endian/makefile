lbe: lbe.o
	gcc -o lbe lbe.o -no-pie
lbe.o: lbe.asm
	nasm -f elf64 lbe.asm
