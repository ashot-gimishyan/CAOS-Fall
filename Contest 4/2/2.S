	.text
	.global main

main:
	sub sp, sp, 16
	str x30, [sp, 8]

loop:
	bl getchar_unlocked
	cmp x0, 0
	blt end

        cmp x0, 48
        blt loop
        cmp x0, 57
        bgt loop

        bl putchar_unlocked
        b loop
end:
	ldr x30, [sp, 8]
	add sp, sp, 16
	sub x0, x0, x0
	ret
