/**
 * Problem: Number of Closed Islands
 * Given a 2D grid of 0s (land) and 1s (water), return the number of closed 
 * islands. A closed island is completely surrounded by water (0s).
 * 
 * Strategy: DFS with boundary tracking
 * - Iterate through the grid. For each unvisited land (0), start a DFS.
 * - During DFS, mark land as visited (or flip to 1).
 * - If any part of the island is on the grid boundary, it's not closed.
 * - Return count of islands that never touched the boundary.
 * 
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N) - Recursion stack.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    bool isClosed;

    void dfs(vector<vector<int>>& grid, int r, int c) {
        int m = grid.size();
        int n = grid[0].size();

        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 1) return;

        // If we hit the boundary, the island is not closed
        if (r == 0 || r == m - 1 || c == 0 || c == n - 1) {
            isClosed = false;
        }

        grid[r][c] = 1; // Mark as visited

        dfs(grid, r + 1, c);
        dfs(grid, r - 1, c);
        dfs(grid, r, c + 1);
        dfs(grid, r, c - 1);
    }

public:
    int closedIsland(vector<vector<int>>& grid) {
        if (grid.empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        int count = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    isClosed = true;
                    dfs(grid, i, j);
                    if (isClosed) count++;
                }
            }
        }
        return count;
    }
};

int main() {
    vector<vector<int>> grid = {
        {1, 1, 1, 1, 1, 1, 1, 0},
        {1, 0, 0, 0, 0, 1, 1, 0},
        {1, 0, 1, 0, 1, 1, 1, 0},
        {1, 0, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0}
    };
    Solution sol;
    cout << "Number of closed islands: " << sol.closedIsland(grid) << " (Expected: 2)" << endl;

    return 0;
}
