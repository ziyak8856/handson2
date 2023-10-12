#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main() {
    int msqid;
    struct msqid_ds msq_info;
    key_t key;
    
    // Create a message queue key
    key = ftok("/tmp", 'A'); // You can choose a different path and id
    
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Get the message queue ID
    msqid = msgget(key, 0666 | IPC_CREAT);
    
    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    // Get the current permissions and information
    if (msgctl(msqid, IPC_STAT, &msq_info) == -1) {
        perror("msgctl");
        exit(1);
    }

    // Change the permissions
    msq_info.msg_perm.mode = 0644;  // New permissions (e.g., read and write for owner, read for others)

    if (msgctl(msqid, IPC_SET, &msq_info) == -1) {
        perror("msgctl");
        exit(1);
    }

    printf("Message queue permissions changed to 0644\n");

    return 0;
}

