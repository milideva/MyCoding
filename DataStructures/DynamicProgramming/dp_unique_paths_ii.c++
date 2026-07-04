#include <iostream>
#include <vector>

using namespace std;

/*
  LeetCode 63: Unique Paths II

  Problem Description:
  Same as Unique Paths, but the grid may contain obstacles. 
  An obstacle is marked as 1 and a space as 0. The robot cannot 
  pass through obstacles.

  Algorithm: Dynamic Programming (Tabulation)
  1. Let `dp[i][j]` be the number of ways to reach `(i, j)`.
  2. If `grid[i][j] == 1`, `dp[i][j] = 0`.
  3. Base Case: `dp[0][0] = 1` if `grid[0][0] == 0`.
  4. Iterate through row 0 and column 0, propagating 1 until an 
     obstacle is hit.
  5. Recursive Step: `dp[i][j] = dp[i-1][j] + dp[i][j-1]`.

  Complexity Analysis:
  - Time Complexity: O(M * N)
  - Space Complexity: O(N) or O(M * N).
*/

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        if (obstacleGrid[0][0] == 1) return 0;

        vector<long long> dp(n, 0);
        dp[0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (obstacleGrid[i][j] == 1) {
                    dp[j] = 0;
                } else if (j > 0) {
                    dp[j] += dp[j - 1];
                }
            }
        }
        return (int)dp[n - 1];
    }
};

void test(vector<vector<int>> grid, int expected) {
    Solution sol;
    int result = sol.uniquePathsWithObstacles(grid);
    cout << "Obstacle Grid Result: " << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    test({{0,0,0},{0,1,0},{0,0,0}}, 2);
    test({{0,1},{0,0}}, 1);
    test({{1,0}}, 0);
    return 0;
}
