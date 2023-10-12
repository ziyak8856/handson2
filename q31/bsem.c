#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h> 

int main() {
    sem_t mySemaphore;

    // Initialize a binary semaphore with an initial value of 1
    if (sem_init(&mySemaphore, 0, 1) == -1) {
        perror("sem_init");
        exit(1);
    }

    printf("Binary semaphore created and initialized.\n");

    // Use the semaphore for synchronization or other purposes

    // Destroy the semaphore when it's no longer needed
    if (sem_destroy(&mySemaphore) == -1) {
        perror("sem_destroy");
        exit(1);
    }

    return 0;
}

