section .data
	text db "Enter the number: ", 0
	format db "%d %d", 0
	result db "The result is: %d", 10, 0
section .bss
	num1 resd 1
	num2 resd 1
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
	call scanf

	movsx rsi, dword [num1]
	add esi, dword [num2]

	mov rdi, result
	call printf

	leave
	ret   
