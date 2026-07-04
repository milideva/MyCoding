#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
  LeetCode 259: 3Sum Smaller

  Problem Description:
  Given an array of n integers `nums` and an integer `target`, find 
  the number of index triplets `i, j, k` with `0 <= i < j < k < n` 
  that satisfy the condition `nums[i] + nums[j] + nums[k] < target`.

  Example 1:
  Input: nums = [-2,0,1,3], target = 2
  Output: 2
  Explanation: Because there are two triplets which sums are less than 2:
  [-2,0,1]
  [-2,0,3]

  Algorithm: Sorting + Two Pointers
  1. Sort the input array.
  2. Iterate through the array with index `i`.
  3. For each `i`, find the number of pairs `(l, r)` such that 
     `nums[l] + nums[r] < target - nums[i]`, where `l = i + 1`.
  4. Optimization: If `nums[l] + nums[r] < target - nums[i]`, then 
     all pairs `(l, l+1), (l, l+2), ..., (l, r)` also satisfy the 
     condition because the array is sorted.
  5. Thus, add `r - l` to the count and increment `l`. 
     Otherwise, decrement `r`.

  Complexity Analysis:
  - Time Complexity: O(N^2)
    Reason: Sorting is O(N log N). The nested loops (one for `i` and 
    the two-pointer scan) take O(N^2).
  - Space Complexity: O(1) auxiliary space (ignoring sorting).

  Brute Force comparison:
  - Check all possible triplets.
  - Time Complexity: O(N^3).
  - The two-pointer "r-l count" trick reduces this to quadratic time.
*/

class Solution {
    int twoSumSmaller(vector<int>& nums, int start, int target) {
        int count = 0;
        int l = start;
        int r = nums.size() - 1;
        while (l < r) {
            if (nums[l] + nums[r] < target) {
                // All elements between l and r will also satisfy the condition
                // when paired with nums[l]
                count += (r - l);
                l++;
            } else {
                r--;
            }
        }
        return count;
    }

public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int n = nums.size();
        if (n < 3) return 0;

        sort(nums.begin(), nums.end());
        int totalCount = 0;

        for (int i = 0; i < n - 2; ++i) {
            totalCount += twoSumSmaller(nums, i + 1, target - nums[i]);
        }
        return totalCount;
    }
};

void test(const string& label, vector<int> nums, int target, int expected) {
    cout << "Testing: " << label << " (Target: " << target << ")" << endl;
    Solution sol;
    int result = sol.threeSumSmaller(nums, target);
    cout << "  Result: " << result << " (Expected: " << expected << ")" << endl;
}

int main() {
    test("Example 1", {-2, 0, 1, 3}, 2, 2);
    test("Empty List", {}, 0, 0);
    test("Standard List", {-4, -3, 0, 3, 10, 20}, 0, 3);
    return 0;
}
