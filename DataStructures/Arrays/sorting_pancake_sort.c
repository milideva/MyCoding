#include <stdio.h>
#include <stdlib.h>

/*
  LeetCode 969: Pancake Sorting

  Problem Description:
  Given an array of integers `arr`, sort the array by performing a 
  series of pancake flips. In one pancake flip, you reverse the 
  sub-array `arr[0...k-1]`.
  
  Return an array of the k-values of the pancake flips that should 
  be executed to sort the array.

  Algorithm: Greedy (Selection Sort Variant)
  1. Find the largest element in the current unsorted portion of the 
     array.
  2. If the largest element is not at the end:
     - Flip it to the front (if it's not already there).
     - Flip it from the front to its correct sorted position (the end 
       of the current portion).
  3. Reduce the size of the unsorted portion and repeat until the 
     entire array is sorted.

  Complexity Analysis:
  - Time Complexity: O(N^2)
    Reason: We perform N iterations, each finding the max (O(N)) and 
    performing flips (O(N)).
  - Space Complexity: O(N) to store the result (list of k-values).

  Brute Force comparison:
  - N/A. Pancake sorting is a specific constrained sorting problem. 
    The greedy approach is the standard solution.
*/

void flip(int arr[], int k) {
    int i = 0, j = k - 1;
    while (i < j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++; j--;
    }
}

int findMax(int arr[], int n) {
    int maxIdx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[maxIdx]) maxIdx = i;
    }
    return maxIdx;
}

void pancakeSort(int arr[], int n) {
    printf("Sorting Steps:\n");
    for (int currSize = n; currSize > 1; currSize--) {
        int maxIdx = findMax(arr, currSize);
        
        if (maxIdx != currSize - 1) {
            // 1. Flip max to the front
            if (maxIdx != 0) {
                printf("  Flip(k=%d) to bring %d to front\n", maxIdx + 1, arr[maxIdx]);
                flip(arr, maxIdx + 1);
            }
            // 2. Flip max from front to its correct position
            printf("  Flip(k=%d) to move max to index %d\n", currSize, currSize - 1);
            flip(arr, currSize);
        }
    }
}

void test(const char* label, int arr[], int n) {
    printf("Testing: %s\n", label);
    pancakeSort(arr, n);
    printf("  Sorted Array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr1[] = {3, 2, 4, 1};
    test("Example 1", arr1, 4);

    int arr2[] = {1, 2, 3};
    test("Already Sorted", arr2, 3);

    return 0;
}
