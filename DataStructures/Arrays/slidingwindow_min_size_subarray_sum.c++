// Compilation: g++ -std=c++26 -Wall DataStructures/Arrays/slidingwindow_min_size_subarray_sum.c++ -o /tmp/slidingwindow_min_size_subarray_sum_test && /tmp/slidingwindow_min_size_subarray_sum_test

#include <vector>
#include <print>
#include <algorithm>

using namespace std;

/*
  LeetCode 209: Minimum Size Subarray Sum

  Problem Description:
  Given an array of positive integers `nums` and a positive integer 
  `target`, return the minimal length of a subarray whose sum is 
  greater than or equal to `target`. If there is no such subarray, 
  return 0 instead.

  Example 1:
  Input: target = 7, nums = [2,3,1,2,4,3]
  Output: 2
  Explanation: The subarray [4,3] has the minimal length.

  Algorithm: Sliding Window
  1. Initialization: Start with two pointers, `l` (left) and `r` (right),
     both initialized to index `0` at the start of the array. They represent 
     the sliding window boundaries.
  2. Window Expansion (r): Iterate through the array by moving `r` from `0` to `N-1`.
     Add `nums[r]` to the running `currentSum` to expand the window's right boundary.
  3. Window Shrinking (l): While `currentSum >= target` (constraint is satisfied):
     - Record/Update the minimum length found so far: `minLen = min(minLen, r - l + 1)`.
     - Shrink the window from the left by subtracting `nums[l]` from `currentSum`
       and incrementing `l` (moves the left boundary rightward).
  4. Repeat until `r` reaches the end of the array.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Each element is visited at most twice (once when expanded by `r` and 
    once when shrunk by `l`).
  - Space Complexity: O(1) auxiliary space.

  Alternative Approaches:
  - Binary Search:
    - Logic: Use a prefix sum array. For each index `i`, binary 
      search for the smallest `j` such that `sum[j] - sum[i] >= target`.
    - Time Complexity: O(N log N).
    - Comparison: The sliding window is more efficient for this problem 
      as all numbers are positive.

  Brute Force comparison:
  - Check all possible subarrays.
  - Time Complexity: O(N^2).
  - The sliding window reduces this to linear time.
*/

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int minLen = n + 1;
        long currentSum = 0;
        int l = 0;

        for (int r = 0; r < n; ++r) {
            currentSum += nums[r];
            
            while (currentSum >= target) {
                minLen = min(minLen, r - l + 1);
                currentSum -= nums[l++];
            }
        }

        return (minLen == n + 1) ? 0 : minLen;
    }
};

void test(const string& label, vector<int> nums, int target, int expected) {
    println("Testing: {} (Target: {})", label, target);
    Solution sol;
    int result = sol.minSubArrayLen(target, nums);
    println("  Result: {} (Expected: {})", result, expected);
}

int main() {
    test("Example 1", {2, 3, 1, 2, 4, 3}, 7, 2);
    test("Example 2", {1, 4, 4}, 4, 1);
    test("Example 3", {1, 1, 1, 1, 1, 1, 1, 1}, 11, 0);
    test("Empty List", {}, 5, 0);
    return 0;
}
