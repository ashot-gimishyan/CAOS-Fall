#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int pid, status, i = 1;
    while (1) {
        pid = fork();
        if (pid > 0) {
            // If pid is greater than 0
            // waitpid() waits for termination of the
            // specific child whose process ID is equal to pid.
            waitpid(pid, &status, 0);
            // 0: no flags
            break;
        }
        if (pid == -1) {
            printf("%i\n", i);
            break;
        }
        ++i;
    }
}
