#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        printf("Sono il processo figlio; il mio PID è %d\n", getpid());
        printf("Il PID di mio padre è %d\n", getppid());
    } else {
        printf("Sono il processo padre; il mio PID %d\n", getpid());
        printf("Ho creato un figlio con PID %d\n", pid);
    }
    return 0;
}