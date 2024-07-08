#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(clientAddr);
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

    int size_mat[4];
    read(clientSocket, size_mat, sizeof(size_mat));

    int r1 = size_mat[0];
    int c1 = size_mat[1];
    int r2 = size_mat[2];
    int c2 = size_mat[3];
    int matrix_A[r1][c1];
    int matrix_B[r2][c2];
    int matrix_R[r1][c2];

    read(clientSocket, matrix_A, sizeof(matrix_A));
    printf("Matrix A received\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            printf("%d ", matrix_A[i][j]);
        }
        printf("\n");
    }

    read(clientSocket, matrix_B, sizeof(matrix_B));
    printf("Matrix B received\n");
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            printf("%d ", matrix_B[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c2; j++) {
            matrix_R[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                matrix_R[i][j] += matrix_A[i][k] * matrix_B[k][j];
            }
        }
    printf("Matrix Result\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            printf("%d ", matrix_R[i][j]);
        }
        printf("\n");
    }

    send(clientSocket, matrix_R, sizeof(matrix_R), 0);

    return 0;
}