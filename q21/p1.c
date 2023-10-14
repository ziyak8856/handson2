/*
============================================================================
Name : 20
Author : ziya ur raheman 
Description :Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 7th oct, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    const char *fifoPath = "my_fifo";
    int fd;

    // Create the FIFO if it doesn't exist
    if (mkfifo(fifoPath, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Open the FIFO for both reading and writing
    fd = open(fifoPath, O_RDWR);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char message[100];
    while (1) {
        printf("Enter a message (or type 'exit' to quit): ");
        fgets(message, sizeof(message), stdin);

        if (strcmp(message, "exit\n") == 0) {
            break;
        }

        // Write to the FIFO
        write(fd, message, strlen(message));

        // Read from the FIFO
        ssize_t bytesRead = read(fd, message, sizeof(message));
        if (bytesRead <= 0) {
            printf("FIFO has been closed by the other program.\n");
            break;
        }

        printf("Received: %.*s", (int)bytesRead, message);
    }

    close(fd);
    //unlink(fifoPath); // Remove the FIFO when done
    return 0;
}

