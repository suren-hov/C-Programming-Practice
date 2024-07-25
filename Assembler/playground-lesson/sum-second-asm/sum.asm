section .data
	num1 dd 2
    num2 dd 5
    result db "The result is: %d", 10, 0
section .text
	global main:
main:
	extern printf
	extern scanf
	
	push rbp
	mov rbp, rsp

	movsx rsi, dword [num1]
	add esi, dword [num2]

	mov rdi, result
	call printf

	leave
	ret   
