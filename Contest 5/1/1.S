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

