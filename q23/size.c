#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/types.h>

int main() {
    // Get the maximum number of files a process can open
    struct rlimit rlp;
    if (getrlimit(RLIMIT_NOFILE, &rlp) == 0) {
        printf("Maximum number of files that can be opened by a process: %ld\n", rlp.rlim_cur);
    } else {
        perror("getrlimit");
    }

    int pipefd[2];
    if (pipe(pipefd) == 0) {
        long pipe_size = fpathconf(pipefd[0], _PC_PIPE_BUF);
        printf("Size of a pipe (circular buffer): %ld bytes\n", pipe_size);
        close(pipefd[0]);
        close(pipefd[1]);
    } else {
        perror("pipe");
    }

    return 0;
}

