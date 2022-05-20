/*Problem inf-I-06-2: asm-x86/avx/dot-product-64
Реализуйте на языке ассемблера x86-64 функцию с сигнатурой:

extern float dot_product(size_t N, const float *A, const float *B);
которая вычисляет скалярное произведение векторов A и B.

Гарантируется, что N больше нуля, но не гарантируется, что N кратно восьми.

Значения исходных векторов хранятся в произвольных адресах памяти, поэтому выравнивание для них не гарантируется.

Необходимо минимизировать количество выполняемых вычислительных инструкций, используя векторные вычисления. Доступен набор команд AVX.
*/

.intel_syntax noprefix
    .text
    .global dot_product

// extern float dot_product(int N, const float *A, const float *B);
//   xmm0                     rax           rcx             rdx

dot_product:
    push        rbp
    mov         rbp, rsp
    push        rbx
    push        rsi

    mov         rbx, 0                 // cnt = 0
    vcvtsi2ss    xmm0, xmm0, rbx       // xmm0 = result = 0

begin:
    mov         rsi, rbx
    add         rsi, 4
    cmp         rsi, rax                // while (cnt + 4 < N)
    jge         new_begin         // movups from AVX
    movups      xmm1, [rcx + rbx * 4]   // xmm1 = A[cnt..cnt+3]
    movups      xmm2, [rdx + rbx * 4]   // xmm2 = B[cnt..cnt+3]
    vdpps        xmm1,xmm1, xmm2, 0xF1  // xmm1 = sum(A[cnt + i]*B[cnt + i])
    vaddss       xmm0, xmm0, xmm1       // result += dot_product (xmm1)
    add         rbx, 4                  // cnt += 4
    jmp         begin

new_begin:
    cmp         rbx, rax                 // while (cnt < N)
    jz          end
    vmovss       xmm1, [rcx + rbx * 4]   // xmm1 = A[cnt]
    vmovss       xmm2, [rdx + rbx * 4]   // xmm2 = B[cnt]
    vmulss       xmm1,xmm1, xmm2         // xmm1 = A[cnt] * B[cnt]
    vaddss       xmm0, xmm0,xmm1         // result += xmm1
    add         rbx, 1                   // ++cnt
    jmp         new_begin
    
end:
    pop         rsi
    pop         rbx
    pop         rbp
    ret
