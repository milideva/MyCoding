#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
  Problem: K-th Smallest Element in an Unsorted Array

  Problem Description:
  Given an array and a number k, find the kth smallest element in 
  the array. All array elements are distinct.

  Algorithm 1: Min-Heap
  1. Build a Min-Heap of all N elements.
  2. Call `extractMin()` k times.
  3. The k-th extracted element is the result.
  4. Time: O(N + k log N).

  Algorithm 2: Max-Heap (Optimized for space/k)
  1. Build a Max-Heap of the first k elements.
  2. For the remaining N-k elements:
     - If an element is smaller than the root of the Max-Heap, 
       replace the root and heapify.
  3. The root of the Max-Heap is the k-th smallest element.
  4. Time: O(k + (N-k) log k) = O(N log k).

  Algorithm 3: QuickSelect (Best Average Time)
  1. Use the partition logic from QuickSort.
  2. If the pivot index is `k-1`, we found the element.
  3. Otherwise, recurse into only one half.
  4. Time: O(N) average, O(N^2) worst case.

  Complexity Analysis (Current Implementation: Min-Heap):
  - Time Complexity: O(N + k log N)
  - Space Complexity: O(N) to store the heap.
*/

typedef struct {
    int* data;
    int size;
} MinHeap;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* heap, int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int smallest = i;
    if (l < heap->size && heap->data[l] < heap->data[i]) smallest = l;
    if (r < heap->size && heap->data[r] < heap->data[smallest]) smallest = r;
    if (smallest != i) {
        swap(&heap->data[i], &heap->data[smallest]);
        minHeapify(heap, smallest);
    }
}

int extractMin(MinHeap* heap) {
    if (heap->size <= 0) return INT_MAX;
    int root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return root;
}

int kthSmallest(int arr[], int n, int k) {
    MinHeap heap = {arr, n};
    // Build heap
    for (int i = (n - 2) / 2; i >= 0; i--) {
        minHeapify(&heap, i);
    }
    // Extract k-1 times
    for (int i = 0; i < k - 1; i++) {
        extractMin(&heap);
    }
    return heap.data[0];
}

void test(const char* label, int arr[], int n, int k, int expected) {
    printf("Testing: %s (k=%d)\n", label, k);
    // Copy array as kthSmallest modifies it (heap in-place)
    int* copy = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) copy[i] = arr[i];

    int result = kthSmallest(copy, n, k);
    if (result == expected) {
        printf("  [PASS] %d-th smallest: %d\n", k, result);
    } else {
        printf("  [FAIL] Result: %d (Expected: %d)\n", result, expected);
    }
    free(copy);
}

int main() {
    int arr1[] = {12, 3, 5, 7, 19};
    test("Standard Example", arr1, 5, 2, 5);
    test("Standard Example", arr1, 5, 3, 7);

    int arr2[] = {7, 10, 4, 3, 20, 15};
    test("Large Unsorted", arr2, 6, 3, 7);
    test("Large Unsorted", arr2, 6, 4, 10);

    return 0;
}
