#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/*
  LeetCode 64: Minimum Path Sum

  Problem Description:
  Given a `m x n` grid filled with non-negative numbers, find a 
  path from top left to bottom right which minimizes the sum of 
  all numbers along its path. You can only move down or right.

  Algorithm: Dynamic Programming (Tabulation)
  1. Let `dp[i][j]` be the minimum path sum to reach cell `(i, j)`.
  2. Base Case: `dp[0][0] = grid[0][0]`.
  3. First Row: `dp[0][j] = dp[0][j-1] + grid[0][j]`.
  4. First Column: `dp[i][0] = dp[i-1][0] + grid[i][0]`.
  5. Recursive Step: `dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])`.

  Complexity Analysis:
  - Time Complexity: O(M * N)
  - Space Complexity: O(N) or O(M * N).
*/

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> dp(n, 0);

        dp[0] = grid[0][0];
        for (int j = 1; j < n; j++) dp[j] = dp[j - 1] + grid[0][j];

        for (int i = 1; i < m; i++) {
            dp[0] += grid[i][0];
            for (int j = 1; j < n; j++) {
                dp[j] = grid[i][j] + min(dp[j], dp[j - 1]);
            }
        }
        return dp[n - 1];
    }
};

void test(vector<vector<int>> grid, int expected) {
    Solution sol;
    int result = sol.minPathSum(grid);
    cout << "Min Path Sum: " << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    test({{1,3,1},{1,5,1},{4,2,1}}, 7);
    test({{1,2,3},{4,5,6}}, 12);
    return 0;
}
