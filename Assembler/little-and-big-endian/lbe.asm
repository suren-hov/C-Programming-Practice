section .data
	lit db "little endian", 10, 0
	big db "big endian", 10, 0
	num dd 4
extern printf

section .text
	global main:
main:
	push rbp
	mov rbp, rsp
	
	mov rdi, lit
	mov rdx, big
	cmp byte [num], 0
	cmove rdi, rdx

	call printf

	leave
	ret
