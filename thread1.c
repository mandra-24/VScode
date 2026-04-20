#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    while(1) {
        printf("Hello from thread1!\n");
        fflush(stdout);
        sleep(1);
    }
    return 0;
}