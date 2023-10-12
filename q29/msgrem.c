#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    int msgid;

    // Key for the message queue (change this to your desired key)
    key_t key = ftok("/tmp", 'A');
    
    // Check if the key was generated successfully
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Get the message queue ID
    msgid = msgget(key, 0);

    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    printf("Message queue removed successfully.\n");
    return 0;
}

