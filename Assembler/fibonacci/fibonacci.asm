section .data
	decimal db '%i', 0
	index db 9
section .text
	extern printf
	global main:
main:
	push rbp
	mov rbp, rsp

	mov rax, 0
	mov rbx, 1
	mov rdx, [index]

loop_foo:
	cmp rdx, 0
	je even_index
	cmp rdx, 1
	je odden_index
	add rax, rbx
	add rbx, rax
	sub rdx, 2
	jmp loop_foo

even_index:
	mov rbx, rax
odden_index:
	mov rsi, rbx
	mov rdi, decimal
	mov rax, 0
	call printf
	
	leave
	ret
