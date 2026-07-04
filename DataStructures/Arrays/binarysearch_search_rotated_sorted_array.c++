#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 33: Search in Rotated Sorted Array

  Problem Description:
  There is an integer array `nums` sorted in ascending order (with 
  distinct values). `nums` is possibly rotated at an unknown pivot 
  index `k`. Given the array `nums` after rotation and an integer 
  `target`, return the index of `target` if it is in `nums`, or -1 
  if it is not.

  You must write an algorithm with O(log N) runtime complexity.

  Example 1:
  Input: nums = [4,5,6,7,0,1,2], target = 0
  Output: 4

  Algorithm: Modified Binary Search
  1. Initialize `l = 0` and `r = n - 1`.
  2. While `l <= r`:
     - Calculate `mid = l + (r - l) / 2`.
     - If `nums[mid] == target`, return `mid`.
     - Determine which half is sorted:
       - If `nums[l] <= nums[mid]`: Left half is sorted.
         - If `nums[l] <= target < nums[mid]`, target is in left; `r = mid - 1`.
         - Else, target is in right; `l = mid + 1`.
       - Else: Right half is sorted.
         - If `nums[mid] < target <= nums[r]`, target is in right; `l = mid + 1`.
         - Else, target is in left; `r = mid - 1`.
  3. If not found, return -1.

  Complexity Analysis:
  - Time Complexity: O(log N)
    Reason: In each step, we eliminate half of the search space.
  - Space Complexity: O(1) auxiliary space.

  Brute Force comparison:
  - Linear scan of the entire array.
  - Time: O(N).
  - Modified binary search provides the optimal logarithmic time complexity.
*/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;

        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) return mid;

            if (nums[l] <= nums[mid]) { // Left half sorted
                if (nums[l] <= target && target < nums[mid]) r = mid - 1;
                else l = mid + 1;
            } else { // Right half sorted
                if (nums[mid] < target && target <= nums[r]) l = mid + 1;
                else r = mid - 1;
            }
        }
        return -1;
    }
};

void test(const string& label, vector<int> nums, int target, int expected) {
    cout << "Testing: " << label << " (Target: " << target << ")" << endl;
    Solution sol;
    int result = sol.search(nums, target);
    if (result == expected) {
        cout << "  [PASS] Index: " << result << endl;
    } else {
        cout << "  [FAIL] Result: " << result << " (Expected: " << expected << ")" << endl;
    }
}

int main() {
    test("Example 1", {4, 5, 6, 7, 0, 1, 2}, 0, 4);
    test("Example 2", {4, 5, 6, 7, 0, 1, 2}, 3, -1);
    test("No rotation", {1, 2, 3, 4, 5}, 3, 2);
    test("Empty list", {}, 5, -1);
    return 0;
}
