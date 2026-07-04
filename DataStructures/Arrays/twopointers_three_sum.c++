#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
  LeetCode 15: 3Sum

  Problem Description:
  Given an integer array nums, return all the triplets `[nums[i], 
  nums[j], nums[k]]` such that `i != j`, `i != k`, and `j != k`, 
  and `nums[i] + nums[j] + nums[k] == 0`.

  The solution set must not contain duplicate triplets.

  Algorithm: Sorting + Two Pointers
  1. Sort the input array.
  2. Iterate through the array with index `i`.
  3. For each `i`, use two pointers `l = i + 1` and `r = n - 1` to 
     find pairs that sum to `-nums[i]`.
  4. Skip duplicate values for `i`, `l`, and `r` to ensure unique 
     triplets.

  Complexity Analysis:
  - Time Complexity: O(N^2)
    Reason: Sorting takes O(N log N). The nested loops (one for `i` and 
    the two-pointer search) take O(N^2).
  - Space Complexity: O(1) or O(log N) auxiliary space.
    Reason: Ignoring the result vector, the space used is for sorting.

  Brute Force comparison:
  - Check all possible triplets using three nested loops.
  - Time Complexity: O(N^3).
  - The two-pointer approach reduces this to quadratic time.
*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        if (n < 3) return result;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 2; ++i) {
            // Skip duplicate values for the first element
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int l = i + 1;
            int r = n - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum == 0) {
                    result.push_back({nums[i], nums[l], nums[r]});
                    // Skip duplicates for l and r
                    while (l < r && nums[l] == nums[l + 1]) l++;
                    while (l < r && nums[r] == nums[r - 1]) r--;
                    l++;
                    r--;
                } else if (sum < 0) {
                    l++;
                } else {
                    r--;
                }
            }
        }
        return result;
    }
};

void test(const string& label, vector<int> nums) {
    cout << "Testing: " << label << endl;
    Solution sol;
    vector<vector<int>> result = sol.threeSum(nums);
    cout << "  Result: [ ";
    for (const auto& triplet : result) {
        cout << "[" << triplet[0] << "," << triplet[1] << "," << triplet[2] << "] ";
    }
    cout << "]" << endl;
}

int main() {
    test("Example 1", {-1, 0, 1, 2, -1, -4});
    test("Empty List", {});
    test("Single Zero", {0});
    test("Multiple Zeros", {0, 0, 0, 0});
    return 0;
}
