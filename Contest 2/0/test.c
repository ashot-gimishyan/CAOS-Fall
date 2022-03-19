// C program to do recursive addition
// of two integers
#include <stdio.h>
 
int add(int x, int y) {
    int keep = (x & y) << 1;
    int res = x^y;
 
    // If bitwise & is 0, then there
    // is not going to be any carry.
    // Hence result of XOR is addition.
    if (keep == 0)
        return res;
 
    add(keep, res);
}
 
// Driver code
int main(){
    printf("%d", add(-300, -38));
    return 0;
}
