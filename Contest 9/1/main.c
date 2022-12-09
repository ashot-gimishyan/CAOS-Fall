#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int good_const = 64;

int exec_permission_enabled(char* buf)
{
    return access(buf, X_OK) == 0;
}

// Read the first four bytes.
// If they are equal to \x7fELF , it's an ELF file.
int is_elf(int descriptor)
{
    char buf[good_const];
    const char ELF[] = {0x7f, 'E', 'L', 'F', '\0'};

    lseek(descriptor, 0, SEEK_SET);
    if (read(descriptor, buf, 4) != 4)
        return 0;

    buf[4] = '\0';
    return strcmp(ELF, buf) == 0;
}

int is_correct(int descriptor)
{
    lseek(descriptor, 0, SEEK_SET);
    int i = 2;
    char buf[good_const];
    char interpreter[good_const];

    int readb = read(descriptor, buf, good_const);
    if (readb == -1 || readb < 3)
        return 0;

    if (buf[0] != '#')
        return 0;
    else if (buf[1] != '!') {
        return 0;
    }

    do {
        if (buf[i] == ' ')
            break;
        if (buf[i] == '\n')
            break;
        interpreter[i - 2] = buf[i];
        ++i;
    } while (1);

    interpreter[i - 2] = '\0';
    return exec_permission_enabled(interpreter);
}

int main()
{
    char fname[good_const];
    int descriptor;

    while (fgets(fname, good_const, stdin)) {
        if (fname[strlen(fname) - 1] == '\n') {
            fname[strlen(fname) - 1] = '\0';
        }
        if (exec_permission_enabled(fname)) {
            descriptor = open(fname, O_RDONLY);
            if (!(is_elf(descriptor) || is_correct(descriptor))) {
                puts(fname);
            }
        }
    }
}
