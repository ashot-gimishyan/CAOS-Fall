/*
Problem inf-I-02-2: generic/ieee754/classify
Реализуйте функцию с прототипом:

typedef enum {
    PlusZero      = 0x00,
    MinusZero     = 0x01,
    PlusInf       = 0xF0,
    MinusInf      = 0xF1,
    PlusRegular   = 0x10,
    MinusRegular  = 0x11,
    PlusDenormal  = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN  = 0x30,
    QuietNaN      = 0x31
} float_class_t;

extern float_class_t
classify(double *value_ptr);
      
которая классифицирует специальные значения вещественного числа, на которое указывает value_ptr, в соответствии со стандартом IEEE 754.

При решении допускается использовать только побитовые операции, включая сдвиги.
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    PlusZero = 0x00,
    MinusZero = 0x01,
    PlusInf = 0xF0,
    MinusInf = 0xF1,
    PlusRegular = 0x10,
    MinusRegular = 0x11,
    PlusDenormal = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN = 0x30,
    QuietNaN = 0x31
} float_class_t;

typedef union {
    double d;
    struct {
        uint64_t mantisa : 52;
        unsigned int exponent : 11;
        unsigned int sign : 1;
    } parts;
} double_cast;

float_class_t classify(double* value_ptr)
{
    const int64_t exponent_mask = 0x7FF; // 2**11-1
    const int64_t mantisa_mask = 0x8000000000000; // 2**51
    double_cast a = {.d = *value_ptr};
    unsigned int S = a.parts.sign;
    unsigned int E = a.parts.exponent;
    uint64_t M = a.parts.mantisa;
    if (S == 0 && E == 0 && M == 0) {
        return PlusZero;
    }
    if (S == 1 && E == 0 && M == 0) {
        return MinusZero;
    }
    if (S == 0 && E == exponent_mask && M == 0) {
        return PlusInf;
    }
    if (S == 1 && E == exponent_mask && M == 0) {
        return MinusInf;
    }
    if (E == exponent_mask && ((M & mantisa_mask) == 0) && M != 0) {
        return SignalingNaN;
    }
    if (E == exponent_mask && ((M & mantisa_mask) != 0)) {
        return QuietNaN;
    }
    if (S == 0 && E == 0 && M != 0) {
        return PlusDenormal;
    }
    if (S == 1 && E == 0 && M != 0) {
        return MinusDenormal;
    }
    return S == 0 ? PlusRegular : MinusRegular;
}

int main()
{
    double x = 0;
    printf("\n%lf\t%x", x, classify(&x));
    
    long long i = 0x8000000000000000;
    void* void_i = &i;
    double* px = void_i;
    printf("\n%lf\t%x", *px, classify(px));
    
    i = 0x7FF0000000000000;
    void_i = &i;
    px = void_i;
    printf("\n%lf\t%x", *px, classify(px));
    
    i = 0xFFF0000000000000;
    void_i = &i;
    px = void_i;
    printf("\n%lf\t%x", *px, classify(px));
    
    x = 1;
    printf("\n%lf\t%x", x, classify(&x));
    x = -1;
    printf("\n%lf\t%x", x, classify(&x));
    
    i = 0x000000000000000F;
    void_i = &i;
    px = void_i;
    printf("\n%lf\t%x", *px, classify(px));
    
    i = 0x800000000000000F;
    void_i = &i;
    px = void_i;
    printf("\n%lf\t%x", *px, classify(px));
    
    i = 0x7FFFFFFFFFFFFFFF;
    void_i = &i;
    px = void_i;
    printf("\n%lf\t%x", *px, classify(px));
    
    x = 0;
    x = 0 / x;
    printf("\n%lf\t%x", x, classify(&x));
}
