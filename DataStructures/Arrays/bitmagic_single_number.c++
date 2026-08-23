#include <vector>
#include <iostream>
#include <string>

using namespace std;

/*
  Solution
  Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.

  You must implement a solution with a linear runtime complexity and use only constant extra space.

  Example 1:
  Input: nums = [2,2,1]
  Output: 1

  Example 2:
  Input: nums = [4,1,2,1,2]
  Output: 4

  Example 3:
  Input: nums = [1]
  Output: 1

  Constraints:
  1 <= nums.length <= 3 * 104
  -3 * 104 <= nums[i] <= 3 * 104
  Each element in the array appears twice except for one element which appears only once.

  Algorithm: Bit Magic (Bitwise XOR)
  - x ^ x = 0 (Any number XOR'ed with itself is 0)
  - x ^ 0 = x (Any number XOR'ed with 0 is the number itself)
  - The XOR operation is associative and commutative: (a ^ b) ^ a = (a ^ a) ^ b = 0 ^ b = b.
  - Therefore, XORing all elements together cancels out pairs, leaving only the single number.

  Complexity Analysis:
  - Time Complexity: O(N) where N is the number of elements in the array.
  - Space Complexity: O(1) auxiliary space as we only use a single variable for XOR.
*/

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        // a ^ a = 0
        // a ^ 0 = a
        // a ^ b ^ a = a ^ a ^ c = 0 ^ c = c
        
        int res = 0;
        
        for (auto n : nums) {
            res = res ^ n;
        }
        
        return res;
    }
};

void test(const string& label, vector<int> nums, int expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    int result = sol.singleNumber(nums);
    if (result == expected) {
        cout << "  [PASS] Expected: " << expected << ", Result: " << result << endl;
    } else {
        cout << "  [FAIL] Expected: " << expected << ", Result: " << result << endl;
    }
}

int main() {
    test("Example 1", {2, 2, 1}, 1);
    test("Example 2", {4, 1, 2, 1, 2}, 4);
    test("Example 3", {1}, 1);
    test("Negative elements", {-1, 2, -1, 3, 2}, 3);
    return 0;
}
