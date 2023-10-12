/*
============================================================================
Name : 17
Author : ziya ur raheman 
Description :Write a program to execute ls -l | wc.
b. use fcntl
Date: 7th oct, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int pipe_fd[2];
    
    if (pipe(pipe_fd) == -1) {
        perror("Pipe failed");
        exit(1);
    }
    
    // Create a child process
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("Fork failed");
        exit(1);
    }
    
    if (pid == 0) { // Child process
        // Close the read end of the pipe
        close(pipe_fd[0]);
        
        // Make stdout non-blocking
        int flags = fcntl(STDOUT_FILENO, F_GETFL);
        if (fcntl(STDOUT_FILENO, F_SETFL, flags | O_NONBLOCK) == -1) {
            perror("fcntl");
            exit(1);
        }
        
        // Redirect stdout to the write end of the pipe
        if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        close(pipe_fd[1]);
        
        // Execute 'ls -l' command
        execlp("ls", "ls", "-l", NULL);
        
        // If execlp fails
        perror("execlp");
        exit(1);
    } else { // Parent process
        // Close the write end of the pipe
        close(pipe_fd[1]);
        
        // Make stdin non-blocking
        int flags = fcntl(STDIN_FILENO, F_GETFL);
        if (fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK) == -1) {
            perror("fcntl");
            exit(1);
        }
        
        // Redirect stdin to the read end of the pipe
        if (dup2(pipe_fd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        close(pipe_fd[0]);
        
        // Execute 'wc' command
        execlp("wc", "wc", NULL);
        
        // If execlp fails
        perror("execlp");
        exit(1);
    }
    
    return 0;
}

