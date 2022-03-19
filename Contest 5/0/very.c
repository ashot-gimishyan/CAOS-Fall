#include <stdio.h>
extern int A[];
void very_important_function(int N){

    int sum = 0;
    int n;
    int i = 0;
    while(N>0)
    {
        scanf("%d", &n);
        sum += n * A[i];
        ++i;
        --N;
    }
    printf("%d", sum);
    
}
