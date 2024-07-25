section .data
	arr dw 1, -8, 35, 188, -669
	size equ ($-arr) / 2
	format db "Max number is %d at the index of %d ", 10, 0

section .text
	global main
	extern printf
main:
	push rbp
	mov rbp, rsp
	
	sub rsp, 16
	
	mov rbx, 1
	mov dx, word [arr]
	mov word [rbp - 10], dx
	mov qword [rbp - 8], 0
loop1:	
	cmp rbx, size
	je end
	
	cmp dx, word [arr + rbx * 2]
	jge next
	mov dx, word [arr + rbx * 2]
	mov word[rbp - 10], dx
	mov qword [rbp - 8], rbx

next:
	inc rbx
	jmp loop1

end:
	mov rdi, format
	movsx rsi, word [rbp - 10]
	mov rdx, qword [rbp - 8]
	call printf

	add rsp, 10
	mov rsp, rbp
	pop rbp
	ret
