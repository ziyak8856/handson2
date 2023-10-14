/*
============================================================================
Name : 22
Author : ziya ur raheman 
Description :Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
Date: 7th oct, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

int main() {
    const char *fifoPath = "my_fifo";
    int fd;
 
    // Open the FIFO for reading
    fd = open(fifoPath, O_RDONLY | O_NONBLOCK);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct timeval timeout;
    fd_set readfds;

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);

        // Set the timeout to 10 seconds
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;

        int ready = select(fd + 1, &readfds, NULL, NULL, &timeout);

        if (ready < 0) {
            perror("select");
            break;
        } else if (ready == 0) {
            printf("Timeout: No data received within 10 seconds.\n");
            break;
        } else {
            if (FD_ISSET(fd, &readfds)) {
                char message[100];
                ssize_t bytesRead = read(fd, message, sizeof(message));

                if (bytesRead <= 0) {
                    printf("FIFO has been closed by the other program.\n");
                    break;
                }

                printf("Received: %.*s", (int)bytesRead, message);
            }
        }
    }

    close(fd);
    return 0;
}

