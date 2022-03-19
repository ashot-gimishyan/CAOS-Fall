#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

extern double avx_sin(double x);

int32_t main(int32_t argc, char **argv) {
    double ans = avx_sin(-5.0);
    printf("%.15lf", ans);

}
