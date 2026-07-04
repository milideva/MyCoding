#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 80: Remove Duplicates from Sorted Array II

  Problem Description:
  Given an integer array `nums` sorted in non-decreasing order, 
  remove some duplicates in-place such that each unique element 
  appears at most twice. The relative order of the elements should 
  be kept the same.

  Return the number of unique elements `k` after placing the result 
  in the first `k` slots of `nums`.

  Example 1:
  Input: nums = [1,1,1,2,2,3]
  Output: 5, nums = [1,1,2,2,3,_]

  Algorithm: Two Pointers (Look-back)
  1. Maintain a `write` pointer at index 0.
  2. Iterate through the array with a `read` pointer.
  3. For each element `nums[read]`:
     - If the element is one of the first two (`write < 2`), or 
       if it's different from the element placed two positions back 
       (`nums[read] != nums[write - 2]`):
       - Copy `nums[read]` to `nums[write]`.
       - Increment `write`.
  4. This naturally allows at most two occurrences because a third 
     occurrence would equal `nums[write - 2]`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the array once.
  - Space Complexity: O(1) auxiliary space.

  Brute Force comparison:
  - Count frequencies and build a new array.
  - Time: O(N), Space: O(N).
  - The two-pointer approach is the most space-efficient.
*/

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) return n;

        int write = 2;
        for (int read = 2; read < n; ++read) {
            // Compare with the element at 'write - 2'
            if (nums[read] != nums[write - 2]) {
                nums[write++] = nums[read];
            }
        }
        return write;
    }
};

void test(const string& label, vector<int> nums, int expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    int result = sol.removeDuplicates(nums);
    if (result == expected) {
        cout << "  [PASS] Result Size: " << result << " Array: [ ";
        for (int i = 0; i < result; ++i) cout << nums[i] << " ";
        cout << "]" << endl;
    } else {
        cout << "  [FAIL] Result: " << result << " (Expected: " << expected << ")" << endl;
    }
}

int main() {
    test("Example 1", {1, 1, 1, 2, 2, 3}, 5);
    test("Example 2", {0, 0, 1, 1, 1, 1, 2, 3, 3}, 7);
    test("Short Array", {1, 1}, 2);
    test("All Same", {1, 1, 1, 1}, 2);
    return 0;
}
