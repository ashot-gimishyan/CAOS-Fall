    .intel_syntax noprefix
    .globl _start
    
_start:
    mov rax, 12
    syscall
    
    mov rbp, rax
    mov rsp, rbp
    mov rax, 12
    lea rdi, [rbp+60000000]
    syscall

    // add EOL symbol
    mov r8, 10
    mov [rbp], r8
    add rsp, 1
    jmp read

read:
    mov rax, 0
    mov rdi, 0
    mov rsi, rsp
    mov rdx, 4096
    syscall
    
    test rax, rax
    jl skip
    
    add rsp, rax
    test rax, rax
    jnz read

skip:
    sub rsp, 1
    cmp rsp, rbp
    jle end
    
    cmpb [rsp], 10
    jz skip
    cmpb [rsp], 32
    jz skip
    
    add rsp, 1
    mov r8, 10
    mov [rsp], r8
    mov rbx, rsp
    jmp line
    
write:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rbx + 1]
    mov rdx, rcx
    syscall

    mov rsp, rbx
    cmp rbx, rbp
    jle end

line:
    sub rbx, 1
    cmpb [rbx], 10
    jnz line

    mov rcx, rsp
    sub rcx, rbx
    jmp write
     
end:
    mov rax, 60
    syscall
