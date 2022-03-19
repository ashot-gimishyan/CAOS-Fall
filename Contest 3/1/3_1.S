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
