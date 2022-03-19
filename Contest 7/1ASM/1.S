    .global _start
    .global syscall
    .intel_syntax noprefix

_start:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        jmp     read
        
write:
        // 1	write	sys_write
        mov     edi, 1
        mov     esi, 1
        mov     rdx, rbp
        mov     ecx, 1
        call    syscall
        
read:
        // 0	read	sys_read
        mov     edi, 0
        mov     esi, 0
        mov     rdx, rbp // void *rdx = &rbp 
        mov     ecx, 1
        call    syscall
        
        cmp rax, 0
        jne     write
        
        // 60	exit	sys_exit
        mov     edi, 60
        mov     esi, 0
        call    syscall


// implementation of syscall from ejudge        
syscall:
    // prologue
    push rbx
    push rbp
    push r12
    push r13
    push r14
    push r15
    // also keep r11 and rcx due to 'syscall' on x64 modifies them
    push r11
    push rcx
    // push arguments into memory to reaarange them
    push r9
    push r8
    push rcx
    push rdx
    push rsi
    push rdi
    // first argument is syscall number, move it into rax
    pop rax
    // move arguments into registers to match syscall calling conventions
    pop rdi
    pop rsi
    pop rdx
    pop r10
    pop r8
    // make actual syscall
    syscall
    // epilogue
    pop rcx
    pop r11
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbp
    pop rbx
    ret

