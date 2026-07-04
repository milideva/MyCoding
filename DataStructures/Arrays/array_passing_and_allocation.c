#include <stdio.h>
#include <stdlib.h>

/*
  Problem: Passing and Allocating 2D Arrays in C

  Problem Description:
  Demonstrate various ways to handle 2D arrays in C:
  1. Passing 2D arrays with fixed dimensions.
  2. Using Variable Length Arrays (VLA) from C99.
  3. Dynamic allocation of 2D arrays (array of pointers).
  4. Understanding pointer arithmetic differences.

  Complexity Analysis:
  - Allocation: O(ROWS) calls to malloc.
  - Access: O(1) for indexing.
  - Space Complexity: O(ROWS * COLS) for data + O(ROWS) for pointers.

  Comparison:
  - Fixed dimensions: Simplest, but size must be known at compile time.
  - Pointers-to-pointers: Allows non-rectangular (jagged) arrays and 
    dynamic sizing, but requires manual multi-step freeing.
*/

#define FIXED_ROWS 4
#define FIXED_COLS 5

// 1. Fixed dimensions (only first dimension can be omitted)
void processFixedArray(int arr[][FIXED_COLS], int rows) {
    printf("Processing Fixed Array (%d x %d)\n", rows, FIXED_COLS);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < FIXED_COLS; j++) {
            arr[i][j] = i + j;
        }
    }
}

// 2. Variable Length Array (C99 feature)
void processVLA(int rows, int cols, int arr[rows][cols]) {
    printf("Processing VLA (%d x %d)\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = i * j;
        }
    }
}

// 3. Dynamic Allocation (Array of Pointers)
int** allocate2D(int rows, int cols) {
    int** arr = (int**)calloc(rows, sizeof(int*));
    if (!arr) return NULL;
    for (int i = 0; i < rows; i++) {
        arr[i] = (int*)calloc(cols, sizeof(int));
    }
    return arr;
}

void free2D(int** arr, int rows) {
    for (int i = 0; i < rows; i++) free(arr[i]);
    free(arr);
}

int main() {
    // Test Fixed
    int fixedArr[FIXED_ROWS][FIXED_COLS];
    processFixedArray(fixedArr, FIXED_ROWS);

    // Test VLA
    int r = 3, c = 3;
    int vlaArr[r][c];
    processVLA(r, c, vlaArr);

    // Test Dynamic
    int** dynamicArr = allocate2D(5, 5);
    if (dynamicArr) {
        dynamicArr[0][0] = 42;
        printf("Dynamic Array [0][0]: %d\n", dynamicArr[0][0]);
        free2D(dynamicArr, 5);
    }

    return 0;
}
