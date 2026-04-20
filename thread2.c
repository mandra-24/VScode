#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

void print_x(void *unused) {
    while(1) {
        printf("Hello from thread2!\n");
        fflush(stdout);
        sleep(1);
    }
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, print_x, NULL);
    while(1) {
        printf("Hello from thread2!\n");
        fflush(stdout);
        sleep(1);
    }
    return 0;
}