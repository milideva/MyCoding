#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>

/*
  Problem: Binary Heap Implementation (Min-Heap)

  Problem Description:
  Implement a Min-Heap data structure from scratch using an array.
  The heap must support:
  - `insert_min`: Add an element while maintaining the heap property.
  - `extract_min`: Remove and return the smallest element.
  - `heapify_min`: Restore the heap property from a given node downwards.

  Algorithm: Array-based Binary Heap
  1. Use a 1-indexed array for easier parent/child calculations:
     - Parent(i) = i / 2
     - LeftChild(i) = 2 * i
     - RightChild(i) = 2 * i + 1
  2. Insert: Add to the end of the array and "bubble up" (percolate up).
  3. Extract Min: Replace the root with the last element and "bubble down" 
     (percolate down / heapify).

  Complexity Analysis:
  - Time Complexity:
    - Insert: O(log N).
    - Extract Min: O(log N).
    - Get Min: O(1).
    - Heapify: O(log N).
  - Space Complexity: O(N) to store the elements in an array.

  Comparison:
  - Binary heaps provide a good balance between insertion and extraction 
    times. A sorted array would be O(1) for Get Min but O(N) for insertion. 
    An unsorted array would be O(1) for insertion but O(N) for Extract Min.
*/

typedef unsigned int uint;
typedef struct heap_tag heap_t;

struct heap_tag {
    uint heap_curr_size;
    uint heap_max_size;
    int heap_arr[0]; // Flexible array member
};

// root is at index 1 not at index 0
uint parent (uint i) {
    return i/2;
}

uint left (uint i) {
    return 2*i;
}

uint right (uint i) {
    return 2*i+1;
}

/* Root is at 1st element of the array, 0th element is unsed. */
int getMin (heap_t  *heap) {
    if (heap->heap_curr_size == 0) return INT_MAX;
    return heap->heap_arr[1]; 
}

heap_t *allocate_heap (uint max_size) {
    heap_t *heap = calloc(1, sizeof(*heap) + (max_size + 1) * sizeof(heap->heap_arr[0]) );
    if (!heap) return NULL;
    heap->heap_max_size = max_size;
    return heap;
}

static void swap (heap_t *heap, int i, int j) {
    int temp  = heap->heap_arr[i];
    heap->heap_arr[i] = heap->heap_arr[j];
    heap->heap_arr[j] = temp;
}

// Insert at the last element and then go up to root swapping if required.
bool insert_min (heap_t *heap, int elem) {
    if (heap->heap_curr_size >= heap->heap_max_size) {
        return false;
    }
    heap->heap_curr_size++;
    /* Insert at the end */
    heap->heap_arr[heap->heap_curr_size] = elem;

    int i = heap->heap_curr_size;
    while (i > 1 && heap->heap_arr[i] < heap->heap_arr[parent(i)]) {
        swap(heap, i, parent(i));
        i = parent(i);
    }
    return true;
}

void heapify_min (heap_t *heap, int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;

    // Compare the smallest with left child and swap index if left is smaller
    if (l <= heap->heap_curr_size && heap->heap_arr[l] < heap->heap_arr[smallest]) {
        smallest = l;
    }
    // Compare right with new smallest now
    if (r <= heap->heap_curr_size && heap->heap_arr[r] < heap->heap_arr[smallest]) {
        smallest = r;
    }
    if (smallest != i) {
        // actual swap is here, recurse and repeat
        swap(heap, i, smallest);
        heapify_min(heap, smallest);
    }
}

int extract_min (heap_t *heap) {
    if (heap->heap_curr_size <= 0) 
      return INT_MAX;
    
    int ret = getMin(heap);

    /* Remove root, move last elem into root and call heapify_min() */
    heap->heap_arr[1] = heap->heap_arr[heap->heap_curr_size];
    heap->heap_curr_size--;
    
    if (heap->heap_curr_size > 1) {
        heapify_min(heap, 1);
    }

    return ret;
}

void print_heap (heap_t *heap) {
    uint i, prev_p=0;
    for (i=1; i<= heap->heap_curr_size; i++) {
        if (prev_p != parent(i)) printf("\n");
        printf("[%d][p:%d]:%d:", i, parent(i), heap->heap_arr[i]);
        prev_p = parent(i);
    }
    printf("\n------------------\n\n");
}

void test (heap_t *heap) {
    printf("Testing: Min-Heap Implementation\n");
    insert_min(heap, 500);
    insert_min(heap, 300);
    insert_min(heap, 200);
    insert_min(heap, 1500);
    insert_min(heap, 800);
    insert_min(heap, 178);
    insert_min(heap, 534);
    insert_min(heap, 6353);

    print_heap(heap);

    int elem = extract_min(heap);
    printf("Removed min: %d (Expected: 178)\n", elem);
    
    print_heap(heap);
}

int main (void) {
    heap_t *heap = allocate_heap(64);
    if (!heap) return 1;
    test(heap);
    free(heap);
    return 0;
}
