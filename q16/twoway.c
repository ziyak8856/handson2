/*
============================================================================
Name : 16
Author : ziya ur raheman 
Description :Write a program to send and receive data from parent to child vice versa. Use two way
communication.
Date: 7th oct, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int parent_to_child_pipe[2];
    int child_to_parent_pipe[2];
    char message_to_child[] = "Hello, Child!";
    char message_to_parent[] = "Hello, Parent!";
    char buffer[256];

   
    if (pipe(parent_to_child_pipe) == -1 || pipe(child_to_parent_pipe) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { // Child process
        close(parent_to_child_pipe[1]); // Close write end from parent to child
        close(child_to_parent_pipe[0]); // Close read end from child to parent

        // Read from parent
        ssize_t bytes_read = read(parent_to_child_pipe[0], buffer, sizeof(buffer));
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        printf("Child received from parent: %s\n", buffer);

        // Write to parent
        ssize_t bytes_written = write(child_to_parent_pipe[1], message_to_parent, strlen(message_to_parent));
        if (bytes_written == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(parent_to_child_pipe[0]);
        close(child_to_parent_pipe[1]);
        exit(EXIT_SUCCESS);
    } else { // Parent process
        close(parent_to_child_pipe[0]); // Close read end from parent to child
        close(child_to_parent_pipe[1]); // Close write end from child to parent

        // Write to child
        ssize_t bytes_written = write(parent_to_child_pipe[1], message_to_child, strlen(message_to_child));
        if (bytes_written == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // Read from child
        ssize_t bytes_read = read(child_to_parent_pipe[0], buffer, sizeof(buffer));
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        printf("Parent received from child: %s\n", buffer);

        close(parent_to_child_pipe[1]);
        close(child_to_parent_pipe[0]);
    }

    return 0;
}

