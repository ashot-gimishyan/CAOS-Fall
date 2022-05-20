/*
Problem inf-I-02-0: simulation/alu-sum
Реализуйте функцию с прототипом:

#include <stdint.h>

extern void sum(ITYPE first, ITYPE second, ITYPE *res, int *CF);
    
в которой ITYPE - это произвольный беззнаковый целочисленный тип данных с неизвестной разрядностью.

Функция должна вычислить сумму значений first и second, результат записать по указателю в выходной параметр res. При возникновении целочисленного переполнения необходимо в выходной параметр CF записать значение 1, в противном случае - значение 0.

Используйте побитовые операции для вычислений. Операции сложения и вычитания допускаются только применительно к переменным цикла.

На сервер необходимо отправить исходный файл, содержащий только реализацию требуемой функции. Для успешной компиляции и тестирования можно использовать следующий ключ компиляции, задающий требуемый тип: -DITYPE=uint64_t.
*/

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
