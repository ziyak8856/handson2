#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msgid;

    // Generate a unique key for the message queue
    if ((key = ftok("/tmp", 'A')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Get the message queue ID
    if ((msgid = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    struct msqid_ds queue_info;

    // Get the message queue information
    if (msgctl(msgid, IPC_STAT, &queue_info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    // Access permissions
    printf("Access Permissions (in octal): 0%o\n", queue_info.msg_perm.mode);

    // UID and GID
    printf("Owner's UID: %d\n", queue_info.msg_perm.uid);
    printf("Owner's GID: %d\n", queue_info.msg_perm.gid);

    // Time-related attributes
    printf("Time of last message sent: %ld seconds since epoch\n", (long)queue_info.msg_stime);
    printf("Time of last message received: %ld seconds since epoch\n", (long)queue_info.msg_rtime);
    printf("Time of last change in the message queue: %ld seconds since epoch\n", (long)queue_info.msg_ctime);

    // Size of the queue
    printf("Size of the queue: %ld bytes\n", (long)queue_info.msg_qbytes);

    // Number of messages in the queue
    printf("Number of messages in the queue: %ld\n", (long)queue_info.msg_qnum);

    // Maximum number of bytes allowed
    printf("Maximum number of bytes allowed per message: %ld\n", (long)queue_info.msg_qbytes);

    // PID of the last msgsnd and msgrcv operations
    printf("PID of the last msgsnd operation: %d\n", queue_info.msg_lspid);
    printf("PID of the last msgrcv operation: %d\n", queue_info.msg_lrpid);

    return 0;
}

