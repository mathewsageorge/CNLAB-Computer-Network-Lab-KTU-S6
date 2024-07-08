#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
    int serverSocket;
    struct sockaddr_in serverAddr, clientAddr;

    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Socket creation failed\n");
        exit(1);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    memset(&clientAddr, 0, sizeof(clientAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (const struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Bind failed\n");
        exit(1);
    }

    int clientLen = sizeof(clientAddr);

    int size_mat[6];
    if ((recvfrom(serverSocket, size_mat, sizeof(size_mat), MSG_WAITALL, (struct sockaddr*)&clientAddr, &clientLen)) < 0) {
        perror("Size not received");
        return -1;
    }
    int r1 = size_mat[0];
    int c1 = size_mat[1];
    int r2 = size_mat[2];
    int c2 = size_mat[3];
    int matrix_A[r1][c1];
    int matrix_B[r2][c2];
    int matrix_R[r1][c2];
    if ((recvfrom(serverSocket, matrix_A, sizeof(matrix_A), MSG_WAITALL, (struct sockaddr*)&clientAddr, &clientLen)) < 0) {
        perror("Matrix A not received");
        return -1;
    }
    printf("Matrix A received\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            printf("%d ", matrix_A[i][j]);
        }
        printf("\n");
    }
    if ((recvfrom(serverSocket, matrix_B, sizeof(matrix_B), MSG_WAITALL, (struct sockaddr*)&clientAddr, &clientLen)) < 0) {
        perror("Matrix B not received");
        return -1;
    }
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
    sendto(serverSocket, matrix_R, sizeof(matrix_R), MSG_CONFIRM, (const struct sockaddr*)&clientAddr, clientLen);

    return 0;
}