#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int serverSocket, clientSocket, bytesRead;
    struct sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(clientAddr);
    char buffer[1024] = {0};
    char* response = "Hello from server";
    int opt = 1;

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        printf("Socket creation failed\n");
        exit(1);
    }

    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        printf("Set socket options failed\n");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Bind failed\n");
        exit(1);
    }

    if (listen(serverSocket, 3) < 0) {
        printf("Listen failed\n");
        exit(1);
    }

    if ((clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, (socklen_t*)&addrLen)) < 0) {
        printf("Accept failed\n");
        exit(1);
    }

    bytesRead = read(clientSocket, buffer, sizeof(buffer));
    printf("Client: %s\n", buffer);
    send(clientSocket, response, strlen(response), 0);
    printf("Response sent\n");

    return 0;
}