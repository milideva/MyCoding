/**
 * Problem: Max Area of Island
 * Given a 2D binary grid of 0s and 1s, return the maximum area of an island. 
 * If there is no island, return 0.
 * 
 * Strategy: DFS (Flood Fill)
 * - Iterate through the grid. For each '1' found, start a DFS.
 * - DFS returns the count of all connected '1's (the area) and marks them 
 *    as '0' to avoid re-visiting.
 * - Maintain the maximum area found so far.
 * 
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N) - Recursion stack.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    int dfs(vector<vector<int>>& grid, int r, int c) {
        int m = grid.size();
        int n = grid[0].size();

        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 0) return 0;

        grid[r][c] = 0; // Mark as visited

        return 1 + dfs(grid, r + 1, c) +
                   dfs(grid, r - 1, c) +
                   dfs(grid, r, c + 1) +
                   dfs(grid, r, c - 1);
    }

public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if (grid.empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        int maxArea = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    maxArea = max(maxArea, dfs(grid, i, j));
                }
            }
        }
        return maxArea;
    }
};

int main() {
    vector<vector<int>> grid = {
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}
    };
    Solution sol;
    cout << "Max area of island: " << sol.maxAreaOfIsland(grid) << " (Expected: 6)" << endl;

    return 0;
}
