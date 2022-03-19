	.text
	.global solve
solve:
	mov	w4, #0	
start:
	cmp	w4, #255	
	bge	stop

	mov	w5, w0		
	mul	w5, w5, w4	
	mul	w5, w5, w4	
	mul	w5, w5, w4	

	mov	w6, w1		
	mul	w6, w6, w4	
	mul	w6, w6, w4	
	add	w5, w5, w6	

	mov	w6, w2		
	mul	w6, w6, w4	
	add	w5, w5, w6	
	add	w5, w5, w3	

	cmp	w5, #0
	beq	stop

	add	w4, w4, #1	
	b	start
	
stop:
	mov	w0, w4
	ret
