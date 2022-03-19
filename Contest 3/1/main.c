#include <stddef.h>
#include <stdio.h>

extern int sum(int x0, size_t N, int *x);

int main(int argc, char const *argv[]) {
  int X[] = {1,2,3,4,5};
  int result = sum(0, sizeof(X)/sizeof(int), X);
  printf("%d\n", result );
}
