#include <iostream>
#include <vector>

using namespace std;

/*
  LeetCode 62: Unique Paths

  Problem Description:
  A robot is located at the top-left corner of a `m x n` grid. The 
  robot can only move either down or right. The robot is trying to 
  reach the bottom-right corner. How many possible unique paths 
  are there?

  Algorithm: Dynamic Programming (Tabulation)
  1. Let `dp[i][j]` be the number of unique paths to reach cell `(i, j)`.
  2. Base Case: `dp[0][j] = 1` and `dp[i][0] = 1` (Only one way 
     to reach any cell in the first row or column).
  3. Recursive Step: `dp[i][j] = dp[i-1][j] + dp[i][j-1]`.
  4. Optimization: Use a 1D array to reduce space to O(N).

  Complexity Analysis:
  - Time Complexity: O(M * N)
    Reason: We iterate through every cell in the grid.
  - Space Complexity: O(N) or O(M * N).
*/

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[j] += dp[j - 1];
            }
        }
        return dp[n - 1];
    }
};

void test(int m, int n, int expected) {
    Solution sol;
    int result = sol.uniquePaths(m, n);
    cout << "Grid: " << m << "x" << n << " -> Unique Paths: " << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    test(3, 7, 28);
    test(3, 2, 3);
    test(3, 3, 6);
    return 0;
}
