section .data
	msg db "Hello World", 10, 0
	size equ 12
	low_f equ 'a'
	low_e equ 'z'
	dif equ 32
section .text
	global main:
main:	
	mov rsi, msg
	mov rbx, 0
	
loop:
	cmp rbx, size
	je end
	cmp byte [rsi + rbx], low_f
	jb cont
	cmp byte [rsi + rbx], low_e
	ja cont
	sub byte [rsi + rbx], dif
cont:
	inc rbx
	jmp loop

end:
	mov rax, 1
	mov rdi, 1
	mov rsi, msg
	mov rdx, size
	syscall	

	mov rax, 60
	mov rdi, 0
	syscall
