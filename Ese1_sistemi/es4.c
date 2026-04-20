#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main () {
    pid_t pid;
    int fd[2];
    int numero_ricevuto;


    if (pipe(fd) == -1) {
        printf("Pipe error!\n");
        exit(1);
    }

    pid = fork();

    if (pid == 0) {
        close(fd[0]);
        srand(time(NULL)); // Inizializza il generatore di numeri casuali
        int n = rand() % 101; // Genera un numero casuale tra 0 e 100 nel figlio
        int pid_figlio = getpid();

        printf("Sono il processo figlio; il mio PID è %d\n", pid_figlio);
        printf("Il numero casuale generato è %d\n", n);
        write(fd[1], &n, sizeof(n));
        close(fd[1]);
        exit(0);
    } else {
        close(fd[1]);
        read(fd[0], &numero_ricevuto, sizeof(numero_ricevuto));
        close(fd[0]);
        printf("Sono il processo padre; il mio PID è %d\n", getpid());
        printf("Il PID del processo figlio è %d\n", pid);
        printf("Il numero casuale ricevuto dal figlio è %d\n", numero_ricevuto);
        wait(NULL); // Aspetta la terminazione del figlio
    }
    return 0;
}

