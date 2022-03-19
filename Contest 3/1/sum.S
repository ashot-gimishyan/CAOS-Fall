.text
.global sum

sum:
ldr w3, [x2]
add x2, x2, #4
add w0, w0, w3

sub w1, w1, #1
cmp w1, #0

// if w1 > 0, go to sum:
bgt sum
ret
