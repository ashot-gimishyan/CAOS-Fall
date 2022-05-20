/*
Реализуйте функцию с прототипом:

#include <stdint.h>

extern void mul(ITYPE first, ITYPE second, ITYPE *res, int *CF);
    
в которой ITYPE - это произвольный беззнаковый целочисленный тип данных с неизвестной разрядностью.

Функция должна вычислить произведение значений first и second, результат записать по указателю в выходной параметр res. При возникновении целочисленного переполнения необходимо в выходной параметр CF записать значение 1, в противном случае - значение 0. В случае переполнения результат умножения считается не определенным, то есть его значение может быть любым.

Используйте побитовые операции для вычислений. Операции сложения и вычитания допускаются только применительно к переменным цикла.

На сервер необходимо отправить исходный файл, содержащий только реализацию требуемой функции. Для успешной компиляции и тестирования можно использовать следующий ключ компиляции, задающий требуемый тип: -DITYPE=uint64_t.
*/

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
