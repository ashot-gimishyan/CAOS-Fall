#include <inttypes.h>
#include <stdio.h>
#include <windows.h>

struct Item {
    int value;
    uint32_t next_pointer;
};

typedef struct Item MyItem;

int main(int argc, char** argv)
{
    DWORD rdb;
    MyItem local;
    local.value = 0;
    local.next_pointer = -1;

    HANDLE in;
    in = CreateFileA(
        TEXT(argv[1]),         // file to open
        GENERIC_READ,          // open for reading
        0,                     // for shared reading
        0,                     // default protection
        OPEN_EXISTING,         // only existing file
        FILE_ATTRIBUTE_NORMAL, // regular file
        0                      // no template attributes
    );

    ReadFile(
        in,           // file descriptor
        &local,       // data buffer
        sizeof local, // number of bytes to read
        &rdb,         // number of bytes read
        0             // asynchronous buffer
    );

    if (rdb <= 0) {
        return 0;
    }

    while (local.next_pointer != 0) {
        printf("%i\n", local.value);
        // SetFilePointer moves the position pointer in the open file
        SetFilePointer(
            in,                 // file descriptor
            local.next_pointer, // pointer move bytes
            0,                  // pointer move bytes
            0                   // reference point is the beginning of the file
        );

        ReadFile(in, &local, sizeof local, &rdb, 0);
    }
    printf("%i\n", local.value);
}
