#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

extern int64_t f(int64_t A, int64_t B, int64_t C, int64_t x);

int main(int argc, char const *argv[]) {
  int64_t A, B,C,x;
  scanf("%"SCNd64" %"SCNd64" %"SCNd64" %"SCNd64, &A, &B, &C, &x);

  int64_t y = f(A,B,C,x);
  printf("%"PRId64"\n", y);
}
