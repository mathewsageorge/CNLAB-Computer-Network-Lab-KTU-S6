#include <stdio.h>
#define INF 1000

int main() {
    int n;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    int cost[n][n];

    printf("Enter the cost matrix from:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cost[i][j] = 0;
            } else {
                printf("%d -> %d: ", i + 1, j + 1);
                scanf("%d", &cost[i][j]);
                if (cost[i][j] == 0)
                    cost[i][j] = INF;
            }
        }

    int src;
    printf("Enter the source node: ");
    scanf("%d", &src);
    src -= 1;

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
        if (i == src || dist[i] == INF) {
            printf("%d\t\t-\t-\n", i + 1);
        } else if (last[i] == src) {
            printf("%d\t\t%d\t-\n", i + 1, dist[i]);
        } else {
            printf("%d\t\t%d\t%d\n", i + 1, dist[i], last[i] + 1);
        }
    }

    printf("The cost from router:\n");
    for (int i = 0; i < n; i++)
        if (i != src)
            printf("(%d -> %d) is %d\n", src + 1, i + 1, dist[i]);

    return 0;
}
