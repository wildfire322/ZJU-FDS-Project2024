#include<stdio.h>
#include<stdlib.h>
#define inf 101

// Array to store the shortest distance from the source vertex to each vertex
int distance[1001];

// Array to store the test cases
int test[1001];

// Array to keep track of visited vertices
int visited[1001];

// Structure to represent a graph
typedef struct Graph {
    int nv; // Number of vertices
    int ne; // Number of edges
    int e[1001][1001]; // Adjacency matrix to store edge weights
} *graph;

// Function to create a graph
graph create(int nv, int ne) {
    graph g = (graph)malloc(sizeof(struct Graph));
    g->nv = nv;
    g->ne = ne;

    // Initialize all edge weights to infinity
    for (int i = 0; i < nv; i++) {
        for (int j = 0; j < nv; j++) {
            g->e[i][j] = inf;
        }
    }
    return g;
}

// Function to find the vertex with minimum distance from the source vertex
int findmin(graph g) {
    int min = inf;
    int minindex = 0;
    for (int i = 0; i < g->nv; i++) {
        if (!visited[i] && distance[i] < min) {
            min = distance[i];
            minindex = i;
        }
    }
    return minindex;
}

// Function to perform Dijkstra's algorithm
int dijkstra(graph g) {
    int kk, z;

    // Read the test case values and initialize distance and visited arrays
    for (int i = 0; i < g->nv; i++) {
        scanf("%d", &kk);
        distance[i] = inf;
        visited[i] = 0;
        test[i] = kk - 1;
    }

    // Set the distance of the source vertex to 0 and mark it as visited
    distance[test[0]] = 0;
    visited[test[0]] = 1;

    // Update the distance array with the weights of the edges connected to the source vertex
    for (int i = 0; i < g->nv; i++) {
        if (i != test[0] && g->e[test[0]][i] != inf) {
            distance[i] = g->e[test[0]][i];
        }
    }

    // Perform Dijkstra's algorithm for the remaining vertices
    for (int i = 1; i < g->nv; i++) {
        z = findmin(g);

        // If the distance of the current vertex is not equal to the distance of the previous vertex, return 0
        if (distance[z] != distance[test[i]]) {
            return 0;
        }
        // Otherwise, the vertice could form a dijkstra sequence ,continue with the algorithm
        // Mark the current vertex as visited
        visited[test[i]] = 1;

        // Update the distance array with the weights of the edges connected to the current vertex
        for (int j = 0; j < g->nv; j++) {
            if (!visited[j] && g->e[test[i]][j] != inf && distance[test[i]] + g->e[test[i]][j] < distance[j]) {
                distance[j] = distance[test[i]] + g->e[test[i]][j];
            }
        }
    }
    return 1;
}

// Function to perform Dijkstra's algorithm with file input
int dijkstra_file(graph g, FILE* file){
    int kk, z;

    // Read the test case values from the file and initialize distance and visited arrays
    for (int i = 0; i < g->nv; i++) {
        fscanf(file, "%d", &kk);
        distance[i] = inf;
        visited[i] = 0;
        test[i] = kk - 1;
    }

    // Set the distance of the source vertex to 0 and mark it as visited
    distance[test[0]] = 0;
    visited[test[0]] = 1;

    // Update the distance array with the weights of the edges connected to the source vertex
    for (int i = 0; i < g->nv; i++) {
        if (i != test[0] && g->e[test[0]][i] != inf) {
            distance[i] = g->e[test[0]][i];
        }
    }

    // Perform Dijkstra's algorithm for the remaining vertices
    for (int i = 1; i < g->nv; i++) {
        z = findmin(g);

        // If the distance of the current vertex is not equal to the distance of the previous vertex, return 0
        if (distance[z] != distance[test[i]]) {
            return 0;
        }

        // Mark the current vertex as visited
        visited[test[i]] = 1;

        // Update the distance array with the weights of the edges connected to the current vertex
        for (int j = 0; j < g->nv; j++) {
            if (!visited[j] && g->e[test[i]][j] != inf && distance[test[i]] + g->e[test[i]][j] < distance[j]) {
                distance[j] = distance[test[i]] + g->e[test[i]][j];
            }
        }
    }
    return 1;
}

int main() {
    int m, n;
    FILE* file;

    // Ask the user for the input method
    printf("Enter 1 for manual input, 2 for file input: ");
    int method;
    scanf("%d", &method);
    getchar(); // This is to capture the newline character after entering the method

    if (method == 2) {
        // If the user selects file input, open the file
        file = fopen("test_data.txt", "r");
        if (file == NULL) {
            fprintf(stderr, "Failed to open the file\n");
            return EXIT_FAILURE;
        }
    }

    // Read the number of vertices and edges
    if (method == 1) {
        scanf("%d %d", &n, &m);
    } else {
        fscanf(file, "%d %d", &n, &m);
    }

    // Create a graph
    graph g = create(n, m);

    // Read the edges and their weights
    for (int i = 0; i < m; i++) {
        int a, b, c;
        if (method == 1) {
            scanf("%d %d %d", &a, &b, &c);
        } else {
            fscanf(file, "%d %d %d", &a, &b, &c);
        }
        g->e[a - 1][b - 1] = c;
        g->e[b - 1][a - 1] = c;
    }

    // Read the number of test cases
    int k,u;
    if (method == 1) {
        scanf("%d", &k);
    } else {
        fscanf(file, "%d", &k);
    }

    // Perform Dijkstra's algorithm for each test case
    for (int i = 0; i < k; i++) {
        if (method == 1) {
            u = dijkstra(g);
        } else {
            u = dijkstra_file(g, file);
        }
        if (u == 1) {
            printf("Yes\n");
        }// If the function returns 1, which means it is a probable Dijkstra Sequence, so print "Yes"
        else {
            printf("No\n");
        }// If the function returns 0, which means it is not a probable Dijkstra Sequence, so print "No"
    }
    if (method == 2) {
        fclose(file);
    }
    return 0;
}