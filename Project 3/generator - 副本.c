// generator.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate and print out a random permutation of vertices
void printRandomPermutation(int n, FILE *file) {
    int a[n];
    for (int i = 0; i < n; i++) { // Fill the array with 'n' vertices
        a[i] = i + 1;
    }
    for (int i = n - 1; i > 0; i--) { // Shuffle array elements
        int j = rand() % (i + 1);
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
    for (int i = 0; i < n; i++) { // Print the randomized array
        fprintf(file, "%d ", a[i]);
    }
    fprintf(file, "\n");
}

int main() {
    // Seed the random number generator to get different results each time
    srand(time(NULL));

    FILE *file = fopen("test_data.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing test data.\n");
        return EXIT_FAILURE;
    }

    // Define maximum vertices and edges according to the problem statement
    int maxVertices = 1000;
    int maxEdges = 100000;

    int Nv = maxVertices; // Vertex count
    int Ne = rand() % (maxEdges - Nv + 1) + Nv; // Ensure at least Nv-1 edges

    fprintf(file, "%d %d\n", Nv, Ne);

    // Generating edges with random weights
    for (int i = 0; i < Ne; ++i) {
        int u = rand() % Nv + 1;
        int v = rand() % Nv + 1;
        while (u == v) { // Ensure u is not equal to v
            v = rand() % Nv + 1;
        }
        int weight = rand() % 100 + 1; // Weights between 1 and 100
        fprintf(file, "%d %d %d\n", u, v, weight);
    }

    // Generating queries (sequences)
    int queries = rand()%100+1;
    fprintf(file, "%d\n", queries);
    // Generate and print random permutations
    for (int i = 0; i < queries; ++i) {
        printRandomPermutation(Nv, file);
    }

    fclose(file);

    printf("Test data generated successfully!\n");
    return EXIT_SUCCESS;
}