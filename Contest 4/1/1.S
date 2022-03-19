	.data
	var1:
	    .word 0
	var2:
	    .word 0
	scan_format:
	    .string "%d %d"
	print_format:
	    .string "%d\n"

	.text
	.global main
main:
	sub sp, sp, 16
	str x30, [sp, 8]
	
	adr    x0, scan_format
	adr    x1, var1
	adr    x2, var2
	bl scanf
	adr    x1, var1
	adr    x2, var2
	ldr    x1, [x1]
	ldr    x2, [x2]
	add    x3, x1, x2

	adr    x0, print_format	
	mov    x1, x3
	bl     printf
	ldr x30, [sp, 8]
	add sp, sp, 16
	
	mov x0, #0
	ret
