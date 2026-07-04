#include <stdio.h>
#include <stdlib.h>

/*
  Problem: Merge Sort (Recursive)

  Problem Description:
  Implement the Merge Sort algorithm to sort an array of integers 
  in ascending order.

  Algorithm: Divide and Conquer
  1. If the array has one or zero elements, it is already sorted.
  2. Divide the array into two halves.
  3. Recursively sort the left half.
  4. Recursively sort the right half.
  5. Merge the two sorted halves into a single sorted array:
     - Compare elements from both halves and pick the smaller one.
     - Copy remaining elements if any.

  Complexity Analysis:
  - Time Complexity: O(N log N)
    Reason: The recurrence relation is T(n) = 2T(n/2) + O(n). 
    The depth of the tree is log N, and at each level, we do O(N) work.
  - Space Complexity: O(N) for the temporary array used during merging.
*/

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void test(const char* label, int arr[], int n) {
    printf("Testing %s:\n", label);
    mergeSort(arr, 0, n - 1);
    printf("  Sorted: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr1[] = {12, 11, 13, 5, 6, 7};
    test("Example 1", arr1, 6);

    int arr2[] = {5, 4, 3, 2, 1};
    test("Reverse Sorted", arr2, 5);

    int arr3[] = {1};
    test("Single Element", arr3, 1);

    return 0;
}
