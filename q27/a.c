#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>

// Define the message structure
struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // ftok() to generate a unique key
    key = ftok("progfile", 65);

    // msgget() to create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // Receive the message with flag set to 0
    if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }

    // Display the received message
    printf("Received message: %s\n", message.msg_text);

    // Remove the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}

