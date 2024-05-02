#include<stdio.h>
#include<stdlib.h>

static int iffirst = 1; // Flag to check if it is the first node

typedef struct node* binarytree; // Define a binary tree as a pointer to a struct node

int a[200000]; // Array to store data for the first tree
int b[200000]; // Array to store father nodes for the first tree
int c[200000]; // Array to store data for the second tree
int d[200000]; // Array to store father nodes for the second tree
int e[200000]; // Array to store the inorder traversal of the first tree
int f[200000]; // Array to store the inorder traversal of the second tree

struct node{
    int data;  
    int left;   // Index of the left child node
    int right;  // Index of the right child node
};

// Function to create a binary tree
binarytree create(int n, int *data, int *father){
    binarytree root = (binarytree)malloc(sizeof(struct node)*n); // Allocate memory for the binary tree
    for(int i=0; i<n; i++){
        root[i].data = data[i]; 
        root[i].left = -1;     // Initialize left child index as -1
        root[i].right = -1;    // Initialize right child index as -1
    }
    for(int i=0; i<n; i++){
        if(father[i] == -1) continue; // Skip if the node has no father
        if(root[i].data < root[father[i]].data) root[father[i]].left = i;  // Assign the current node as the left child of its father
        else root[father[i]].right = i; // Assign the current node as the right child of its father
    }
    return root;
}

// Function to perform inorder traversal of a binary tree and store the result in an array
void inorder(binarytree root, int n, int *array){
    static int i = 0; // Static variable to keep track of the index in the array
    if(n == -1) return; // Base case: if the current node is NULL, return
    inorder(root, root[n].left, array); // Recursively traverse the left subtree
    array[i++] = root[n].data; // Store the data of the current node in the array
    inorder(root, root[n].right, array); // Recursively traverse the right subtree
}


void inorder1(binarytree root, int n, int *array){
    static int j = 0;
    if(n == -1) return;
    inorder1(root, root[n].left, array); 
    array[j++] = root[n].data; 
    inorder1(root, root[n].right, array); 
}

// Function to search for pairs of nodes in two binary trees that sum up to a given value
void search(int m, int *T1, int *T2, int n1, int n2){
    int flag = 0; // Flag to check if any pairs are found
    int start = 0; // Start index of the first array
    int end = n2 - 1; // End index of the second array
    while(start != n1 && end != -1){
        if(T1[start] + T2[end] == m){ // If the sum of the current pair is equal to the given value
            if(!flag) printf("true\n"); // Print "true" if it is the first pair found
            flag = 1; // Set the flag to indicate that at least one pair is found
            printf("%d = %d + %d\n", m, T1[start], T2[end]); // Print the pair
            start++;
            end--;
            if(start == n1 || end == -1) break; // If the start index of the first array reaches the end or the end index of the second array reaches the start, break the loop (to avoid infinite loop
            while(T1[start-1]==T1[start])start++; // Move to the next element in the first array
            while(T2[end]==T2[end+1])end--; // Move to the previous element in the second array
        }
        else if(T1[start] + T2[end] > m) end--; // If the sum is greater than the given value, move to the previous element in the second array
        else start++; // If the sum is less than the given value, move to the next element in the first array
    }
    if(!flag) printf("false\n"); // If no pairs are found, print "false"
}

// Function to perform preorder traversal of a binary tree and print the nodes
void preorder(binarytree root, int n){
    if(n == -1) return; // Base case: if the current node is NULL, return
    if(iffirst)
        iffirst = 0;
    else
        printf(" ");
    printf("%d", root[n].data); // Print the data of the current node
    preorder(root, root[n].left); // Recursively traverse the left subtree
    preorder(root, root[n].right); // Recursively traverse the right subtree
}

int main(){
    int m, n, root1 = 0, root2 = 0, sum;
    scanf("%d", &m); // Read the number of nodes in the first tree
    for(int i=0; i<m; i++){
        scanf("%d %d", &a[i], &b[i]); // Read the data and father nodes for each node in the first tree
        if(b[i] == -1) root1 = i; // Find the root of the first tree
    }
    binarytree T1 = create(m, a, b); // Create the first binary tree
    scanf("%d", &n); 
    for(int i=0; i<n; i++){
        scanf("%d %d", &c[i], &d[i]); 
        if(d[i] == -1) root2 = i;
    }
    binarytree T2 = create(n, c, d); // Create the second binary tree
    scanf("%d", &sum); // Read the target sum
    inorder(T1, root1, e); // Perform inorder traversal of the first tree and store the result in array e
    inorder1(T2, root2, f); // Perform inorder traversal of the second tree and store the result in array f
    search(sum, e, f, m, n); // Search for pairs of nodes in the two trees that sum up to the target sum
    preorder(T1, root1); 
    printf("\n");
    iffirst = 1;
    preorder(T2, root2); 
    return 0;
}