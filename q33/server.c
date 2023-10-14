#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_socket, new_socket;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[1024];

    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket < 0) {
        perror("Error in socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8081); // You can change the port
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the host and port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in binding");
        exit(1);
    }

    // Listen for incoming connections
    listen(server_socket, 10);
    printf("Server is listening on port 12345\n");

    addr_size = sizeof(new_addr);
    new_socket = accept(server_socket, (struct sockaddr*)&new_addr, &addr_size);
    printf("Connection accepted from %s:%d\n", inet_ntoa(new_addr.sin_addr), ntohs(new_addr.sin_port));

    while (1) {
        // Receive data from the client
        ssize_t bytes_received = recv(new_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            printf("Connection closed by the client.\n");
            break;
        }

        printf("Received from client: %s", buffer);

        // Send a response back to the client
        bzero(buffer, sizeof(buffer));
        printf("Enter a response:\n ");
        fgets(buffer, sizeof(buffer), stdin);
        send(new_socket, buffer, strlen(buffer), 0);
        bzero(buffer, sizeof(buffer));
    }

    close(new_socket);
    close(server_socket);

    return 0;
}

