#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 81: Search in Rotated Sorted Array II

  Problem Description:
  Similar to search in rotated array, but the array `nums` may contain 
  duplicates. Given the rotated sorted array `nums` and an integer 
  `target`, return true if `target` is in `nums`, or false otherwise.

  Example 1:
  Input: nums = [2,5,6,0,0,1,2], target = 0
  Output: true

  Algorithm: Modified Binary Search (Handling Duplicates)
  1. Initialize `l = 0` and `r = n - 1`.
  2. While `l <= r`:
     - Calculate `mid = l + (r - l) / 2`.
     - If `nums[mid] == target`, return true.
     - Handle Duplicates: If `nums[l] == nums[mid]`, we cannot 
       confidently say which half is sorted. Increment `l` and continue.
     - Proceed with standard rotated search logic (Check sorted half).

  Complexity Analysis:
  - Time Complexity:
    - Average Case: O(log N).
    - Worst Case: O(N) when all elements are duplicates (e.g., [1,1,1,1,1]).
  - Space Complexity: O(1) auxiliary space.

  Brute Force comparison:
  - Linear scan.
  - Time: O(N).
  - The modified binary search is faster on average but degrades to 
    linear time in the absolute worst case due to duplicates.
*/

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;

        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) return true;

            // Handle the case where we can't determine the sorted half
            if (nums[l] == nums[mid]) {
                l++;
                continue;
            }

            if (nums[l] <= nums[mid]) { // Left half sorted
                if (nums[l] <= target && target < nums[mid]) r = mid - 1;
                else l = mid + 1;
            } else { // Right half sorted
                if (nums[mid] < target && target <= nums[r]) l = mid + 1;
                else r = mid - 1;
            }
        }
        return false;
    }
};

void test(const string& label, vector<int> nums, int target, bool expected) {
    cout << "Testing: " << label << " (Target: " << target << ")" << endl;
    Solution sol;
    bool result = sol.search(nums, target);
    if (result == expected) {
        cout << "  [PASS] Result: " << boolalpha << result << endl;
    } else {
        cout << "  [FAIL] Result: " << boolalpha << result << " (Expected: " << expected << ")" << endl;
    }
}

int main() {
    test("Example 1", {2, 5, 6, 0, 0, 1, 2}, 0, true);
    test("Example 2", {2, 5, 6, 0, 0, 1, 2}, 3, false);
    test("All duplicates", {1, 1, 1, 1, 1, 1}, 1, true);
    test("All duplicates, missing", {1, 1, 1, 1, 1, 1}, 2, false);
    return 0;
}
