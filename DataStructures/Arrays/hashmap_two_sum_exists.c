#include <stdio.h>
#include <stdbool.h>

/*
  Problem: Two Sum (Existence)

  Problem Description:
  Given an array of integers and a target sum N, determine if there 
  exist two elements in the array that add up to N.

  Algorithm 1: Brute Force
  1. Iterate through every pair of elements (i, j).
  2. If `arr[i] + arr[j] == N`, return true.

  Algorithm 2: Sorting + Two Pointers (Standard Optimization)
  1. Sort the array.
  2. Use two pointers `l` and `r` at the ends.
  3. While `l < r`:
     - If `arr[l] + arr[r] == N`, return true.
     - If `arr[l] + arr[r] < N`, `l++`.
     - Else, `r--`.

  Complexity Analysis (Brute Force):
  - Time Complexity: O(N^2)
  - Space Complexity: O(1)

  Complexity Analysis (Sorted):
  - Time Complexity: O(N log N) for sorting, O(N) for scan.
  - Space Complexity: O(1) beyond sorting overhead.
*/

bool isSumPossible(int arr[], int size, int target) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] + arr[j] == target) return true;
        }
    }
    return false;
}

void test(const char* label, int arr[], int size, int target, bool expected) {
    printf("Testing: %s\n", label);
    bool result = isSumPossible(arr, size, target);
    printf("  [%s] Sum %d %s found.\n", (result == expected ? "PASS" : "FAIL"), 
           target, (result ? "was" : "was NOT"));
}

int main() {
    int arr[] = {4, 3, 34, 5, 14, 1, 13, 7};
    int sz = sizeof(arr) / sizeof(arr[0]);

    test("Target 48 (34+14)", arr, sz, 48, true);
    test("Target 9 (4+5)", arr, sz, 9, true);
    test("Target 100 (Missing)", arr, sz, 100, false);

    return 0;
}
