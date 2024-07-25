#makefile for third.asm
third: third.o
	gcc -o third third.o -no-pie
third.o: third.asm
	nasm -f elf64 -g -F dwarf third.asm -l third.lst
