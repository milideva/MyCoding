#include <stdio.h>

/*
  LeetCode 153: Find Minimum in Rotated Sorted Array

  Problem Description:
  Suppose an array of length `n` sorted in ascending order is rotated 
  between 1 and `n` times. Given the sorted rotated array `nums` of 
  unique elements, return the minimum element of this array.

  You must write an algorithm that runs in O(log N) time.

  Example 1:
  Input: nums = [3,4,5,1,2]
  Output: 1

  Algorithm: Binary Search
  1. Initialize `l = 0` and `r = n - 1`.
  2. While `l < r`:
     - Calculate `mid = l + (r - l) / 2`.
     - Compare `nums[mid]` with `nums[r]`:
       - If `nums[mid] > nums[r]`: The minimum must be in the right 
         half (excluding `mid` itself). Set `l = mid + 1`.
       - Else (`nums[mid] <= nums[r]`): The minimum could be `mid` 
         or in the left half. Set `r = mid`.
  3. When the loop ends, `l == r` and points to the minimum element.

  Complexity Analysis:
  - Time Complexity: O(log N)
    Reason: Standard binary search divides the search space in half 
    each step.
  - Space Complexity: O(1) auxiliary space.

  Brute Force comparison:
  - Linear scan to find the smallest element.
  - Time: O(N).
  - Binary search is optimal for sorted/partially sorted data.
*/

int findMin(int nums[], int n) {
    int l = 0, r = n - 1;
    
    // If the array is not rotated at all
    if (nums[l] <= nums[r]) return nums[l];

    while (l < r) {
        int mid = l + (r - l) / 2;
        
        if (nums[mid] > nums[r]) {
            // Minimum must be in the right half
            l = mid + 1;
        } else {
            // Minimum is mid or to the left
            r = mid;
        }
    }
    return nums[l];
}

void test(const char* label, int nums[], int n, int expected) {
    printf("Testing: %s\n", label);
    int result = findMin(nums, n);
    if (result == expected) {
        printf("  [PASS] Min: %d\n", result);
    } else {
        printf("  [FAIL] Result: %d (Expected: %d)\n", result, expected);
    }
}

int main() {
    int arr1[] = {3, 4, 5, 1, 2};
    test("Example 1", arr1, 5, 1);

    int arr2[] = {4, 5, 6, 7, 0, 1, 2};
    test("Example 2", arr2, 7, 0);

    int arr3[] = {11, 13, 15, 17};
    test("No rotation", arr3, 4, 11);

    int arr4[] = {2, 1};
    test("Two elements", arr4, 2, 1);

    int arr5[] = {1};
    test("Single element", arr5, 1, 1);

    return 0;
}
