#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    const char *fifoPath = "my_fifo";
    int fd;
 if (mkfifo(fifoPath, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
    // Open the FIFO for writing
    fd = open(fifoPath, O_WRONLY);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char message[100];
    while (1) {
        printf("Enter a message to send (or type 'exit' to quit): ");
        fgets(message, sizeof(message), stdin);

        if (strcmp(message, "exit\n") == 0) {
            break;
        }

        // Write to the FIFO
        write(fd, message, strlen(message));
    }

    close(fd);
    return 0;
}

