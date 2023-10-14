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

    // Open the FIFO for both reading and writing
    fd = open(fifoPath, O_RDWR);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char message[100];
    while (1) {
        // Read from the FIFO
        ssize_t bytesRead = read(fd, message, sizeof(message));
        if (bytesRead <= 0) {
            printf("FIFO has been closed by the other program.\n");
            break;
        }

        printf("Received: %.*s", (int)bytesRead, message);

        // Enter your response
        printf("Enter a reply (or type 'exit' to quit): ");
        fgets(message, sizeof(message), stdin);

        if (strcmp(message, "exit\n") == 0) {
            break;
        }

        // Write your response to the FIFO
        write(fd, message, strlen(message));
    }

    close(fd);
    return 0;
}

