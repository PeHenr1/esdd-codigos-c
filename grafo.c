//exercicio
#include <stdio.h>
#include <limits.h>

#define INF INT_MAX 
#define N 4        

int findMinDistance(int dist[], int visited[]) {
    int min = INF, min_index;
    for (int i = 0; i < N; i++) {
        if (!visited[i] && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void dijkstra(int graph[N][N], int start, int end) {
    int dist[N];     
    int visited[N];   
    int predecessor[N]; 

    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        visited[i] = 0;
        predecessor[i] = -1;
    }
    dist[start] = 0; 

    for (int count = 0; count < N - 1; count++) {
        int u = findMinDistance(dist, visited);
        visited[u] = 1;

        for (int v = 0; v < N; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                predecessor[v] = u; 
            }
        }
    }

    printf("Menor distância do vértice %d ao vértice %d: %d\n", start + 1, end + 1, dist[end]);

    printf("Caminho: ");
    int path[N];
    int count = 0;
    for (int v = end; v != -1; v = predecessor[v]) {
        path[count++] = v;
    }
    for (int i = count - 1; i >= 0; i--) {
        printf("%d ", path[i] + 1);
    }
    printf("\n");
}

int main() {
    int graph[N][N] = {
        {0, 8, 1, 0},  // Vértice 1
        {0, 0, 7, 3},  // Vértice 2
        {0, 0, 0, 2},  // Vértice 3
        {0, 0, 0, 0}   // Vértice 4
    };

    // Encontra o menor caminho de 1 para 4
    dijkstra(graph, 0, 3);

    return 0;
}
