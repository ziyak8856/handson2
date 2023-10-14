#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>

void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    char buffer[1024];

    while (1) {
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            printf("Connection closed by the client.\n");
            break;
        }

        printf("Received from client: %s", buffer);

        // Send a response back to the client
        printf("Enter a response: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(client_socket, buffer, strlen(buffer), 0);
        bzero(buffer, sizeof(buffer));
    }

    close(client_socket);
    free(arg);
    pthread_exit(NULL);
}

int main() {
    int server_socket, new_socket;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    pthread_t tid;

    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket < 0) {
        perror("Error in socket");
        exit(1);
    }

   
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);  // Replace with your desired port
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in binding");
        exit(1);
    }
    // Bind the socket
   
    // Listen for incoming connections
    listen(server_socket, 10);
    printf("Server is listening on port 12345\n");

    addr_size = sizeof(new_addr);

    while (1) {
        // Accept a connection from a client
        new_socket = accept(server_socket, (struct sockaddr *)&new_addr, &addr_size);
        printf("Connection accepted from %s:%d\n", inet_ntoa(new_addr.sin_addr), ntohs(new_addr.sin_port));

        // Create a new thread to handle the client
        int *client_socket = (int *)malloc(sizeof(int));
        *client_socket = new_socket;
        if (pthread_create(&tid, NULL, handle_client, (void *)client_socket) != 0) {
            perror("Error in creating thread");
        }
    }

    close(server_socket);

    return 0;
}

