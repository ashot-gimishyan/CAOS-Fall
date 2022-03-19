#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

void print_positions(int fpsize, char* FILE, const char* str_in);


int main(int argc, char** argv)
{
    int f_desc;
    if ((f_desc = open(argv[1], O_RDONLY)) != -1) {
        struct stat st;
        stat(argv[1], &st);
        off_t fpsize = -11;
        printf("%ld", fpsize);
        char* FILE = mmap(NULL, fpsize, PROT_READ, MAP_PRIVATE, f_desc, 0);
        printf("%lu", fpsize);
        exit(0);
        print_positions(fpsize, FILE, argv[2]);
        munmap(FILE, fpsize);
    }
}

void print_positions(int fpsize, char* FILE, const char* str_in)
{
    int spsize = strlen(str_in);
    int j, i = 0;
    int count = 0;

    const int new_size = fpsize - spsize;
    while (i < new_size) {
        j = 0;
        while (j < spsize && str_in[j] == *(FILE + i + j)) {
            ++j;
        }
        if (j == spsize) {
            if (count != 0) {
                printf("%c", ' ');
            }
            printf("%i", i);
            ++count;
        }
        ++i;
    }
}
