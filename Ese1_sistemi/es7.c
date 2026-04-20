#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>   
#include <string.h>

int main() {
    pid_t pid_figlio;
    int child_status;
    int fd[2];
    pipe(fd);

    pid_figlio = fork();

    if (pid_figlio == 0) {
        //processo figlio
        close(fd[1]);  //chiudo la pipe lato scrittura
        char buffer[100];  //buffer per ricevere la stringa dal processo padre
        read(fd[0], buffer, sizeof(buffer));
        printf("Stringa ricevuta dal processo padre: %s\n", buffer);
        execlp("mv", "mv", "esempio2.c", buffer, NULL);  //rinomino il file esempio2.c in pane.c
        exit(0);
    } else {
        //processo padre
        close(fd[0]);  //chiudo la pipe lato lettura
        char stringa[] = "pane.c";   //stringa da inviare al processo figlio che servira per rinominare il file esempio2.c in pane.c
        write(fd[1], stringa, sizeof(stringa));
        wait(&child_status);
    }
    return 0;
}