#include <vector>
#include <iostream>
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
  1. Use two pointers, `l` (left) and `r` (right), representing the 
     window boundaries.
  2. Iterate through the array with the `r` pointer, adding 
     `nums[r]` to the `currentSum`.
  3. While `currentSum >= target`:
     - Update `minLen = min(minLen, r - l + 1)`.
     - Subtract `nums[l]` from `currentSum` and increment `l` to 
       shrink the window.
  4. Repeat until the end of the array.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Each element is visited at most twice (once by `r` and 
    once by `l`).
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
    cout << "Testing: " << label << " (Target: " << target << ")" << endl;
    Solution sol;
    int result = sol.minSubArrayLen(target, nums);
    cout << "  Result: " << result << " (Expected: " << expected << ")" << endl;
}

int main() {
    test("Example 1", {2, 3, 1, 2, 4, 3}, 7, 2);
    test("Example 2", {1, 4, 4}, 4, 1);
    test("Example 3", {1, 1, 1, 1, 1, 1, 1, 1}, 11, 0);
    test("Empty List", {}, 5, 0);
    return 0;
}
