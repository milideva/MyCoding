#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 1099: Two Sum Less Than K

  Problem Description:
  Given an array `nums` of integers and integer `k`, return the 
  maximum sum such that `nums[i] + nums[j] = sum` where `i < j` 
  and `sum < k`. If no such `i, j` exist, return -1.

  Algorithm: Sorting + Two Pointers
  1. Sort the input array `nums`.
  2. Initialize two pointers, `l = 0` and `r = n - 1`.
  3. While `l < r`:
     - `sum = nums[l] + nums[r]`.
     - If `sum < k`:
       - Update `maxSum = max(maxSum, sum)`.
       - Increment `l` to try a larger sum.
     - Else (`sum >= k`):
       - Decrement `r` to try a smaller sum.
  4. Return `maxSum`.

  Complexity Analysis:
  - Time Complexity: O(N log N)
    Reason: Sorting takes O(N log N). The two-pointer scan is O(N).
  - Space Complexity: O(1) or O(log N) for sorting overhead.

  Brute Force comparison:
  - Check every pair (i, j).
  - Time Complexity: O(N^2).
  - The sorting + two-pointer approach is more efficient for large N.
*/

class Solution {
public:
    int twoSumLessThanK(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int l = 0, r = nums.size() - 1;
        int maxSum = -1;

        while (l < r) {
            int sum = nums[l] + nums[r];
            if (sum < k) {
                maxSum = max(maxSum, sum);
                l++;
            } else {
                r--;
            }
        }
        return maxSum;
    }
};

void test(const string& label, vector<int> nums, int k, int expected) {
    cout << "Testing: " << label << " (k: " << k << ")" << endl;
    Solution sol;
    int result = sol.twoSumLessThanK(nums, k);
    if (result == expected) {
        cout << "  [PASS] Result: " << result << endl;
    } else {
        cout << "  [FAIL] Result: " << result << " (Expected: " << expected << ")" << endl;
    }
}

int main() {
    test("Example 1", {34, 23, 1, 24, 75, 33, 54, 8}, 60, 58);
    test("Example 2", {10, 20, 30}, 15, -1);
    test("Sorted Array", {1, 2, 3, 4, 5}, 10, 9);
    return 0;
}
