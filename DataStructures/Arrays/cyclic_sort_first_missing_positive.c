#include <stdio.h>

/*
  LeetCode 41: First Missing Positive

  Problem Description:
  Given an unsorted integer array `nums`, return the smallest missing 
  positive integer. You must implement an algorithm that runs in O(N) 
  time and uses O(1) auxiliary space.

  Example 1:
  Input: nums = [3,4,-1,1]
  Output: 2

  Algorithm: Cyclic Sort (In-place Hashing)
  1. Iterate through the array. For each element `nums[i]`:
     - While `nums[i]` is in the range `[1, n]` and `nums[i]` is not 
       at its correct position (`nums[nums[i] - 1] != nums[i]`):
       - Swap `nums[i]` with the element at its target index 
         `nums[i] - 1`.
  2. After placing all possible elements in their correct positions 
     (where `nums[j] == j + 1`):
     - Iterate through the array again.
     - The first index `i` such that `nums[i] != i + 1` identifies 
       the missing positive integer `i + 1`.
  3. If all positions are correct, the missing integer is `n + 1`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Although there is a nested while loop, each element is 
    swapped into its correct position at most once.
  - Space Complexity: O(1) auxiliary space.

  Brute Force comparison:
  - Sort the array (O(N log N)).
  - Use a hash set (O(N) space).
  - Cyclic sort is the only approach meeting the O(N) time and O(1) 
    space constraints simultaneously.
*/

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int firstMissingPositive(int nums[], int n) {
    for (int i = 0; i < n; ++i) {
        // While the current number belongs in the array and is not at its correct spot
        while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
            swap(&nums[i], &nums[nums[i] - 1]);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }
    return n + 1;
}

void test(const char* label, int nums[], int n, int expected) {
    printf("Testing: %s\n", label);
    int result = firstMissingPositive(nums, n);
    if (result == expected) {
        printf("  [PASS] Smallest Missing: %d\n", result);
    } else {
        printf("  [FAIL] Result: %d (Expected: %d)\n", result, expected);
    }
}

int main() {
    int arr1[] = {1, 2, 0};
    test("Example 1", arr1, 3, 3);

    int arr2[] = {3, 4, -1, 1};
    test("Example 2", arr2, 4, 2);

    int arr3[] = {7, 8, 9, 11, 12};
    test("Large Gaps", arr3, 5, 1);

    int arr4[] = {1, 1};
    test("Duplicates", arr4, 2, 2);

    return 0;
}
