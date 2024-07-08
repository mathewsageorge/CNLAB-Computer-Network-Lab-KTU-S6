#include <stdio.h>
#define INF 1000

void shortest_path(int n, int cost[n][n], int src) {
    int dist[n], visited[n], last[n];
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        last[i] = src;
    }
    dist[src] = 0;

    for (int count = 0; count < n; count++) {
        int min = INF, u = -1;
        for (int i = 0; i < n; i++)
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }

        if (u == -1) break;
        visited[u] = 1;

        for (int i = 0; i < n; i++)
            if (!visited[i] && dist[u] + cost[u][i] < dist[i]) {
                dist[i] = dist[u] + cost[u][i];
                last[i] = u;
            }
    }

    printf("Routing Table of Node %d\n", src + 1);
    printf("Destination\tCost\tNext Hop\n");
    for (int i = 0; i < n; i++) {
        if (i == src) {
            printf("%d\t\t-\t\t-\n", i + 1);
        } else if (dist[i] == INF) {
            printf("%d\t\t-\t\t-\n", i + 1);
        } else if (last[i] == src) {
            printf("%d\t\t%d\t\t-\n", i + 1, dist[i]);
        } else {
            printf("%d\t\t%d\t\t%d\n", i + 1, dist[i], last[i] + 1);
        }
    }

    for (int i = 0; i < n; i++)
        if (i != src)
            printf("The cost from router %d to %d is %d\n", src + 1, i + 1, dist[i]);
}

int main() {
    int n;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    int cost[n][n];

    printf("Enter the cost matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cost[i][j] = 0;
            } else {
                printf("Cost from %d to %d: ", i + 1, j + 1);
                scanf("%d", &cost[i][j]);
                if (cost[i][j] == 0) cost[i][j] = INF;
            }
        }

    int src;
    printf("Enter the source node: ");
    scanf("%d", &src);
    shortest_path(n, cost, src - 1);

    return 0;
}