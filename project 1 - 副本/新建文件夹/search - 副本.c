#include <stdio.h>  // Include standard input and output library
#include <time.h>   // Include time library for time-related functions

clock_t begin, stop; // Declare variables to record time
double duration;     // To calculate the running time

// Function for iterative binary search
int iterativeBinary(int *a, int start, int end, int N) {
    while (start < end) { // Continue loop until start and end meet
        int mid = (start + end) / 2; // Calculate the middle index
        if (N == a[mid]) {
            return mid; // If N is found at mid, return the index
        } else if (N > a[mid]) {
            start = mid + 1; // Update start for right half
        } else {
            end = mid - 1;   // Update end for left half
        }
    }
    return -1; // Return -1 if element is not found
}

// Function for recursive binary search
int recursiveBinary(int *a, int start, int end, int N) {
    if (start < end) { // Base case: when start exceeds end
        int mid = (start + end) / 2; // Calculate the middle index
        if (N == a[mid]) {
            return mid; // If N is found at mid, return the index
        } else if (N > a[mid]) {
            return recursiveBinary(a, mid + 1, end, N); // Search the right half
        } else {
            return recursiveBinary(a, start, mid - 1, N); // Search the left half
        }
    }
    return -1; // Return -1 if element is not found
}

// Function for iterative sequential search
int iterativeSequential(int *a, int end, int N) {
    for (int i = 0; i <= end; i++) { // Iterate through the array
        if (a[i] == N) {
            return i; // If N is found, return the index
            break;     // Break the loop after finding the element
        }
    }
    return -1; // Return -1 if element is not found
}

// Function for recursive sequential search
int recursiveSequential(int *a, int start, int end, int N) {
    if (start <= end) { // Base case: when start exceeds end
        if (a[start] == N) {
            return start; // If N is found at index start, return the index
        } else {
            return recursiveSequential(a, start + 1, end, N); // Recur for the rest of the array
        }
    }
    return -1; // Return -1 if element is not found
}
int main() {
    int N;
    scanf("%d", &N); // Input the size of the array

    int a[N], m;
    for (int i = 0; i < N; i++) {
        a[i] = i; // Populate the array with values from 0 to N-1
    }

    // Measure the time taken for each search algorithm
    begin = clock(); // Record the starting time
    for (int i = 0; i < 100000; i++) { // Repeat 100000 times for better time measurement
        m = iterativeBinary(a, 0, N - 1, N); // Perform iterative binary search
    }
    stop = clock(); // Record the stopping time
    duration = ((double)(stop - begin)) / CLOCKS_PER_SEC; // Calculate the duration in seconds
    printf("Tick for iterativeBinary: %lf, Time for iterativeBinary: %lf\n", (double)(stop - begin), duration);

    begin = clock(); 
    for (int i = 0; i < 100000; i++) { // Repeat 100000 times for better time measurement
        m = recursiveBinary(a, 0, N - 1, N); // Perform recursive binary search
    }
    stop = clock(); 
    duration = ((double)(stop - begin)) / CLOCKS_PER_SEC; // Calculate the duration in seconds
    printf("Tick for recursiveBinary: %lf, Time for recursiveBinary: %lf\n", (double)(stop - begin), duration);

    begin = clock(); 
    for (int i = 0; i < 100000; i++) { // Repeat 100000 times for better time measurement
        m = iterativeSequential(a, N - 1, N); // Perform iterative sequential search
    }
    stop = clock(); 
    duration = ((double)(stop - begin)) / CLOCKS_PER_SEC; // Calculate the duration in seconds
    printf("Tick for iterativeSequential:%lf,Time for iterativesequential:%lf\n",(double)(stop-begin),duration);\
    
	begin=clock();
    for (int i = 0; i < 100000; i++)// Repeat 100000 times for better time measurement
    {
        m=recursiveSequential(a,0,N-1,N);
    }
    stop=clock();
    duration=((double)(stop-begin))/CLK_TCK;
    printf("Tick for recursiveSequential:%lf,Time for recursivesequential:%lf\n",(double)(stop-begin),duration);
    
	return 0;
}
