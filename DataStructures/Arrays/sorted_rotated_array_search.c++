#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

/*
33. Search in Rotated Sorted Array

There is an integer array nums sorted in ascending order (with distinct values).

Prior to being passed to your function, nums is possibly rotated at an
unknown pivot index k (1 <= k < nums.length) such that the resulting
array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ...,
nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated
at pivot index 3 and become [4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer
target, return the index of target if it is in nums, or -1 if it is
not in nums.

You must write an algorithm with O(log n) runtime complexity.

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
Example 3:

Input: nums = [1], target = 0
Output: -1

*/

class Solution {
public:
    int search(vector<int>& nums, int target) {

        int l = 0;
        int r = nums.size() - 1;

        while (l <= r) {
            int mid = l + (r - l) / 2 ;
            if (nums[mid] == target) 
                return mid;

            if (nums[l] <= nums[mid]) {
                if (nums[l] <= target and target < nums[mid]) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }

            } else  {
                if (nums[mid] < target and target <= nums[r]) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
        }
        return -1;
    }
};

void testSearch() {
    Solution sol;

    // Test Case 1
    vector<int> nums1 = {4, 5, 6, 7, 0, 1, 2};
    int target1 = 0;
    int expected1 = 4;
    assert(sol.search(nums1, target1) == expected1);
    cout << "Test Case 1 passed!" << endl;

    // Test Case 2
    vector<int> nums2 = {4, 5, 6, 7, 0, 1, 2};
    int target2 = 3;
    int expected2 = -1;
    assert(sol.search(nums2, target2) == expected2);
    cout << "Test Case 2 passed!" << endl;

    // Test Case 3
    vector<int> nums3 = {1};
    int target3 = 0;
    int expected3 = -1;
    assert(sol.search(nums3, target3) == expected3);
    cout << "Test Case 3 passed!" << endl;

    // Additional Test Case 4: No rotation
    vector<int> nums4 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int target4 = 6;
    int expected4 = 5;
    assert(sol.search(nums4, target4) == expected4);
    cout << "Test Case 4 passed!" << endl;

    // Additional Test Case 5: Full rotation
    vector<int> nums5 = {6, 7, 8, 9, 10, 1, 2, 3, 4, 5};
    int target5 = 1;
    int expected5 = 5;
    assert(sol.search(nums5, target5) == expected5);
    cout << "Test Case 5 passed!" << endl;
}

int main() {
    testSearch();
    cout << "All test cases passed!" << endl;
    return 0;
}