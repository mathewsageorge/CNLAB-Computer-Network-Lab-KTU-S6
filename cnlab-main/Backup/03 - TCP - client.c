#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int clientSocket, bytesRead;
    struct sockaddr_in serverAddr;
    char buffer[1024] = {0};
    char* message = "Hello from client";

    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation failed\n");
        return -1;
    }

    serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Connection failed\n");
        return -1;
    }

    send(clientSocket, message, strlen(message), 0);
    printf("Message sent\n");
    bytesRead = read(clientSocket, buffer, sizeof(buffer));
    printf("Server: %s\n", buffer);

    return 0;
}