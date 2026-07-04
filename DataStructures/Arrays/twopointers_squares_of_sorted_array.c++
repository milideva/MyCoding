#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 977: Squares of a Sorted Array

  Problem Description:
  Given an integer array `nums` sorted in non-decreasing order, return 
  an array of the squares of each number sorted in non-decreasing 
  order.

  Example 1:
  Input: nums = [-4,-1,0,3,10]
  Output: [0,1,9,16,100]

  Algorithm: Two Pointers
  1. Initialize two pointers, `l = 0` and `r = n - 1`.
  2. Create a result vector `ans` of the same size.
  3. Since the array is sorted, the largest squares will be at the 
     ends (either the most negative or the most positive).
  4. Fill the `ans` vector from back to front:
     - Compare `abs(nums[l])` and `abs(nums[r])`.
     - Square the larger absolute value and place it at the current 
       back position.
     - Move the corresponding pointer (`l` forward or `r` backward).

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the array once using two pointers.
  - Space Complexity: O(1) auxiliary space (excluding result).

  Brute Force comparison:
  - Square every number and then sort the array.
  - Time: O(N log N).
  - The two-pointer approach is optimal as it utilizes the existing 
    sorting.
*/

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        int l = 0, r = n - 1;

        for (int i = n - 1; i >= 0; --i) {
            if (abs(nums[l]) > abs(nums[r])) {
                ans[i] = nums[l] * nums[l];
                l++;
            } else {
                ans[i] = nums[r] * nums[r];
                r--;
            }
        }
        return ans;
    }
};

void test(const string& label, vector<int> nums) {
    cout << "Testing: " << label << endl;
    Solution sol;
    vector<int> result = sol.sortedSquares(nums);
    cout << "  Result: [ ";
    for (int x : result) cout << x << " ";
    cout << "]" << endl;
}

int main() {
    test("Example 1", {-4, -1, 0, 3, 10});
    test("Example 2", {-7, -3, 2, 3, 11});
    test("All Negatives", {-5, -4, -3});
    test("All Positives", {1, 2, 3});
    return 0;
}
