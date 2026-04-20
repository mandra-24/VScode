#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
    pid_t pid;
    int fd[2];

    if (pipe(fd) == -1) {
        printf("Pipe error!\n");
        exit(1);
    }

    pid = fork();

    if (pid == 0) {
        close(fd[0]);
        int n = getpid();
        printf("Sono il processo figlio; il mio PID è %d\n", n);
        write(fd[1], &n, sizeof(n));
        exit(0);
    } else {
        close(fd[1]);
        read(fd[0], &pid, sizeof(pid));
        printf("Sono il processo padre; il mio PID è %d\n", getpid());
        printf("Il PID del processo figlio è %d\n", pid);
    }
    return 0;
}