#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main() {
    key_t key;
    int shmid;
    char *shmaddr;
    struct shmid_ds shminfo;

    // Generate a unique key for the shared memory segment
    key = ftok(".", 'a');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a new shared memory segment or get an existing one
    shmid = shmget(key, 1024, IPC_CREAT | IPC_EXCL | 0666); // 1024 bytes with read-write permission
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment with read-write permission
    shmaddr = (char *)shmat(shmid, NULL, 0);
    if (shmaddr == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Write data to the shared memory segment
    strcpy(shmaddr, "Hello, Shared Memory!");

    printf("Data written to shared memory: %s\n", shmaddr);

    // Attach the shared memory segment with read-only permission (O_RDONLY)
    shmaddr = (char *)shmat(shmid, NULL, SHM_RDONLY);
    if (shmaddr == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Try to overwrite the shared memory (this should fail)
    //it will give the segmen fault
    strcpy(shmaddr, "This should not work!");

    // Detach from the shared memory segment
    shmdt(shmaddr);

    // Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, &shminfo) == -1) {
        perror("shmctl");
        exit(1);
    }

    return 0;
}

