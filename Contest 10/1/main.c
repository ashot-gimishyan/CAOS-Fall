#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct {
    int value;
    uint32_t next_pointer;
} Item;

int main(int argc, char** argv)
{
    // if (argc != 2) { return 1; }
    int f_desc = open(argv[1], O_RDONLY);
    // if (fd <= -1) { return  1; }
    off_t SIZE = lseek(f_desc, 0, SEEK_END);
    if (SIZE == 0) {
        return 1;
    }
    lseek(f_desc, 0, SEEK_SET);

    char* contents = mmap(NULL, SIZE, PROT_READ, MAP_PRIVATE, f_desc, 0);

    Item* tmp = (Item*)contents;
    printf("%i ", tmp->value);

    while (tmp->next_pointer != 0) {
        tmp = (Item*)(contents + tmp->next_pointer);
        printf("%i ", tmp->value);
    }

    munmap(contents, SIZE);
}
