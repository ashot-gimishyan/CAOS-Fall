/*
Problem inf-I-04-2: asm-arm/basics/char-filter-digits-64
Напишите программу на языке ассемблера armv8 (AArch64), которая читает со стандартного потока ввода последовательность символов, и выводит только те из них, которые являются десятичными цифрами от 0 до 9.

Можно использовать функции стандартной библиотеки языка Си: getchar_unlocked и putchar_unclocked.

В качестве точки входа можно считать функцию main.
*/

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
