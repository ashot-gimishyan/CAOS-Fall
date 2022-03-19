#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int status, i = 0;
    int n = atoi(argv[1]);
    pid_t pid;

    while (i < n) {
        pid = fork();
        if (pid == 0) {
            if (i < n - 1) {
                printf("%i ", i + 1);
            } else if (i == n - 1) {
                printf("%i\n", i + 1);
            }
            break;
        }
        waitpid(pid, &status, 0);
        ++i;
    }
}
