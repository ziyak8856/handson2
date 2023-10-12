#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Define the message structure
struct message {
    long mtype;     // Message type (must be greater than 0)
    char mtext[100]; // Message content
};

int main() {
    key_t key;
    int msgid;
    struct message msg;

    // Generate a unique key for the message queue (use the same key as the previous example)
    if ((key = ftok("/tmp", 'A')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Get the message queue ID
    if ((msgid = msgget(key, 0)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Prepare the message
    msg.mtype = 1;  // Message type (greater than 0)
    strcpy(msg.mtext, "Hello, Message Queue!");

    // Send the message to the queue
    if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Message sent to the queue.\n");

    return 0;
}

