#include <fcntl.h>
#include <stdlib.h>
#include <zconf.h>

char TMP_BUFFER[10000];
const int INT_SIZE = sizeof(int);

int _read_(int FILE, char* buf, int for_reading);
int _write_(int FILE, char* buf, int for_writting);

void SortSmallFile(int FILE, int smsz, off_t curr);
int MergeLocal(
    int* l_border,
    int quant1,
    int* r_border,
    int quant2,
    int* array,
    int* l,
    int* r);
void MergeSortFile(int desc1, int f1sz, int desc2, int f2sz, int desc_out);
void MergeSort(int FILE, int l, int r, int file1, int file2);
int compare(const void* num1, const void* num2)
{
    return (*(int*)num1 - *(int*)num2);
}

int main(int argc, char** argv)
{
    int sz = 0;
    if (argc < 2) {
        return 0;
    }

    int FILE = open(argv[1], O_RDWR);
    int file1 = open("file1", O_RDWR | O_CREAT, 0664); // 0ugo rw-rw-r
    int file2 = open("file2", O_RDWR | O_CREAT, 0664); // 0ugo rw-rw-r

    if (FILE == -1) {
        return 1;
    }

    sz = lseek(FILE, 0, SEEK_END) / INT_SIZE;
    MergeSort(FILE, 0, sz, file1, file2);
}

int _read_(int FILE, char* buf, int for_reading)
{

    size_t bytes_read = 0;
    ssize_t currently_read;

    while (bytes_read < for_reading) {
        currently_read = read(FILE, buf + bytes_read, for_reading - bytes_read);
        if (currently_read == -1) {
            return -1;
        }
        if (currently_read == 0) {
            return bytes_read;
        }
        bytes_read += currently_read;
    }
    return for_reading;
}

int _write_(int FILE, char* buf, int for_writting)
{
    size_t bytes_written = 0;
    ssize_t currently_written;

    while (bytes_written < for_writting) {
        currently_written =
            write(FILE, buf + bytes_written, for_writting - bytes_written);
        if (currently_written == -1) {
            return -1;
        }
        bytes_written += currently_written;
    }
    return for_writting;
}

void SortSmallFile(int FILE, int smsz, off_t curr)
{
    int buf[smsz];
    _read_(FILE, (char*)buf, INT_SIZE * smsz);
    qsort(buf, smsz, INT_SIZE, compare);
    lseek(FILE, curr, SEEK_SET);
    _write_(FILE, (char*)buf, INT_SIZE * smsz);
}

int MergeLocal(
    int* l_border,
    int quant1,
    int* r_border,
    int quant2,
    int* array,
    int* l,
    int* r)
{
    int idx2 = 0, idx1 = 0;
    int merged = 0;
    while (idx1 < quant1 && idx2 < quant2) {
        if (l_border[idx1] <= r_border[idx2]) {
            array[merged] = l_border[idx1++];
        } else {
            array[merged] = r_border[idx2++];
        }
        merged++;
    }

    *r = idx2;
    *l = idx1;

    return merged;
}

void MergeSortFile(int desc1, int f1sz, int desc2, int f2sz, int desc_out)
{
    lseek(desc1, 0, SEEK_SET);
    lseek(desc2, 0, SEEK_SET);

    int file1_buf[10000];
    int file2_buf[10000];
    int target_buf[10000 * 2];

    int min1, min2, min1_, min2_, merged;
    while ((f1sz * f2sz) != 0) {
        min2 = (f2sz < 10000) * f2sz + (f2sz >= 10000) * 10000;
        min1 = (f1sz < 10000) * f1sz + (f1sz >= 10000) * 10000;

        _read_(desc2, (char*)file2_buf, min2 * INT_SIZE);
        _read_(desc1, (char*)file1_buf, min1 * INT_SIZE);

        int merged = MergeLocal(
            file1_buf, min1, file2_buf, min2, target_buf, &min1_, &min2_);

        f2sz -= min2_;
        f1sz -= min1_;

        lseek(desc2, -(min2 - min2_) * INT_SIZE, SEEK_CUR);
        lseek(desc1, -(min1 - min1_) * INT_SIZE, SEEK_CUR);

        _write_(desc_out, (char*)target_buf, merged * INT_SIZE);
    }

    if ((f1sz + f2sz) != 0) {
        int tail_fd = desc1 * (f1sz > 0) + desc2 * (f2sz > 0);
        int tail_sz = f1sz + f2sz;

        int count = tail_sz * INT_SIZE;
        while (count) {
            int move = (10000 < count) * 10000 + (10000 >= count) * count;
            _read_(tail_fd, TMP_BUFFER, move);
            _write_(desc_out, TMP_BUFFER, move);
            count -= move;
        }
    }
}

void MergeSort(int FILE, int l, int r, int file1, int file2)
{
    int diff = r - l;
    if (diff <= 10000) {
        off_t curr = lseek(FILE, l * INT_SIZE, SEEK_SET);
        SortSmallFile(FILE, diff, curr);
    } else {
        int middle = (l + r) / 2;

        MergeSort(FILE, l, middle, file1, file2);
        MergeSort(FILE, middle, r, file1, file2);

        lseek(FILE, l * INT_SIZE, SEEK_SET);
        lseek(file1, 0, SEEK_SET);
        lseek(file2, 0, SEEK_SET);

        int count = INT_SIZE * (middle - l);
        while (count) {
            int move = (10000 < count) * 10000 + (10000 >= count) * count;
            _read_(FILE, TMP_BUFFER, move);
            _write_(file1, TMP_BUFFER, move);
            count -= move;
        }

        lseek(FILE, middle * INT_SIZE, SEEK_SET);
        count = INT_SIZE * (r - middle);
        while (count) {
            int move = (10000 < count) * 10000 + (10000 >= count) * count;
            _read_(FILE, TMP_BUFFER, move);
            _write_(file2, TMP_BUFFER, move);
            count -= move;
        }

        lseek(FILE, l * INT_SIZE, SEEK_SET);
        MergeSortFile(file1, middle - l, file2, r - middle, FILE);
    }
}
