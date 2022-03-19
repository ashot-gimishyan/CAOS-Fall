#include <sys/types.h>
#include <sys/syscall.h>

long syscall(long number, ...);
ssize_t write(int fd, const void *buf, size_t count) { return syscall(1, fd, buf, count); }
int main() { write(1, "Hello, World!\n", 14); }
void _start() { syscall(SYS_exit, main()); }
