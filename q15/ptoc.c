/*
============================================================================
Name : 15
Author : ziya ur raheman 
Description :Write a simple program to send some data from parent to the child process
Date: 7th oct, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//note:
//If the child process executes first, it closes the write end of the pipe (pipe_fd[1]) and then attempts to read from the read end of the pipe (pipe_fd[0]). At this point, the read operation in the child will block because there is no data written to the pipe by the parent yet.

int main() {
    int pipe_fd[2];
    char message[] = "Hello, Child!";

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { // Child process
        close(pipe_fd[1]); // Close write end of the pipe in the child

        char buffer[256];
        ssize_t bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("Child process received: %s\n", buffer);

        close(pipe_fd[0]); // Close read end of the pipe in the child
        exit(EXIT_SUCCESS);
    } else { // Parent process
        close(pipe_fd[0]); // Close read end of the pipe in the parent

        // Write data to the pipe
        ssize_t bytes_written = write(pipe_fd[1], message, strlen(message));
        if (bytes_written == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(pipe_fd[1]); // Close write end of the pipe in the parent
    }

    return 0;
}

