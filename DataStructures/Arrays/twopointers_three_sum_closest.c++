#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/*
  LeetCode 16: 3Sum Closest

  Problem Description:
  Given an integer array `nums` of length `n` and an integer `target`, 
  find three integers in `nums` such that the sum is closest to 
  `target`. Return the sum of the three integers.

  You may assume that each input would have exactly one solution.

  Algorithm: Sorting + Two Pointers
  1. Sort the input array.
  2. Iterate through the array with index `i`.
  3. For each `i`, use two pointers `l = i + 1` and `r = n - 1`.
  4. Calculate `currentSum = nums[i] + nums[l] + nums[r]`.
  5. Update the `closestSum` if `abs(target - currentSum)` is smaller 
     than the current minimum difference.
  6. Adjust pointers:
     - If `currentSum < target`, increment `l`.
     - If `currentSum > target`, decrement `r`.
     - If `currentSum == target`, return it immediately.

  Complexity Analysis:
  - Time Complexity: O(N^2)
    Reason: Sorting is O(N log N). The outer loop runs N times, and 
    the inner two-pointer scan takes O(N).
  - Space Complexity: O(1) auxiliary space (ignoring sorting overhead).

  Brute Force comparison:
  - Check all possible triplets.
  - Time Complexity: O(N^3).
  - The two-pointer approach reduces this to quadratic time.
*/

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        long closestSum = 1e9; // Large enough to not overflow on subtraction

        for (int i = 0; i < n - 2; ++i) {
            int l = i + 1;
            int r = n - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum == target) return sum;

                if (abs(1L * target - sum) < abs(1L * target - closestSum)) {
                    closestSum = sum;
                }

                if (sum < target) {
                    l++;
                } else {
                    r--;
                }
            }
        }
        return (int)closestSum;
    }
};

void test(const string& label, vector<int> nums, int target, int expected) {
    cout << "Testing: " << label << " (Target: " << target << ")" << endl;
    Solution sol;
    int result = sol.threeSumClosest(nums, target);
    cout << "  Result: " << result << " (Expected: " << expected << ")" << endl;
}

int main() {
    test("Example 1", {-1, 2, 1, -4}, 1, 2);
    test("Example 2", {0, 0, 0}, 1, 0);
    test("Standard List", {-4, -3, 0, 3, 10, 20}, 0, 0);
    return 0;
}
