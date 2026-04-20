#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
    pid_t pid[2];
    int fd[2];
    int numero_ricevuto;

    if (pipe(fd) == -1) {
        printf("Pipe error!\n");
        exit(1);

    }

    for(int i = 0; i<2; i++) {
        pid[i] = fork();

        if (pid[i] < 0) {
            printf("Fork error!\n");
            exit(1);
        }

        if (pid[i] == 0) {
            close(fd[0]);
            int n = getpid();
            numero_ricevuto = random() % 101; // Genera un numero casuale tra 0 e 100 nel figlio

            printf("Sono il processo figlio[%d]; il mio PID è %d\n", i+1, n);
            printf("Il numero casuale generato è %d\n", numero_ricevuto);
            write(fd[1], &n, sizeof(n));
            exit(0);
        }
    }
    return 0;
}