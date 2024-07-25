section .data
       decimal db "%d"
section .bss
       number resd 1
section .text
extern printf
extern scanf
       global main:
main:
       push rbp     
       mov rbp, rsp 
       mov rax, 0
       mov rdi, decimal
       mov rsi, number
       call scanf

       mov rax, 1
       mov rsi, number
f_loop:
       cmp dword [rsi], 0
       jl low_case
       je end_prog
       mul dword [rsi] 
       dec dword [rsi]   
       jmp f_loop 
low_case:
       mov rax, -1
end_prog:
       mov rsi, rax
       mov rax, 0
       mov rdi, decimal
       call printf

       mov rax, 0    
       mov rsp, rbp  
       pop rbp        
       ret




