#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 1: Two Sum

  Problem Description:
  Given an array of integers `nums` and an integer `target`, return 
  indices of the two numbers such that they add up to `target`.

  You may assume that each input would have exactly one solution, 
  and you may not use the same element twice.

  Algorithm 1: Hash Map (Single Pass)
  1. Use a hash map to store `value -> index` of elements seen so far.
  2. For each element `nums[i]`:
     - Calculate `complement = target - nums[i]`.
     - If `complement` exists in the map, return `{map[complement], i}`.
     - Else, add `nums[i]` to the map.

  Algorithm 2: Two Pointers (If sorted)
  1. Sort the array while keeping track of original indices.
  2. Use two pointers `l = 0` and `r = n - 1`.
  3. While `l < r`:
     - `sum = nums[l] + nums[r]`.
     - If `sum == target`, return indices.
     - If `sum < target`, `l++`.
     - Else, `r--`.

  Complexity Analysis:
  - Time Complexity: O(N) for Hash Map, O(N log N) for Two Pointers.
  - Space Complexity: O(N) for Hash Map, O(N) for indices in Two Pointers.

  Brute Force comparison:
  - Check every pair (i, j).
  - Time Complexity: O(N^2).
  - The hash map approach is optimal for unsorted arrays.
*/

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;
        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];
            if (seen.count(complement)) {
                return {seen[complement], i};
            }
            seen[nums[i]] = i;
        }
        return {};
    }
};

void test(const string& label, vector<int> nums, int target) {
    cout << "Testing: " << label << endl;
    Solution sol;
    vector<int> result = sol.twoSum(nums, target);
    if (!result.empty()) {
        cout << "  [PASS] Indices: [" << result[0] << ", " << result[1] << "] Values: " 
             << nums[result[0]] << " + " << nums[result[1]] << " = " << target << endl;
    } else {
        cout << "  [FAIL] No solution found." << endl;
    }
}

int main() {
    test("Example 1", {2, 7, 11, 15}, 9);
    test("Example 2", {3, 2, 4}, 6);
    test("Same Value", {3, 3}, 6);
    return 0;
}
