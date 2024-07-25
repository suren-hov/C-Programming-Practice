section .data
	text db "Enter the numbers and operation: ", 0
	format db "%d %d %c", 0
	result db "The result is %d", 10, 0
section .bss
	num1 resd 1
	num2 resd 1
	operation resb 1
section .text
	global main:
main:
	extern printf
	extern scanf

	push rbp
	mov rbp, rsp

	mov rdi, text
	call printf

	mov rdi, format
	mov rsi, num2
	mov rdx, num1
	mov rcx, operation
	call scanf

	movsx rsi, dword [num1]
	movsx rdi, dword [num2]

	cmp byte [operation], '+'
	je addition
	cmp byte [operation], '-'
	je minus
	cmp byte [operation], '*'
	je mult
	
	mov rax, rdi
	div rsi
	jmp print

addition:
	add rsi, rdi
	mov rax, rsi
	jmp print

minus: 
	sub rsi, rdi
	mov rax, rsi
	jmp print

mult:
	mov rax, rsi	
	mul rdi
	jmp print

print:
	mov rdi, result
	mov rsi, rax
	call printf

	leave
	ret
