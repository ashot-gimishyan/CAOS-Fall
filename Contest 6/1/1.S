 .intel_syntax noprefix
.global avx_sin

.text
avx_sin:
    push rbp
    mov rbp, rsp
    mov rax, 0
    vcvtsi2sd xmm5, xmm5, rax
    vcvtsi2sd xmm6, xmm6,rax
    mov rax, 1
    vcvtsi2sd xmm1, xmm1,rax
    vmovsd xmm2, xmm2,xmm0
    vcvtsi2sd xmm3,xmm3, rax
    vcvtsi2sd xmm7, xmm7, rax
    vcvtsi2sd xmm8, xmm8, rax

begin:
    vmovsd xmm4,xmm4, xmm2
    vdivsd xmm4,xmm4, xmm3
    vcomisd xmm4,xmm6
    jz end
    vcomisd xmm8,xmm6
    jz substraction
    jmp addition

    substraction:
        vsubsd xmm5,xmm5, xmm4
        vmovsd xmm8, xmm8,xmm7
        jmp continue
    addition:
        vaddsd xmm5, xmm5, xmm4
        vmovsd xmm8, xmm8,xmm6

continue:

    vmulsd xmm2, xmm2, xmm0
    vmulsd xmm2, xmm2, xmm0
    vaddsd xmm1,  xmm1,xmm7
    vmulsd xmm3, xmm3,xmm1
    vaddsd xmm1, xmm1, xmm7
    vmulsd xmm3, xmm3,xmm1
    jmp begin

end:
    vmovsd xmm0, xmm0, xmm5
    pop rbp
    ret
