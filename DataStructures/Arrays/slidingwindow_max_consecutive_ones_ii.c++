#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 1004: Max Consecutive Ones III

  Problem Description:
  Given a binary array `nums` and an integer `k`, return the maximum 
  number of consecutive 1's in the array if you can flip at most `k` 
  0's.

  Example 1:
  Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
  Output: 6

  Algorithm: Sliding Window
  1. Use two pointers, `l` and `r`, to define a window.
  2. Maintain a count of `zeroCount` in the current window.
  3. Iterate with `r` from 0 to n-1:
     - If `nums[r] == 0`, increment `zeroCount`.
     - While `zeroCount > k`:
       - If `nums[l] == 0`, decrement `zeroCount`.
       - Increment `l`.
     - The current window `[l, r]` is valid (contains at most `k` zeros).
     - Update `maxLen = max(maxLen, r - l + 1)`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Each element is visited at most twice.
  - Space Complexity: O(1) auxiliary space.

  Brute Force comparison:
  - Check every subarray (i, j) and count zeros.
  - Time: O(N^2).
  - Sliding window approach is optimal.
*/

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int l = 0, maxLen = 0, zeroCount = 0;
        for (int r = 0; r < nums.size(); ++r) {
            if (nums[r] == 0) zeroCount++;
            
            while (zeroCount > k) {
                if (nums[l] == 0) zeroCount--;
                l++;
            }
            maxLen = max(maxLen, r - l + 1);
        }
        return maxLen;
    }
};

void test(const string& label, vector<int> nums, int k, int expected) {
    cout << "Testing: " << label << " (k: " << k << ")" << endl;
    Solution sol;
    int result = sol.longestOnes(nums, k);
    if (result == expected) {
        cout << "  [PASS] Max Len: " << result << endl;
    } else {
        cout << "  [FAIL] Result: " << result << " (Expected: " << expected << ")" << endl;
    }
}

int main() {
    test("Example 1", {1,1,1,0,0,0,1,1,1,1,0}, 2, 6);
    test("Example 2", {0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1}, 3, 10);
    test("All Zeros", {0, 0, 0}, 1, 1);
    return 0;
}
