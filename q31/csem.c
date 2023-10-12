#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    int semid;

    // Generate a unique key for the semaphore (change this as needed)
    key_t key = ftok(".", 'S');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a counting semaphore with an initial value of 5
    semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // Initialize the semaphore value to 5 (counting semaphore)
    union semun {
        int val;
       /* struct semid_ds *buf;
        unsigned short *array;
        struct seminfo *__buf;*/
    } arg;
    arg.val = 5;

    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(1);
    }

    printf("Counting semaphore created and initialized to 5.\n");

    // Use the semaphore for synchronization or other purposes

    // Remove the semaphore when it's no longer needed
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl");
        exit(1);
    }

    return 0;
}

