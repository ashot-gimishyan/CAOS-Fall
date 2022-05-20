/*
Problem inf-I-05-1: asm-x86/arrays-64
Реализуйте функцию на языке ассемблера x86-64 с сигнатурой:

extern void sum(size_t N, const int *A, const int *B, int *R);
      
Функция вычисляет значения Ri=Ai+Bi для всех i от 0 до N.

Память для хранения массива-результата уже выделена.

*/

        .intel_syntax noprefix
	.text
	.global sum
	
sum:
Begin:
	sub edi, 1
	cmp edi, 0
	jl End
	mov ebx, [esi + 4 * edi]
	add ebx, [edx + 4 * edi]
	mov [ecx + 4 * edi], ebx
	jmp Begin
	
End:
	ret

