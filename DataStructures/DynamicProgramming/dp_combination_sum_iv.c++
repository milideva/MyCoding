#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 377: Combination Sum IV

  Problem Description:
  Given an array of distinct integers `nums` and a target integer 
  `target`, return the number of possible combinations that add up 
  to `target`. Different sequences are counted as different 
  combinations (e.g., [1, 2] and [2, 1] are different).

  Algorithm: Dynamic Programming (Bottom-Up)
  1. Let `dp[i]` be the number of ways to sum up to `i`.
  2. Base Case: `dp[0] = 1`.
  3. For `i` from 1 to `target`:
     - For each `num` in `nums`:
       - If `i >= num`:
         - `dp[i] += dp[i - num]`.
  4. Use `unsigned int` to prevent overflow during intermediate steps 
     (as per LeetCode constraints).

  Complexity Analysis:
  - Time Complexity: O(Target * N) where N is the number of elements.
  - Space Complexity: O(Target).
*/

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<unsigned int> dp(target + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= target; i++) {
            for (int num : nums) {
                if (i >= num) {
                    dp[i] += dp[i - num];
                }
            }
        }
        return (int)dp[target];
    }
};

void test(vector<int> nums, int target, int expected) {
    Solution sol;
    int result = sol.combinationSum4(nums, target);
    cout << "Target: " << target << " -> Ways: " << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    test({1, 2, 3}, 4, 7);
    test({9}, 3, 0);
    return 0;
}
