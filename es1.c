#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Errore nella fork
        fprintf(stderr, "Fork fallita\n");
        return 1;
    } 
    else if (pid == 0) {
        // Processo Figlio
        printf("Sono il FIGLIO! Il mio PID è %d e il PID di mio padre è %d\n", getpid(), getppid());
        sleep(2); // Simula del lavoro
        printf("FIGLIO: Ho finito, termino.\n");
        exit(0);
    } 
    else {
        // Processo Padre
        printf("Sono il PADRE! Il mio PID è %d. Ho creato un figlio con PID %d\n", getpid(), pid);
        printf("PADRE: Aspetto che il figlio finisca...\n");
        
        wait(NULL); // Attende la terminazione del figlio
        
        printf("PADRE: Il figlio ha terminato. Esco anche io.\n");
    }

    return 0;
}
