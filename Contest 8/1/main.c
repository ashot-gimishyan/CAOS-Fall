#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>

struct Item {
    int value;
    uint32_t next_pointer;
};

int main(int argc, char** argv)
{
    int in = open(argv[1], O_RDONLY);
    // errno is set to indicate the error
    if (in == -1) {
        return 1;
    }

    struct Item local = {0, -1};

    ssize_t read_bytes = read(in, &local, sizeof(local));

    if (read_bytes <= 0) {
        return 0;
    }

    while (local.next_pointer != 0) {
        printf("%d\n", local.value);
        lseek(in, local.next_pointer, SEEK_SET);
        read(in, &local, sizeof(local));
    }
    printf("%d\n", local.value);
}
