#include <vector>
#include <iostream>

using namespace std;

/*
  LeetCode 283: Move Zeroes

  Problem Description:
  Given an integer array `nums`, move all 0's to the end of it while 
  maintaining the relative order of the non-zero elements.

  Note that you must do this in-place without making a copy of the array.

  Example 1:
  Input: nums = [0,1,0,3,12]
  Output: [1,3,12,0,0]

  Algorithm: Two Pointers (Read and Write)
  1. Maintain a `writePtr` (initially 0).
  2. Iterate through the array with a `readPtr`.
  3. If `nums[readPtr]` is non-zero, copy it to `nums[writePtr]` and 
     increment `writePtr`.
  4. After the loop, fill the remaining positions from `writePtr` 
     to the end of the array with zeros.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the array exactly once.
  - Space Complexity: O(1) auxiliary space.
    Reason: In-place modification.

  Brute Force comparison:
  - Create a new array, copy non-zeros, then copy zeros.
  - Time: O(N), Space: O(N).
  - The two-pointer approach is more space-efficient.
*/

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int writePtr = 0;
        
        // 1. Overwrite non-zero elements
        for (int i = 0; i < n; ++i) {
            if (nums[i] != 0) {
                nums[writePtr++] = nums[i];
            }
        }
        
        // 2. Fill the rest with zeros
        while (writePtr < n) {
            nums[writePtr++] = 0;
        }
    }

    void printVector(const vector<int>& nums) {
        for (int x : nums) cout << x << " ";
        cout << endl;
    }
};

void test(const string& label, vector<int> nums, const vector<int>& expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    sol.moveZeroes(nums);
    cout << "  Result: "; sol.printVector(nums);
}

int main() {
    test("Example 1", {0, 1, 0, 3, 12}, {1, 3, 12, 0, 0});
    test("All Zeros", {0, 0, 0}, {0, 0, 0});
    test("No Zeros", {1, 2, 3}, {1, 2, 3});
    test("Single Zero", {0}, {0});
    return 0;
}
