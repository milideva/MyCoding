/**
 * Problem: Unique Paths III
 * Given an m x n grid where:
 * 1: Start, 2: End, 0: Empty, -1: Obstacle.
 * Return the number of 4-directional walks from start to end that walk over 
 * every non-obstacle square exactly once.
 * 
 * Strategy: DFS + Backtracking
 * - Count the number of empty squares initially.
 * - Start DFS from the starting point.
 * - In each step, mark the cell as visited and decrement empty square count.
 * - If end is reached and empty square count is -1 (including start), 
 *   increment the path count.
 * - Backtrack by unmarking the cell.
 * 
 * Time Complexity: O(3^N) where N is number of cells.
 * Space Complexity: O(N)
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int totalPaths = 0;
    int emptySquares = 0;

    void dfs(vector<vector<int>>& grid, int r, int c, int count) {
        int m = grid.size();
        int n = grid[0].size();

        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == -1) return;

        if (grid[r][c] == 2) {
            if (count == emptySquares + 1) {
                totalPaths++;
            }
            return;
        }

        int temp = grid[r][c];
        grid[r][c] = -1; // Mark as visited

        dfs(grid, r + 1, c, count + 1);
        dfs(grid, r - 1, c, count + 1);
        dfs(grid, r, c + 1, count + 1);
        dfs(grid, r, c - 1, count + 1);

        grid[r][c] = temp; // Backtrack
    }

public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int startR = -1, startC = -1;
        emptySquares = 0;
        totalPaths = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    startR = i;
                    startC = j;
                } else if (grid[i][j] == 0) {
                    emptySquares++;
                }
            }
        }

        dfs(grid, startR, startC, 0);
        return totalPaths;
    }
};

int main() {
    vector<vector<int>> grid = {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 2, -1}};
    Solution sol;
    cout << "Number of unique paths: " << sol.uniquePathsIII(grid) << " (Expected: 2)" << endl;

    return 0;
}
