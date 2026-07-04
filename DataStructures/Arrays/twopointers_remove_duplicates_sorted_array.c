#include <stdio.h>

/*
  LeetCode 26: Remove Duplicates from Sorted Array

  Problem Description:
  Given an integer array `nums` sorted in non-decreasing order, 
  remove the duplicates in-place such that each unique element 
  appears only once. The relative order of the elements should be 
  kept the same.

  Return the number of unique elements `k`. The first `k` elements 
  of `nums` should contain the unique elements.

  Example 1:
  Input: nums = [1,1,2]
  Output: 2, nums = [1,2,_]

  Algorithm: Two Pointers (Read and Write)
  1. Maintain a `write` pointer at index 0 (the first unique element).
  2. Iterate through the array with a `read` pointer starting at 1.
  3. If `nums[read] != nums[write]`:
     - Increment `write`.
     - Copy `nums[read]` to `nums[write]`.
  4. Return `write + 1`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the array exactly once.
  - Space Complexity: O(1) auxiliary space.

  Brute Force comparison:
  - Use a hash set or a new array to store unique elements.
  - Space: O(N).
  - The two-pointer approach is the most memory-efficient.
*/

int removeDuplicates(int nums[], int n) {
    if (n == 0) return 0;

    int write = 0;
    for (int read = 1; read < n; read++) {
        if (nums[read] != nums[write]) {
            write++;
            nums[write] = nums[read];
        }
    }
    return write + 1;
}

void test(const char* label, int nums[], int n, int expected) {
    printf("Testing: %s\n", label);
    int result = removeDuplicates(nums, n);
    if (result == expected) {
        printf("  [PASS] Unique Count: %d\n", result);
    } else {
        printf("  [FAIL] Result: %d (Expected: %d)\n", result, expected);
    }
}

int main() {
    int arr1[] = {1, 1, 2};
    test("Example 1", arr1, 3, 2);

    int arr2[] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    test("Example 2", arr2, 10, 5);

    int arr3[] = {1, 2, 3};
    test("No Duplicates", arr3, 3, 3);

    return 0;
}
