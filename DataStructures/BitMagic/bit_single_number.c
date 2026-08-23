#include <stdio.h>

/*
  Solution
  Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.

  You must implement a solution with a linear runtime complexity and use only constant extra space.

  Example 1:
  Input: nums = [2,2,1]
  Output: 1

  Example 2:
  Input: nums = [4,1,2,1,2]
  Output: 4

  Example 3:
  Input: nums = [1]
  Output: 1

  Constraints:
  1 <= nums.length <= 3 * 104
  -3 * 104 <= nums[i] <= 3 * 104
  Each element in the array appears twice except for one element which appears only once.

  Algorithm: Bit Magic (Bitwise XOR)
  - x ^ x = 0 (Any number XOR'ed with itself is 0)
  - x ^ 0 = x (Any number XOR'ed with 0 is the number itself)
  - The XOR operation is associative and commutative: (a ^ b) ^ a = (a ^ a) ^ b = 0 ^ b = b.
  - Therefore, XORing all elements together cancels out pairs, leaving only the single number.

  Complexity Analysis:
  - Time Complexity: O(N) where N is the number of elements in the array.
  - Space Complexity: O(1) auxiliary space as we only use a single variable for XOR.
*/

int singleNumber(int nums[], int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        res ^= nums[i];
    }
    return res;
}

void test(const char* label, int nums[], int n, int expected) {
    printf("Testing: %s\n", label);
    int result = singleNumber(nums, n);
    if (result == expected) {
        printf("  [PASS] Expected: %d, Result: %d\n", expected, result);
    } else {
        printf("  [FAIL] Expected: %d, Result: %d\n", expected, result);
    }
}

int main() {
    int arr1[] = {2, 2, 1};
    test("Example 1", arr1, 3, 1);

    int arr2[] = {4, 1, 2, 1, 2};
    test("Example 2", arr2, 5, 4);

    int arr3[] = {1};
    test("Example 3", arr3, 1, 1);

    int arr4[] = {-1, 2, -1, 3, 2};
    test("Negative elements", arr4, 5, 3);

    return 0;
}
