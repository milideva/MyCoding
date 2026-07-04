#include <vector>
#include <iostream>
#include <numeric>

using namespace std;

/*
  LeetCode 1013: Partition Array Into Three Parts With Equal Sum

  Problem Description:
  Given an array of integers `arr`, return true if we can partition 
  the array into three non-empty parts with equal sums.

  Formally, we can partition the array if we can find indices 
  `i + 1 < j` such that:
  `Sum(arr[0...i]) == Sum(arr[i+1...j-1]) == Sum(arr[j...n-1])`.

  Example 1:
  Input: arr = [0,2,1,-6,6,-7,9,1,2,0,1]
  Output: true

  Algorithm: Greedy Iteration
  1. Calculate the total `sum` of the array.
  2. If `sum % 3 != 0`, return false.
  3. The `targetSum` for each part is `sum / 3`.
  4. Iterate through the array, accumulating `currSum`.
  5. Whenever `currSum == targetSum`:
     - Increment the `partsCount`.
     - Reset `currSum = 0`.
  6. If we find at least 3 parts, return true.
     - Note: If there are more than 3 parts (possible only if 
       `targetSum == 0`), the remaining parts will also sum to 0, 
       so it's still valid.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the array exactly twice (once for sum, once 
    for partitioning).
  - Space Complexity: O(1) auxiliary space.

  Brute Force comparison:
  - Check all possible split points (i, j).
  - Time: O(N^2).
  - The greedy approach is much faster.
*/

class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& arr) {
        int totalSum = accumulate(arr.begin(), arr.end(), 0);
        if (totalSum % 3 != 0) return false;

        int target = totalSum / 3;
        int partsCount = 0;
        int currSum = 0;

        for (int i = 0; i < arr.size(); ++i) {
            currSum += arr[i];
            if (currSum == target) {
                partsCount++;
                currSum = 0;
            }
        }
        // If we found at least 3 parts, the entire sum being multiple 
        // of 3 guarantees the rest is also valid.
        return partsCount >= 3;
    }
};

void test(const string& label, vector<int> arr, bool expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    bool result = sol.canThreePartsEqualSum(arr);
    cout << "  [" << (result == expected ? "PASS" : "FAIL") << "] Result: " << boolalpha << result << endl;
}

int main() {
    test("Example 1", {0, 2, 1, -6, 6, -7, 9, 1, 2, 0, 1}, true);
    test("Example 2", {0, 2, 1, -6, 6, 7, 9, -1, 2, 0, 1}, false);
    test("Example 3", {3, 3, 6, 5, -2, 2, 5, 1, -9, 4}, true);
    test("Zeros", {0, 0, 0, 0}, true);
    return 0;
}
