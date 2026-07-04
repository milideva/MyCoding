#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 75: Sort Colors (Dutch National Flag Problem)

  Problem Description:
  Given an array `nums` with `n` objects colored red, white, or blue, 
  sort them in-place so that objects of the same color are adjacent, 
  with the colors in the order red, white, and blue. 
  (0 = Red, 1 = White, 2 = Blue).

  You must solve this problem without using the library's sort function.

  Algorithm: Three Pointers (Dutch National Flag)
  1. Maintain three pointers: `low`, `mid`, and `high`.
     - `nums[0...low-1]` are all 0s.
     - `nums[low...mid-1]` are all 1s.
     - `nums[high+1...n-1]` are all 2s.
  2. Initially: `low = 0`, `mid = 0`, `high = n - 1`.
  3. While `mid <= high`:
     - If `nums[mid] == 0`: Swap `nums[low]` and `nums[mid]`, 
       increment `low` and `mid`.
     - If `nums[mid] == 1`: Increment `mid`.
     - If `nums[mid] == 2`: Swap `nums[mid]` and `nums[high]`, 
       decrement `high`.
  4. This ensures all elements are partitioned into their correct sections.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the array exactly once with the `mid` pointer.
  - Space Complexity: O(1) auxiliary space.

  Alternative Approaches:
  - Counting Sort (Two Pass):
    - 1st Pass: Count 0s, 1s, and 2s.
    - 2nd Pass: Overwrite the array with the counts.
    - Time: O(N), Space: O(1).
    - Comparison: The three-pointer approach is a single-pass solution.

  Brute Force comparison:
  - Standard library sort.
  - Time Complexity: O(N log N).
  - The single-pass three-pointer approach is faster for this 
    constrained set of values.
*/

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int low = 0, mid = 0, high = n - 1;

        while (mid <= high) {
            if (nums[mid] == 0) {
                swap(nums[low++], nums[mid++]);
            } else if (nums[mid] == 1) {
                mid++;
            } else {
                swap(nums[mid], nums[high--]);
            }
        }
    }

    void printVector(const vector<int>& nums) {
        for (int x : nums) cout << x << " ";
        cout << endl;
    }
};

void test(const string& label, vector<int> nums) {
    cout << "Testing: " << label << endl;
    Solution sol;
    sol.sortColors(nums);
    cout << "  Result: "; sol.printVector(nums);
}

int main() {
    test("Example 1", {2, 0, 2, 1, 1, 0});
    test("Example 2", {2, 0, 1});
    test("All Same", {1, 1, 1});
    test("Already Sorted", {0, 1, 2});
    return 0;
}
