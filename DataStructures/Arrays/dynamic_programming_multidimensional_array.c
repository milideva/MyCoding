#include <stdlib.h>
#include <stdio.h>

/*
  Problem: Dynamic 2D Array Allocation in C

  Problem Description:
  Implement a function to allocate a 2D dynamic array such that its 
  elements can be accessed using the standard `arr[i][j]` syntax.

  Algorithm: Array of Pointers
  1. Allocate an array of `row` pointers (type `int**`).
  2. For each pointer, allocate an array of `col` integers (type `int*`).
  3. This creates a structure where `arr` points to an array of pointers, 
     each pointing to a row of data.

  Complexity Analysis:
  - Allocation: O(R) where R is the number of rows.
  - Access: O(1) for `arr[i][j]`.
  - Deallocation: O(R).
  - Space Complexity: O(R * C) for data + O(R) for pointers.

  Comparison:
  - Single Allocation: `int* arr = malloc(R * C * sizeof(int))`.
    - Access: `arr[i * C + j]`.
    - Better cache locality and fewer malloc calls, but less intuitive 
      syntax.
  - Array of Pointers: Allows `arr[i][j]` but has more overhead and 
    potential memory fragmentation.
*/

int** allocate2D(int rows, int cols) {
    int** arr = (int**)malloc(rows * sizeof(int*));
    if (!arr) return NULL;
    for (int i = 0; i < rows; i++) {
        arr[i] = (int*)malloc(cols * sizeof(int));
    }
    return arr;
}

void free2D(int** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
}

void useArray(int rows, int cols) {
    printf("Testing 2D Allocation (%d x %d)\n", rows, cols);
    int** arr = allocate2D(rows, cols);
    if (!arr) return;

    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = count++;
        }
    }

    printf("  arr[0][0] = %d\n", arr[0][0]);
    printf("  arr[%d][%d] = %d\n", rows-1, cols-1, arr[rows-1][cols-1]);

    free2D(arr, rows);
}

int main() {
    useArray(5, 10);
    return 0;
}
