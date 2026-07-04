#include <stdio.h>
#include <stdlib.h>

/*
  Problem: Count Inversions in an Array

  Problem Description:
  Inversion Count for an array indicates how far (or close) the array 
  is from being sorted. If the array is already sorted, the inversion 
  count is 0. If the array is sorted in reverse order, the inversion 
  count is maximum. 
  Two elements `a[i]` and `a[j]` form an inversion if `a[i] > a[j]` 
  and `i < j`.

  Example:
  Input: [2, 4, 1, 3, 5]
  Output: 3
  Inversions: (2,1), (4,1), (4,3).

  Algorithm: Divide and Conquer (Merge Sort Based)
  1. Divide the array into two halves.
  2. Recursively count inversions in the left half.
  3. Recursively count inversions in the right half.
  4. Count "split" inversions during the merge step:
     - When merging two sorted halves `L` and `R`, if `L[i] > R[j]`, 
       then `R[j]` forms an inversion with ALL remaining elements 
       in `L` (because `L` is sorted).
     - Add `size(L) - i` to the total count.

  Complexity Analysis:
  - Time Complexity: O(N log N)
    Reason: Same as Merge Sort.
  - Space Complexity: O(N) for the temporary merge array.

  Brute Force comparison:
  - Use nested loops to check every pair (i, j).
  - Time Complexity: O(N^2).
  - The divide and conquer approach is significantly faster for large N.
*/

long long mergeAndCount(int arr[], int temp[], int left, int mid, int right) {
    int i = left;    // Index for left subarray
    int j = mid + 1; // Index for right subarray
    int k = left;    // Index for merged subarray
    long long count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            // All elements from arr[i] to arr[mid] are greater than arr[j]
            count += (mid - i + 1);
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = left; i <= right; i++) arr[i] = temp[i];

    return count;
}

long long mergeSortAndCount(int arr[], int temp[], int left, int right) {
    long long count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        count += mergeSortAndCount(arr, temp, left, mid);
        count += mergeSortAndCount(arr, temp, mid + 1, right);
        count += mergeAndCount(arr, temp, left, mid, right);
    }
    return count;
}

void test(const char* label, int arr[], int n, long long expected) {
    printf("Testing: %s\n", label);
    int* temp = (int*)malloc(n * sizeof(int));
    long long result = mergeSortAndCount(arr, temp, 0, n - 1);
    if (result == expected) {
        printf("  [PASS] Inversions: %lld\n", result);
    } else {
        printf("  [FAIL] Result: %lld (Expected: %lld)\n", result, expected);
    }
    free(temp);
}

int main() {
    int arr1[] = {2, 4, 1, 3, 5};
    test("Example 1", arr1, 5, 3);

    int arr2[] = {1, 20, 6, 4, 5};
    test("Example 2", arr2, 5, 5);

    int arr3[] = {5, 4, 3, 2, 1};
    test("Reverse Sorted (n=5)", arr3, 5, 10);

    return 0;
}
