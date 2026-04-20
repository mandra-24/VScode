#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid[2];
    int N = 2;

    //Versione corretta:

    for(int i = 0; i<N; i++) {
        pid[i] = fork();

        if (pid[i] == 0) {
            printf("Sono il processo figlio[%d]; il mio PID è %d\n", i+1, getpid());
            printf("Il PID di mio padre è %d\n", getppid());
            exit(0);
        } else if (pid[i] < 0) {
            printf("Fork error!\n");
            exit(1);
        }
    }

    printf("Sono il processo padre; il mio PID %d\n", getpid());
    
    // Stampa i PID dei figli
    for(int j = 0; j<N; j++) {
        printf("PID processo figlio[%d]: %d\n", j+1, pid[j]);
    }

    // Aspetta che entrambi i figli terminino
    for(int j = 0; j<N; j++) {
        wait(NULL);
    }


    /* ESercizio 2 versione sbagliata: il processo padre incrementa il contatore e stampa il PID
     del figlio N volte, ma non aspetta che il figlio termini. Il processo figlio incrementa il 
     contatore e stampa il proprio PID e quello del padre N volte.
    pid = fork();

    if (pid == 0) {
        for(int i=0; i<N; i++) {
            counter++;
            printf("Sono il processo figlio[%d]; il mio PID è %d\n", counter, getpid());
            printf("Il PID di mio padre è %d\n", getppid());
        }
    } else if (pid > 0) {
        printf("Sono il processo padre; il mio PID %d\n", getpid());
        for(int j=0; j<N; j++) {
            counter++;
            printf("PID processo figlio[%d]: %d\n", counter, pid);
        }
    } else {
        printf("Fork error!\n");
    }
    return 0; */
}