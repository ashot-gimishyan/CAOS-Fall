/*
Problem inf-I-04-0: asm-arm/basics/globalvars-64
Реализуйте на языке ассемблера armv8 (AArch64) функцию calculate, которая вычисляет значение выражения: R = ( A * B ) + ( C * D ), где A, B, C, и D - это глобальные переменные типа uint64_t, объявленные во внешнем модуле компиляции, а R, - глобальная переменная типа uint64_t в текущем модуле компиляции.
*/

        //Секция text используется для хранения кода программы.
        .text
        //Секция data используется для объявления инициализированных данных или констант.
        .data
	.global R
	.global calculate
R:
	.space 8
calculate:
	eor x0, x0, x0 // x0 = 0
	
	adr x1, A // x1 = &A
	ldr x1, [x1] // загрузка x1 = *x1
	adr x2, B // x2 = &B
	ldr x2, [x2] // загрузка x2 = *x2
	mul x1, x1, x2 // x1 = x1 * x2
	add x0, x0, x1 // x0 = x0 + x1
	
	adr x1, C // x1 = &C
	ldr x1, [x1] // загрузка x1 = *x1
	adr x2, D // x2 = &D
	ldr x2, [x2] // загрузка x2 = *x2
	mul x1, x1, x2
	add x0, x0, x1
	
	adr x3, R // x = &B
	str x0, [x3] // *x3 = x0
	ret
