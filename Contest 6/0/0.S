/*
Problem inf-I-06-0: asm-x86/avx/intro-64
Реализуйте на языке ассемблера x86-64 функцию с сигнатурой:

extern double very_important_function(size_t N, const float *A, const float *B, float *R);
Функция вычисляет:

поэлементную сумму R[i]=A[i]+B[i];
среднее арифметическое всех значений R[i], которое является возвращаемым результатом функции.
Гарантируется, что число N больше нуля и кратно 8, а адреса массивов выровнены в памяти по границе 32 байта. Используйте векторные инструкции для вычисления.
*/

        .intel_syntax noprefix
	.text
	.global very_important_function
	
very_important_function:
	xor r10, r10
	xor r11, r11
	xor rax, rax
	vcvtsi2sd xmm0, xmm0,rax
	mov r12, rdi
	mov r13, rsi
	mov r14, rdx
	mov r15, rcx
	
begin:
	cmp r10, r12
	jge end
	vmovaps xmm1, [r13 + 4*r10]
	vmovaps xmm2, [r14 + 4*r10]
	vaddps xmm1, xmm1,xmm2
	vmovaps [r15 + 4*r10], xmm1
	add r10, 4
	movaps xmm1, [r13 + 4*r10]
	movaps xmm2, [r14 + 4*r10]
	vaddps xmm1, xmm1,xmm2
	vmovaps [r15 + 4*r10], xmm1
	vmovaps xmm3, [r13 + 4*r11]
	vmovaps xmm4, [r14 + 4*r11]
	vaddps xmm3,xmm3, xmm4
	vhaddps xmm3, xmm3,xmm3
	vhaddps xmm3,xmm3, xmm3
	vaddss xmm0,xmm0, xmm3
	add r11, 4
	vmovaps xmm3, [r13 + 4*r11]
	vmovaps xmm4, [r14 + 4*r11]
	vaddps xmm3,xmm3, xmm4
	vhaddps xmm3, xmm3,xmm3
	vhaddps xmm3,xmm3, xmm3
	vaddss xmm0, xmm0,xmm3
	add r10, 4
	add r11, 4
	jmp begin
end:
	mov rax, r12
	vcvtsi2ss xmm2,xmm2, rax
	vdivss xmm0, xmm0,xmm2
	vcvtss2sd xmm0, xmm0, xmm0
	ret
