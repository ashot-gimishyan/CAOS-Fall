#include <stdint.h>

extern void mul(uint64_t first, uint64_t second, uint64_t* res, int* CF)
{
    const uint64_t a = (first < second) ? first : second;
    const uint64_t b = (first > second) ? first : second;
    uint64_t sum = 0;
    uint64_t a_copy = a;
    uint64_t res_tmp = 0;
    for (int i = 0; i < b; ++i) {
        while (1) {
            if (a_copy == 0) {
                break;
            }
            res_tmp = sum ^ a_copy;
            a_copy = (sum & a_copy) << 1;
            sum = res_tmp;
        }
        a_copy = a;
    }
    *res = sum;
    // always a*b >= a and a*b >= b for unsigned a and b
    if (*res < a || *res < b)
        *CF = 1;
    else
        *CF = 0;
}
