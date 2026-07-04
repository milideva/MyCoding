#include <stdio.h>

/*
  LeetCode 53: Maximum Subarray (Kadane's Algorithm)

  Problem Description:
  Given an integer array `nums`, find the contiguous subarray (containing 
  at least one number) which has the largest sum and return its sum.

  Example 1:
  Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
  Output: 6
  Explanation: [4,-1,2,1] has the largest sum = 6.

  Algorithm: Kadane's Algorithm (Greedy/DP)
  1. Maintain two variables: `max_so_far` and `curr_max`.
  2. For each element `x` in the array:
     - `curr_max = max(x, curr_max + x)`. This means we either start 
        a new subarray at `x` or extend the previous one.
     - `max_so_far = max(max_so_far, curr_max)`.
  3. This algorithm effectively discards negative prefix sums that 
     would only decrease the sum of future subarrays.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the array exactly once.
  - Space Complexity: O(1) auxiliary space.

  Brute Force comparison:
  - Check all possible subarrays (i, j).
  - Time Complexity: O(N^2) or O(N^3).
  - Kadane's algorithm reduces this to linear time using dynamic 
    programming intuition.
*/

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxSubArray(int nums[], int n) {
    if (n == 0) return 0;
    
    int max_so_far = nums[0];
    int curr_max = nums[0];

    for (int i = 1; i < n; i++) {
        curr_max = max(nums[i], curr_max + nums[i]);
        max_so_far = max(max_so_far, curr_max);
    }
    return max_so_far;
}

void test(const char* label, int nums[], int n, int expected) {
    printf("Testing: %s\n", label);
    int result = maxSubArray(nums, n);
    if (result == expected) {
        printf("  [PASS] Max Sum: %d\n", result);
    } else {
        printf("  [FAIL] Result: %d (Expected: %d)\n", result, expected);
    }
}

int main() {
    int arr1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    test("Example 1", arr1, 9, 6);

    int arr2[] = {5, 4, -1, 7, 8};
    test("All Positive with one negative", arr2, 5, 23);

    int arr3[] = {-1, -2, -3};
    test("All Negative", arr3, 3, -1);

    return 0;
}
