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

typedef struct Node{
    int vertex;
    int distance;
}node;

// Function to check if an array is in non-decreasing order
int isundecreaes(int *a,int n){
    for(int i=0;i<n-1;i++){
        if(distance[a[i]-1]>distance[a[i+1]-1]){
            return 0;
        }
    }
    return 1;
}

typedef struct Heap {
    node a[100000] ;
    int heapSize;
} *heap;

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

// Function to insert a node into the heap
void insert(heap h, int vertex, int distance) {
    // Insert the vertex and distance into the heap
    h->heapSize++;
    int i = h->heapSize;
    h->a[i].vertex = vertex;
    h->a[i].distance = distance;

    // Move the element up the heap until the heap property is satisfied
    while (i > 1 && h->a[i / 2].distance > h->a[i].distance) {
        node temp = h->a[i];
        h->a[i] = h->a[i / 2];
        h->a[i / 2] = temp;
        i = i / 2;
    }
}

// Function to extract the minimum node from the heap
node extractMin(heap h) {
    // Extract the minimum element from the heap
    node minNode = h->a[1];
    h->a[1] = h->a[h->heapSize];
    h->heapSize--;

    // Move the last element down the heap until the heap property is satisfied
    int i = 1;
    while (2 * i <= h->heapSize) {
        int left = 2 * i;
        int right = 2 * i + 1;
        int min = left;
        if (right <= h->heapSize && h->a[right].distance < h->a[left].distance) {
            min = right;
        }
        if (h->a[i].distance <= h->a[min].distance) {
            break;
        }
        node temp = h->a[i];
        h->a[i] = h->a[min];
        h->a[min] = temp;
        i = min;
    }
    return minNode;
}

// Function to create a heap
heap create_heap() {
    heap h = (heap)malloc(sizeof(struct Heap));
    h->heapSize = 0;
    return h;
}

// Function to check if the heap is empty
int is_empty(heap h) {
    return h->heapSize == 0;
}

// Function to perform Dijkstra's algorithm using heap
void dijkstra_heap(graph g,int start) {
    // Create a min heap to store distances of vertices
    heap h = create_heap();

    // Initialize all distances to infinity
    for (int i = 0; i < g->nv; i++) {
        distance[i] = inf;
        visited[i] = 0;
    }

    // Set the distance of the source vertex to 0
    distance[start] = 0;

    // Insert the source vertex into the heap
    insert(h, start, 0);

    // Perform Dijkstra's algorithm
    while (!is_empty(h)) {
        // Extract the vertex with the minimum distance from the heap
        node minNode = extractMin(h);
        int minVertex = minNode.vertex;

        // Mark the extracted vertex as visited
        visited[minVertex] = 1;

        // Update the distances of the adjacent vertices
        for (int v = 0; v < g->nv; v++) {
            if (!visited[v] && g->e[minVertex][v] != inf && distance[minVertex] + g->e[minVertex][v] < distance[v]) {
                // Update the distance of vertex v
                distance[v] = distance[minVertex] + g->e[minVertex][v];

                // Insert distance of vertex v into the heap
                insert(h, v, distance[v]);
            }
        }
    }
    free(h);
}

// Function to perform Dijkstra's algorithm using file input
void dijkstra_file(graph g, FILE* file,int start) {
    // Read the source vertex for the test case
    for (int i = 0; i < g->nv; i++) {
        distance[i] = inf;
        visited[i] = 0;
    }

    // Set the distance of the source vertex to 0 and mark it as visited
    distance[start] = 0;
    visited[start] = 1;

    // Create a min heap to store distances of vertices
    heap h = create_heap();

    // Insert the source vertex into the heap
    insert(h, start, 0);

    // Perform Dijkstra's algorithm
    while (!is_empty(h)) {
        // Extract the vertex with the minimum distance from the heap
        node minNode = extractMin(h);
        int minVertex = minNode.vertex;

        // Mark the extracted vertex as visited
        visited[minVertex] = 1;

        // Update the distances of the adjacent vertices
        for (int v = 0; v < g->nv; v++) {
            if (!visited[v] && g->e[minVertex][v] != inf && distance[minVertex] + g->e[minVertex][v] < distance[v]) {
                // Update the distance of vertex v
                distance[v] = distance[minVertex] + g->e[minVertex][v];

                // Insert distance of vertex v into the heap
                insert(h, v, distance[v]);
            }
        }
    }
    free(h);
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
    int k;
    // Read the number of test cases
    if (method == 1) {
        scanf("%d", &k);
    } else {
        fscanf(file, "%d", &k);
    }

    // Perform Dijkstra's algorithm for each test case
    for (int i = 0; i < k; i++) {
        for(int j=0;j<g->nv;j++){
            if(method==1){
                scanf("%d",&test[j]);
            }else{
                fscanf(file,"%d",&test[j]);
            }
        }
        if (method == 1) {
            dijkstra_heap(g,test[0]-1);
        } else {
            dijkstra_file(g, file,test[0]-1);
        }
        if(isundecreaes(test,n)){
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    if (method == 2) {
        fclose(file);
    }

    return 0;
}
