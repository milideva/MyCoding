#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

/*
  LeetCode 560: Subarray Sum Equals K

  Problem Description:
  Given an array of integers `nums` and an integer `k`, return the 
  total number of continuous subarrays whose sum equals to `k`.

  Example 1:
  Input: nums = [1,1,1], k = 2
  Output: 2

  Algorithm: Prefix Sum + Hash Map
  1. Maintain a `currSum` that stores the sum of elements from the 
     beginning to the current index.
  2. Use a hash map `m` to store the frequency of each prefix sum 
     encountered so far.
  3. Initialize `m[0] = 1` to handle cases where `currSum == k`.
  4. For each element `nums[i]`:
     - Update `currSum += nums[i]`.
     - The number of subarrays ending at `i` with sum `k` is the 
       frequency of `currSum - k` in the hash map.
     - Increment the frequency of `currSum` in the map.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the array exactly once. Hash map operations 
    are O(1) on average.
  - Space Complexity: O(N)
    Reason: In the worst case, the hash map stores N unique prefix sums.

  Brute Force comparison:
  - Check all possible subarrays (i, j).
  - Time Complexity: O(N^2).
  - The prefix sum + hash map approach reduces this to linear time.
*/

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int count = 0;
        int currSum = 0;
        unordered_map<int, int> m;
        m[0] = 1;

        for (int x : nums) {
            currSum += x;
            if (m.find(currSum - k) != m.end()) {
                count += m[currSum - k];
            }
            m[currSum]++;
        }
        return count;
    }
};

void test(const string& label, vector<int> nums, int k, int expected) {
    cout << "Testing: " << label << " (k: " << k << ")" << endl;
    Solution sol;
    int result = sol.subarraySum(nums, k);
    if (result == expected) {
        cout << "  [PASS]" << endl;
    } else {
        cout << "  [FAIL] Result: " << result << " (Expected: " << expected << ")" << endl;
    }
}

int main() {
    test("Example 1", {1, 1, 1}, 2, 2);
    test("Example 2", {1, 2, 3}, 3, 2);
    test("With negatives", {1, -1, 0}, 0, 3); // [], [1,-1], [1,-1,0], [0]
    return 0;
}
