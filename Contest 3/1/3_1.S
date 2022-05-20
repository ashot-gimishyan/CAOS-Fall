/*
Problem inf-I-03-1: asm-arm/basics/memaccess-64
Реализуйте на языке ассемблера armv8 (AArch64) функцию с сигнатурой:

int sum(int x0, size_t N, int *X)
Функция должна вычислять значение x0+∑xi, где 0≤i<N

Обратите внимание на то, что тип int имеет размер 32 бит, а тип size_t - 64 бит.
*/

        .text
        .global sum
        
sum:
        ldr x3, [x2]
        add x2, x2, #4
        add x0, x0, x3
        
        sub w1, w1, #1
        cmp w1, #0
        
        // if w1 > 0, go to sum:
        bgt sum
        mov w1, w0
        ret
