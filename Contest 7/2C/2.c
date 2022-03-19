#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

const int BUF = 10000;

long syscall(long number, ...);

ssize_t read(int fd, void *buf, size_t count) {
  return syscall(SYS_read, fd, buf, count);
}
ssize_t write(int fd, const void *buf, size_t count) {
  return syscall(SYS_write, fd, buf, count);
}

int brk(void *addr) { return syscall(SYS_brk, addr); }

void _start() {
  char end = '\n';
  char *str = (char *)syscall(SYS_brk, 0); // получить текущий конец адресного пространства
  int size = 1;
  int to_read = BUF;
  int i, tmp;

  brk(str + to_read);
  while (1) {
    int ret = read(SYS_read, str + size, to_read);
    if (ret == 0) {
      break;
    }
    size += ret;
    if (size >= to_read) {
      brk(str + to_read + BUF);
      to_read += BUF;
    }
  }

  tmp = size;
  if (size > 0) {
    i = size - 1;
    while (i > -1) {
      if (i == 0 || *(str + i) == end) {
        write(SYS_write, str + i + 1, tmp - i - 1);
        if (i > 0 && i < size - 1) {
          write(SYS_write, &end, 1);
        }
        tmp = i;
      }
      i--;
    }
  }

  syscall(SYS_exit, 0);
}
