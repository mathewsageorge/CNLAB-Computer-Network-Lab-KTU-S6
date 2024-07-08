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
    int clientSocket;
    struct sockaddr_in serverAddr;

    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Socket creation failed\n");
        exit(1);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    int r1, c1, r2, c2;
    printf("Matrix A\n");
    printf("Row:\t");
    scanf("%d", &r1);
    printf("Column:\t");
    scanf("%d", &c1);
    printf("Matrix B\n");
    printf("Row:\t");
    scanf("%d", &r2);
    printf("Column:\t");
    scanf("%d", &c2);
    int size_mat[6];
    size_mat[0] = r1;
    size_mat[1] = c1;
    size_mat[2] = r2;
    size_mat[3] = c2;
    int matrix_A[r1][c1];
    int matrix_B[r2][c2];
    int matrix_R[r1][c2];
    if (r2 != c1) {
        printf("Not a valid Matrix");
        return -1;
    }
    printf("Enter Matrix A elements:\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%d", &matrix_A[i][j]);
        }
    }
    printf("Enter Matrix B elements:\n");
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            printf("B[%d][%d]: ", i, j);
            scanf("%d", &matrix_B[i][j]);
        }
    }
    
    int serverLen = sizeof(serverAddr);

    sendto(clientSocket, size_mat, sizeof(size_mat), MSG_CONFIRM, (const struct sockaddr*)&serverAddr, sizeof(serverAddr));
    sendto(clientSocket, matrix_A, sizeof(matrix_A), MSG_CONFIRM, (const struct sockaddr*)&serverAddr, sizeof(serverAddr));
    sendto(clientSocket, matrix_B, sizeof(matrix_B), MSG_CONFIRM, (const struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if ((recvfrom(clientSocket, matrix_R, sizeof(matrix_R), MSG_WAITALL, (struct sockaddr*)&serverAddr, &serverLen)) < 0) {
        perror("Matrix Result not received");
        return -1;
    }
    printf("Matrix Result received:\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            printf("%d ", matrix_R[i][j]);
        }
        printf("\n");
    }
    close(clientSocket);

    return 0;
}