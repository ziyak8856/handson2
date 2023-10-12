#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_BUF_SIZE 1024

int main() {
    const char *fifo_path = "ziyafifo"; // Replace with the path to your FIFO
    char buffer[MAX_BUF_SIZE];
    
    // Open the FIFO for reading
    int fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    
    // Read data from the FIFO
    int num_bytes = read(fd, buffer, sizeof(buffer));
    if (num_bytes == -1) {
        perror("read");
        exit(1);
    }
    
    // Close the FIFO
    close(fd);
    
    // Null-terminate the received data to treat it as a string
    buffer[num_bytes] = '\0';
    
    printf("Received message: %s\n", buffer);
    
    return 0;
}

