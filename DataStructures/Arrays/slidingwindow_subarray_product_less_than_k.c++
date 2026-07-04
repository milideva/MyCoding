#include <vector>
#include <iostream>

using namespace std;

/*
  LeetCode 713: Subarray Product Less Than K

  Problem Description:
  Given an array of positive integers `nums` and an integer `k`, 
  return the number of contiguous subarrays where the product of 
  all the elements in the subarray is strictly less than `k`.

  Example 1:
  Input: nums = [10, 5, 2, 6], k = 100
  Output: 8

  Algorithm: Sliding Window
  1. Use two pointers, `l` (left) and `r` (right), for the window.
  2. Maintain `currentProduct` of elements in the window.
  3. Iterate with `r` from 0 to n-1:
     - Update `currentProduct *= nums[r]`.
     - While `currentProduct >= k` (and `l <= r`):
       - `currentProduct /= nums[l]`.
       - Increment `l`.
     - After shrinking, all subarrays ending at `r` and starting 
       between `l` and `r` are valid.
     - The number of such subarrays is `r - l + 1`.
  4. Add this count to the total for each `r`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Each element is multiplied once and divided at most once.
  - Space Complexity: O(1) auxiliary space.

  Brute Force comparison:
  - Check every subarray (i, j).
  - Time Complexity: O(N^2).
  - The sliding window approach reduces this to linear time.
*/

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) return 0;

        int count = 0;
        long long product = 1;
        int l = 0;

        for (int r = 0; r < nums.size(); ++r) {
            product *= nums[r];
            while (product >= k) {
                product /= nums[l++];
            }
            // Number of valid subarrays ending at 'r'
            count += (r - l + 1);
        }
        return count;
    }
};

void test(const string& label, vector<int> nums, int k, int expected) {
    cout << "Testing: " << label << " (k: " << k << ")" << endl;
    Solution sol;
    int result = sol.numSubarrayProductLessThanK(nums, k);
    if (result == expected) {
        cout << "  [PASS] Count: " << result << endl;
    } else {
        cout << "  [FAIL] Result: " << result << " (Expected: " << expected << ")" << endl;
    }
}

int main() {
    test("Example 1", {10, 5, 2, 6}, 100, 8);
    test("K=0", {1, 2, 3}, 0, 0);
    test("All ones", {1, 1, 1}, 2, 6);
    return 0;
}
