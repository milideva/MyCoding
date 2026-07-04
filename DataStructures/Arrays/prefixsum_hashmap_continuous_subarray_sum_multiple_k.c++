#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

/*
  LeetCode 523: Continuous Subarray Sum

  Problem Description:
  Given an integer array `nums` and an integer `k`, return true if 
  `nums` has a "good" subarray or false otherwise.

  A "good" subarray is a subarray where:
  - its length is at least two, and
  - the sum of the elements of the subarray is a multiple of k.

  Note: 0 is always a multiple of k.

  Algorithm: Prefix Sum % k + Hash Map
  1. Maintain a `currSum` that stores the sum of elements % k.
  2. Use a hash map to store the first occurrence of each remainder: 
     `remainder -> index`.
  3. Initialize `map[0] = -1` to handle cases where the prefix sum 
     itself is a multiple of k and its length is `i - (-1) = i + 1`.
  4. For each element `nums[i]`:
     - Update `currSum = (currSum + nums[i]) % k`.
     - If `currSum` is already in the map:
       - Check if the length `i - map[currSum]` is at least 2.
       - If yes, return true.
     - Else, store the current index: `map[currSum] = i`.
  5. If the loop ends, return false.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the array once. Hash map operations are O(1).
  - Space Complexity: O(min(N, k))
    Reason: The hash map stores at most N entries, or k entries 
    (different remainders).

  Brute Force comparison:
  - Check all subarrays of length >= 2 and their sums.
  - Time Complexity: O(N^2).
  - The prefix remainder approach reduces this to linear time.
*/

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        if (nums.size() < 2) return false;

        unordered_map<int, int> remainderMap;
        remainderMap[0] = -1;
        int currRemainder = 0;

        for (int i = 0; i < nums.size(); ++i) {
            currRemainder = (currRemainder + nums[i]);
            if (k != 0) currRemainder %= k;

            if (remainderMap.find(currRemainder) != remainderMap.end()) {
                if (i - remainderMap[currRemainder] > 1) {
                    return true;
                }
            } else {
                remainderMap[currRemainder] = i;
            }
        }
        return false;
    }
};

void test(const string& label, vector<int> nums, int k, bool expected) {
    cout << "Testing: " << label << " (k: " << k << ")" << endl;
    Solution sol;
    bool result = sol.checkSubarraySum(nums, k);
    if (result == expected) {
        cout << "  [PASS]" << endl;
    } else {
        cout << "  [FAIL] Result: " << boolalpha << result << " (Expected: " << expected << ")" << endl;
    }
}

int main() {
    test("Example 1", {23, 2, 4, 6, 7}, 6, true);
    test("Example 2", {23, 2, 6, 4, 7}, 6, true);
    test("Example 3", {23, 2, 6, 4, 7}, 13, false);
    test("Large K", {1, 2, 3}, 10, false);
    test("Zeros", {0, 0}, 0, true);
    return 0;
}
