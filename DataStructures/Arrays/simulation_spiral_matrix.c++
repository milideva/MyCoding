#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 54: Spiral Matrix

  Problem Description:
  Given an m x n matrix, return all elements of the matrix in 
  spiral order.

  Example 1:
  Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
  Output: [1,2,3,6,9,8,7,4,5]

  Algorithm: Simulation with Boundaries
  1. Maintain four boundaries: `top`, `bottom`, `left`, and `right`.
  2. Initially: `top = 0`, `bottom = m-1`, `left = 0`, `right = n-1`.
  3. While `top <= bottom` and `left <= right`:
     - Traverse from `left` to `right` along `top` row. Increment `top`.
     - Traverse from `top` to `bottom` along `right` column. Decrement `right`.
     - Check if `top <= bottom`:
       - Traverse from `right` to `left` along `bottom` row. Decrement `bottom`.
     - Check if `left <= right`:
       - Traverse from `bottom` to `top` along `left` column. Increment `left`.

  Complexity Analysis:
  - Time Complexity: O(M * N)
    Reason: We visit every element of the matrix exactly once.
  - Space Complexity: O(1) auxiliary space (excluding the result vector).

  Brute Force comparison:
  - N/A. Simulation is the standard way to solve this problem.
*/

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty()) return {};

        int m = matrix.size(), n = matrix[0].size();
        int top = 0, bottom = m - 1, left = 0, right = n - 1;
        vector<int> result;

        while (top <= bottom && left <= right) {
            // Move Right
            for (int j = left; j <= right; ++j) result.push_back(matrix[top][j]);
            top++;

            // Move Down
            for (int i = top; i <= bottom; ++i) result.push_back(matrix[i][right]);
            right--;

            // Move Left
            if (top <= bottom) {
                for (int j = right; j >= left; --j) result.push_back(matrix[bottom][j]);
                bottom--;
            }

            // Move Up
            if (left <= right) {
                for (int i = bottom; i >= top; --i) result.push_back(matrix[i][left]);
                left++;
            }
        }
        return result;
    }
};

void test(const string& label, vector<vector<int>> matrix) {
    cout << "Testing: " << label << endl;
    Solution sol;
    vector<int> result = sol.spiralOrder(matrix);
    cout << "  Result: ";
    for (int x : result) cout << x << " ";
    cout << endl;
}

int main() {
    test("Example 1", {{1,2,3},{4,5,6},{7,8,9}});
    test("Example 2", {{1,2,3,4},{5,6,7,8},{9,10,11,12}});
    test("Single Row", {{1,2,3}});
    test("Single Column", {{1},{2},{3}});
    return 0;
}
