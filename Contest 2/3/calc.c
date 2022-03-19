#include <stdint.h>
#include <stdio.h>

int main()
{
    int64_t res = 0, tmp = 0;
    unsigned long long bit_check = 1;
    int i;

    char ch;
    while (1) {
        ch = getchar();
        if (ch == EOF)
            break;
        if ('0' <= ch && ch <= '9') {
            tmp |= (bit_check << (ch - '0'));
        } else if ('A' <= ch && ch <= 'Z') {
            tmp |= (bit_check << (ch - 'A' + 10));
        } else if ('a' <= ch && ch <= 'z') {
            tmp |= (bit_check << (ch - 'a' + 36));
        } else if (ch == '|') {
            res |= tmp;
            tmp = 0;
        } else if (ch == '&') {
            res &= tmp;
            tmp = 0;
        } else if (ch == '^') {
            res ^= tmp;
            tmp = 0;
        } else if (ch == '~') {
            res = ((~res) & ((bit_check << 62) - 1));
            tmp = 0;
        } else
            continue;
    }

    for (i = 0; i < 10; ++i) {
        if ((res & (bit_check << i)) != 0) {
            printf("%d", i);
        }
    }
    for (i = 10; i < 36; ++i) {
        if ((res & (bit_check << i)) != 0) {
            printf("%c", i + 'A' - 10);
        }
    }
    for (i = 36; i < 62; ++i) {
        if ((res & (bit_check << i)) != 0) {
            printf("%c", i + 'a' - 36);
        }
    }
    printf("\n");
}
