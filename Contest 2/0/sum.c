#include <stdint.h>

extern void sum(uint64_t first, uint64_t second, uint64_t* res, int* CF)
{
    uint64_t result;
    uint64_t f_copy = first;
    uint64_t s_copy = second;

    while (1) {
        if (second == 0) {
            (*res) = first;
            return;
        }
        result = first ^ second;
        second = (first & second) << 1;
        first = result;
    }
    *res = result;
    if (*res < f_copy || *res < s_copy)
        *CF = 1;
    else
        *CF = 0;
}
