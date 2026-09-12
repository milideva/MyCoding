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

/*
  Brute Force DFS (Time Limit Exceeded - TLE)

  Explanation of TLE due to Redundant Recomputations:
  In a naive DFS without memoization, we explore every single possible path from the top-left 
  to the bottom-right. This results in an exponential number of redundant calculations 
  because different paths overlap at the same cells.

  Example Walkthrough on a 3x3 Grid:
  ---------------------------------
  Grid coordinates:
    (0,0) -> (0,1) -> (0,2)
      |        |        |
    (1,0) -> (1,1) -> (1,2)
      |        |        |
    (2,0) -> (2,1) -> (2,2)

  Consider how we reach the middle cell (1,1):
  - Path A: (0,0) -> (0,1) -> (1,1) [Right then Down]
  - Path B: (0,0) -> (1,0) -> (1,1) [Down then Right]

  When DFS reaches (1,1) via Path A:
    It recursively explores all paths from (1,1) to the bottom-right (2,2):
    1. dfs(grid, 2, 1, ...) [Down to (2,1)]
    2. dfs(grid, 1, 2, ...) [Right to (1,2)]
    These paths eventually reach (2,2) and find their minimum.

  When DFS backtracks and later reaches (1,1) via Path B:
    It has absolutely no memory of its previous search from (1,1). It must completely 
    re-explore the exact same sub-grid starting from (1,1) down to (2,2) all over again:
    1. dfs(grid, 2, 1, ...) [Down to (2,1)]
    2. dfs(grid, 1, 2, ...) [Right to (1,2)]

  As the grid dimensions (M, N) increase, this duplication scales exponentially.
  The total number of paths to explore is:
      Total Paths = C(M + N - 2, M - 1)
  
  For a standard LeetCode grid of 200 x 200, this is C(398, 199) ≈ 2 * 10^118 operations.
  This exceeds LeetCode's typical 10^8 operations (2-second limit), running into a 
  Time Limit Exceeded (TLE) error.

  Complexity Analysis:
  - Time Complexity: O(2^(M + N)) worst-case. More precisely, O(C(M + N - 2, M - 1)) as it explores every path.
  - Space Complexity: O(M + N) due to the maximum recursion depth of the call stack.
*/
class Solution_DFS_TLE {
    int nr;
    int nc;
    int pathSumMin;

    void dfs (vector<vector<int>>& grid, int x, int y, int pathSum) {
        if (x >= nr or y >= nc) 
            return;
        pathSum += grid[x][y];
        if (pathSum >= pathSumMin) return;
        if (x == nr - 1 and y == nc - 1) {
            if (pathSum < pathSumMin)
                pathSumMin = pathSum;
        }
        dfs(grid, x + 1, y, pathSum);
        dfs(grid, x, y + 1, pathSum);
    }
public:
    int minPathSum(vector<vector<int>>& grid) {
        nr = grid.size();
        nc = grid[0].size();
        pathSumMin = INT_MAX;
        dfs(grid, 0, 0, 0);
        return pathSumMin;
    }
};

void test(vector<vector<int>> grid, int expected) {
    Solution sol;
    Solution_DFS_TLE sol_tle;

    int result_dp = sol.minPathSum(grid);
    int result_dfs = sol_tle.minPathSum(grid);

    cout << "DP Result: " << result_dp << (result_dp == expected ? " [PASS]" : " [FAIL]");
    cout << " | DFS TLE Result: " << result_dfs << (result_dfs == expected ? " [PASS]" : " [FAIL]") << endl;
}

int main() {
    test({{1,3,1},{1,5,1},{4,2,1}}, 7);
    test({{1,2,3},{4,5,6}}, 12);
    return 0;
}
