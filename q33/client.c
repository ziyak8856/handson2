#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket < 0) {
        perror("Error in socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8081);  // You can change the port
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Replace with the actual server IP or hostname

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in connection");
        exit(1);
    }

    while (1) {
        // Send a message to the server
        printf("Enter a message (or 'exit' to quit): ");
        bzero(buffer, sizeof(buffer));
        fgets(buffer, 1024, stdin);
        send(client_socket, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "exit\n") == 0) {
            printf("Connection closed by the client.\n");
            break;
        }

        // Receive the server's response
        recv(client_socket, buffer, 1024, 0);
        printf("Received from server: %s", buffer);
        bzero(buffer, sizeof(buffer));
    }

    close(client_socket);

    return 0;
}

