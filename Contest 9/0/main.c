#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

typedef struct stat _stat;

int main()
{
    _stat st;
    off_t size = 0;
    int i = 0, status = -1;
    char ch, buf[256];
    while ((ch = getchar()) != EOF) {
        buf[i] = ch;
        ++i;
        if (ch == '\n') {
            if (buf[0] == '\n') {
                break;
            }
            buf[i - 1] = '\0';
            status = lstat(buf, &st);
            if ((status == 0) && S_ISREG(st.st_mode)) {
                size += st.st_size;
            }
            i = 0;
        }
    }
    printf("%ld", size);
}
