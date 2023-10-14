/*
============================================================================
Name : 20
Author : ziya ur raheman 
Description :Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 7th oct, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    const char *fifo_path = "ziyafifo"; // Replace with the path to your FIFO
    const char *message = "Hello, FIFO!"; // Message to send
    
    // Open the FIFO for writing
    int fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    
    // Write the message to the FIFO
    if (write(fd, message, strlen(message)) == -1) {
        perror("write");
        exit(1);
    }
    
    // Close the FIFO
    close(fd);
    
    printf("Message sent!");
    
    return 0;
}

