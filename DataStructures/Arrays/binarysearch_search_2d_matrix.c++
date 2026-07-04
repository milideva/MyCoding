#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
  LeetCode 74: Search a 2D Matrix

  Problem Description:
  You are given an m x n integer matrix `matrix` with the following 
  two properties:
  - Each row is sorted in non-decreasing order.
  - The first integer of each row is greater than the last integer of 
    the previous row.
  Given an integer `target`, return true if `target` is in matrix or 
  false otherwise.

  You must write a solution in O(log(m * n)) time complexity.

  Algorithm: Binary Search on Virtual Flattened Array
  1. Treat the 2D matrix as a sorted 1D array of size `m * n`.
  2. Map the 1D index `mid` back to 2D coordinates:
     - `row = mid / n`
     - `col = mid % n`
  3. Perform standard binary search using these coordinates.

  Complexity Analysis:
  - Time Complexity: O(log(M * N))
    Reason: We perform binary search over a virtual range of size M * N.
  - Space Complexity: O(1) auxiliary space.

  Brute Force comparison:
  - Linear scan of the entire matrix.
  - Time: O(M * N).
  - The binary search approach provides the optimal logarithmic time complexity.
*/

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;

        int rows = matrix.size();
        int cols = matrix[0].size();
        int l = 0, r = rows * cols - 1;

        while (l <= r) {
            int mid = l + (r - l) / 2;
            int val = matrix[mid / cols][mid % cols];

            if (val == target) return true;
            if (val < target) l = mid + 1;
            else r = mid - 1;
        }
        return false;
    }
};

void test(const string& label, vector<vector<int>> matrix, int target, bool expected) {
    cout << "Testing: " << label << " (Target: " << target << ")" << endl;
    Solution sol;
    bool result = sol.searchMatrix(matrix, target);
    cout << "  [" << (result == expected ? "PASS" : "FAIL") << "] Result: " << boolalpha << result << endl;
}

int main() {
    test("Example 1", {{1,3,5,7}, {10,11,16,20}, {23,30,34,60}}, 3, true);
    test("Example 2", {{1,3,5,7}, {10,11,16,20}, {23,30,34,60}}, 13, false);
    test("Single Element", {{5}}, 5, true);
    test("Empty Matrix", {}, 1, false);
    return 0;
}
