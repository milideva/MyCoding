#include <stdio.h>
#include <limits.h>

/*
  Problem: Find Largest Sum Pair in an Unsorted Array

  Problem Description:
  Given an unsorted array of integers, find the maximum sum of a 
  pair of elements.

  Example:
  Input: [12, 34, 10, 6, 40]
  Output: 74 (40 + 34)

  Algorithm: Single Pass (Top Two Elements)
  1. Maintain two variables, `first` and `second`, representing the 
     two largest elements seen so far.
  2. Initially, `first = max(arr[0], arr[1])` and `second = min(arr[0], arr[1])`.
  3. Iterate from index 2 to n-1:
     - If `arr[i] > first`:
       - `second = first`
       - `first = arr[i]`
     - Else if `arr[i] > second`:
       - `second = arr[i]`
  4. The maximum sum is `first + second`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the array exactly once.
  - Space Complexity: O(1) auxiliary space.

  Brute Force comparison:
  - Check every pair (i, j) and find the max sum: O(N^2).
  - Sort the array and sum the last two elements: O(N log N).
  - The single-pass approach is the most efficient.
*/

int findLargestSumPair(int arr[], int n) {
    if (n < 2) return 0;
    
    int first, second;
    if (arr[0] > arr[1]) {
        first = arr[0];
        second = arr[1];
    } else {
        first = arr[1];
        second = arr[0];
    }

    for (int i = 2; i < n; i++) {
        if (arr[i] > first) {
            second = first;
            first = arr[i];
        } else if (arr[i] > second) {
            second = arr[i];
        }
    }
    return first + second;
}

void test(const char* label, int arr[], int n, int expected) {
    printf("Testing: %s\n", label);
    int result = findLargestSumPair(arr, n);
    if (result == expected) {
        printf("  [PASS] Max Pair Sum: %d\n", result);
    } else {
        printf("  [FAIL] Result: %d (Expected: %d)\n", result, expected);
    }
}

int main() {
    int arr1[] = {12, 34, 10, 6, 40};
    test("Example 1", arr1, 5, 74);

    int arr2[] = {10, 10, 10};
    test("Duplicates", arr2, 3, 20);

    return 0;
}
