#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
    pid_t pid_figlio1, pid_figlio2;
    int child_status1, child_status2;
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);

    pid_figlio1 = fork();

    if (pid_figlio1 == 0) {
        // figlio 1
        close(fd1[1]);  //chiudo l'estremità di scrittura della prima pipe
        close(fd2[0]);  //chiudo l'estremità di lettura della seconda pipe

        printf("Sono il processo figlio 1; il mio pid è: %d\n", (int) getpid());
        
        pid_t pid_padre;
        read(fd1[0], &pid_padre, sizeof(pid_padre));
        printf("Sono il processo figlio 1; il pid di mio padre è: %d\n", pid_padre);
        write(fd2[1], &pid_padre, sizeof(pid_padre));
        exit(0);
    } else {
        pid_figlio2 = fork();

    if(pid_figlio2 == 0) {// figlio 2                                                                 
            close(fd1[1]); //chiudo l'estremità di scrittura della prima pipe
            close(fd2[1]); // chiudo l'estremità di scrittura della seconda pipe

            printf("Sono il processo figlio 2; il mio pid è: %d\n", (int) getpid());

            pid_t pid_padre;
            read(fd2[0], &pid_padre, sizeof(pid_padre));
            printf("Sono il processo figlio 2; il pid di mio padre è: %d\n", pid_padre);
            exit(0);
    } else {
        // padre
        close(fd1[0]); // chiudo l'estremità di lettura della prima pipe
        close(fd2[0]); // chiudo l'estremità di lettura della seconda pipe
        close(fd2[1]); // chiudo l'estremità di scrittura della seconda pipe

        printf("Sono il processo padre; il mio pid è: %d\n", (int) getpid());
        
        pid_t pid_padre = getpid();
        write(fd1[1], &pid_padre, sizeof(pid_padre));

        wait(&child_status1);
        wait(&child_status2);
    }
}
return 0;
}
