#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct stat _stat;
const int LEN = 512;

int main()
{
    _stat st;
    char ch, buf[LEN];
    char abs_path[LEN];
    char ln_buf[LEN];
    int i = 0, status = -1;

    while ((ch = getchar()) != EOF) {
        buf[i] = ch;
        ++i;

        if (ch == '\n') {
            if (buf[0] == '\n') {
                break;
            }
            buf[i - 1] = '\0';
            status = lstat(buf, &st);
            if (status == 0) {
                if (S_ISLNK(st.st_mode)) {
                    char* ptr = realpath(buf, abs_path);
                    if (ptr != NULL)
                        puts(ptr);
                } else if (S_ISREG(st.st_mode)) {
                    strcpy(ln_buf, "link_to_");
                    strcat(ln_buf, basename(buf));
                    symlink(buf, ln_buf);
                }
            }
            i = 0;
        }
    }
}
