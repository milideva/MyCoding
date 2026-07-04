#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
  Problem: Can Sum (Target Sum with Reuse)

  Problem Description:
  Given an array of non-negative integers and a target sum, determine 
  if it's possible to generate the target sum using numbers from the 
  array. You can reuse numbers as many times as needed.

  Algorithm: Dynamic Programming (Memoization)
  1. Recursive function `canSum(target)`.
  2. Base Case: `if (target == 0) return true`, `if (target < 0) return false`.
  3. Recursive Step:
     - For each `num` in the array:
       - If `canSum(target - num)` is true, then `canSum(target)` is true.
  4. Use a map or array to store results of previously computed targets.

  Complexity Analysis:
  - Time Complexity: O(Target * N) where N is the number of elements.
  - Space Complexity: O(Target) for memoization and recursion depth.
*/

class Solution {
    unordered_map<int, bool> memo;

public:
    bool canSum(vector<int>& nums, int target) {
        if (target == 0) return true;
        if (target < 0) return false;
        if (memo.count(target)) return memo[target];

        for (int num : nums) {
            if (canSum(nums, target - num)) {
                return memo[target] = true;
            }
        }
        return memo[target] = false;
    }
};

void test(vector<int> nums, int target, bool expected) {
    Solution sol;
    bool result = sol.canSum(nums, target);
    cout << "Target: " << target << " -> Can Sum: " << boolalpha << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    test({2, 3}, 7, true);
    test({5, 3, 4, 7}, 7, true);
    test({2, 4}, 7, false);
    test({2, 3, 5}, 8, true);
    return 0;
}
