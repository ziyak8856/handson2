/*
============================================================================
Name : 17.b
Author : ziya ur raheman 
Description :Write a program to execute ls -l | wc.
b. use dup2
Date: 7th oct, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
    //The child process will execute the "ls -l" command, and the parent process will execute the "wc" command.
    //child will
    if (pid == 0) { // Child process
        // Close the read end of the pipe
        close(pipe_fd[0]);
        
        // Redirect stdout to the write end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        
        // Execute 'ls -l' command
        execlp("ls", "ls", "-l", NULL);
        
        // If execlp fails
        perror("execlp");
        exit(1);
    } else { // Parent process
        // Close the write end of the pipe
        close(pipe_fd[1]);
        
        // Redirect stdin to the read end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        
        // Execute 'wc' command
        execlp("wc", "wc", NULL);
        
        // If execlp fails
        perror("execlp");
        exit(1);
    }
    
    return 0;
}

