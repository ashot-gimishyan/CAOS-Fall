#include <sys/types.h>
#include <sys/syscall.h>

long syscall(long number, ...);

ssize_t read(int fd, void *buf, size_t count) { return syscall(0, fd, buf, count); }
ssize_t write(int fd, const void *buf, size_t count) { return syscall(1, fd, buf, count); }

int main() {
  int ret;
	char in[4096];
	do {
		ret = read(0, in, sizeof(in) - 1);
		write(1, in, ret);
	} while(ret != 0);
}

void _start() {syscall(SYS_exit, main()); }
