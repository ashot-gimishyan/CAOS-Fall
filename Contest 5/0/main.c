#include <stdio.h>

int A[5];
extern void very_important_function(int N);

int main()
{
  A[0] = 1;
  A[1] = 1;
  A[2] = 1;
  A[3] = 1;
  A[4] = 1;
  very_important_function(5);
}

