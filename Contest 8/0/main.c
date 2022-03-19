// If the input file does not exist, then exit with code 1.
// If it is not possible to create one of the output files, then exit with
// code 2. If any other I / O errors occur, exit with code 3.
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int write_bytes(int fd, char* buffer, int to_write);

int main(int argc, char** argv)
{
    if (argc < 3) {
        return 3;
    }

    char read_buf[4096];
    char digits_buf[4096];
    char nodigits_buf[4096];
    int ptr1, ptr2, i;
    ssize_t currently_read;
    int check, check_write_1, check_write_2;
    int in, out_yes, out_no;
    in = open(argv[1], O_RDONLY);

    // we get error and no such file or directory
    int count = (in == -1) + (errno == ENOENT);
    if (count == 2) {
        return 1;
    }

    // we get other error
    if (count == 1) {
        return 3;
    }

    // O_CREAT := create file if does not exist
    out_yes = open(argv[2], O_CREAT | O_WRONLY, 0640);
    out_no = open(argv[3], O_CREAT | O_WRONLY, 0640);

    if (out_yes == -1 || out_no == -1) {
        return 2;
    }

    while (1) {
        for (size_t bytes_read = 0; bytes_read < 4096;) {
            currently_read = read(in, read_buf + bytes_read, 4096 - bytes_read);

            if (currently_read == -1) {
                check = -1;
                break;
            }
            if (currently_read == 0) {
                check = bytes_read;
                break;
            }
            bytes_read += currently_read;
        }

        if (check == 0) {
            break;
        }

        ptr1 = ptr2 = 0;

        i = 0;
        while (i < check) {
            if (read_buf[i] >= 48 && read_buf[i] <= 57) {
                digits_buf[ptr1++] = read_buf[i];
            } else {
                nodigits_buf[ptr2++] = read_buf[i];
            }
            ++i;
        }

        check_write_1 = write_bytes(out_yes, digits_buf, ptr1);
        check_write_2 = write_bytes(out_no, nodigits_buf, ptr2);
        if (check_write_1 == -1 || check_write_2 == -1)
            return 3;
    }

    close(in);
    close(out_yes);
    close(out_no);
}

int write_bytes(int fd, char* buffer, int to_write)
{
    size_t bytes_written = 0;
    ssize_t currently_written;

    while (bytes_written < to_write) {
        currently_written =
            write(fd, buffer + bytes_written, to_write - bytes_written);
        if (currently_written == -1) {
            return -1;
        }
        bytes_written += currently_written;
    }
    return to_write;
}
