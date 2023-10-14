/*
============================================================================
Name : 19d
Author : ziya ur raheman 
Description :Create a FIFO file by use mkfifo
Date: 7th oct, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *fifo_path = "ziyafifo"; // Replace with the desired FIFO file path
    
    // Create the FIFO file using the mkfifo system call
    if (mkfifo(fifo_path, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }
    
    printf("FIFO file created successfully: %s\n", fifo_path);
    
    return 0;
}

