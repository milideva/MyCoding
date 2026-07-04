#include <stdio.h>
#include <limits.h>

/*
  LeetCode 137: Single Number II

  Problem Description:
  Given an integer array `nums` where every element appears three 
  times except for one, which appears exactly once. Find the single 
  element and return it.
  You must implement a solution with a linear runtime complexity and 
  use only constant extra space.

  Algorithm: Bit Counting
  1. For each bit position `i` from 0 to 31:
     - Count how many numbers in the array have the i-th bit set.
     - Let the count be `count`.
     - If `count % 3 != 0`, then the single number must have its 
       i-th bit set.
  2. Combine these bits to form the result.

  Complexity Analysis:
  - Time Complexity: O(N * 32) = O(N)
    Reason: We iterate through the array 32 times (once for each bit).
  - Space Complexity: O(1).

  Alternative Approaches:
  - Bitwise Simulation (Optimal): 
    - Use `ones` and `twos` variables to track bit counts modulo 3.
    - Time: O(N), Space: O(1). Single pass.
*/

int findSingleNumber(int nums[], int n) {
    int result = 0;
    for (int i = 0; i < 32; i++) {
        int sum = 0;
        int mask = (1 << i);
        for (int j = 0; j < n; j++) {
            if (nums[j] & mask) {
                sum++;
            }
        }
        if (sum % 3 != 0) {
            result |= mask;
        }
    }
    return result;
}

void test(const char* label, int nums[], int n, int expected) {
    printf("Testing: %s\n", label);
    int result = findSingleNumber(nums, n);
    if (result == expected) {
        printf("  [PASS] Single Number: %d\n", result);
    } else {
        printf("  [FAIL] Result: %d (Expected: %d)\n", result, expected);
    }
}

int main() {
    int arr1[] = {2, 2, 3, 2};
    test("Example 1", arr1, 4, 3);

    int arr2[] = {0, 1, 0, 1, 0, 1, 99};
    test("Example 2", arr2, 7, 99);

    int arr3[] = {-2, -2, 1, 1, -2, 1, -10};
    test("With Negatives", arr3, 7, -10);

    return 0;
}
