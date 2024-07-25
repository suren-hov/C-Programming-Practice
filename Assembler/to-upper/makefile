#makefile for to-upper.asm
to-upper: to-upper.o
	gcc -o to-upper to-upper.o -no-pie
to-upper.o: to-upper.asm
	nasm -f elf64 -g -F dwarf to-upper.asm -l to-upper.lst
