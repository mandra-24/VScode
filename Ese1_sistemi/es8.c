#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    pid_t pid_figlio1, pid_figlio2;
    int child_status1, child_status2;
    int n;
    int fd1[2], fd2[2];
    pipe(fd1);

    pid_figlio1 = fork();

    if (pid_figlio1 == 0) {
        // processo figlio 1
        // chiudo il lato lettura della pipe 1
        close(fd1[0]); 

        printf("Inserisci un numero fra 0 e 31: ");
        scanf("%d", &n);

        if (n < 0 || n > 31) {
            printf("Numero non valido. Inserisci un numero fra 0 e 31.\n");
            exit(1);
        }

        // scrivo il numero nella pipe 1
        write(fd1[1], &n, sizeof(n));
        close(fd1[1]);
        exit(0);

    } else {

        pipe(fd2);
        pid_figlio2 = fork();

         if (pid_figlio2 == 0) {
            // processo figlio 2
            // chiudo entrambi i lati della pipe 1 e il lato scrittura della pipe 2
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[1]);

            // leggo il numero dalla pipe 2
            read(fd2[0], &n, sizeof(n));
            close(fd2[0]);

            // L'utente inserisce un PID valido
            int PID;
            printf("Inserisci un PID: ");
            scanf("%d", &PID);

            // Invio il signal al PID specificato
            if (kill(PID, n) == -1) {
                perror("kill");
                exit(1);
            }
            printf("Signal %d inviato al processo %d\n", n, PID);

            exit(0);
        } else {
            // processo padre
            close(fd1[1]);  // chiudo il lato scrittura della pipe 1
            close(fd2[0]);  // chiudo il lato lettura della pipe 2

            // leggo il numero dalla pipe 1
            read(fd1[0], &n, sizeof(n));
            close(fd1[0]);
            printf("Numero ricevuto dal processo figlio 1: %d\n", n);

            // scrivo il numero nella pipe 2
            write(fd2[1], &n, sizeof(n));
            close(fd2[1]);

            wait(&child_status1);
            wait(&child_status2);
        }
    }
    return 0;
}