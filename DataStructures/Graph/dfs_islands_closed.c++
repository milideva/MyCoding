/**
 * Problem: Number of Closed Islands
 * Given a 2D grid of 0s (land) and 1s (water), return the number of closed 
 * islands. A closed island is completely surrounded by water (0s).
 * 
 * Strategy: DFS with boundary tracking using an explicit visited matrix
 * - Iterate through the grid. For each unvisited land (0), start a DFS.
 * - During DFS, mark land as visited in a separate visited matrix.
 * - If any part of the island is on the grid boundary, it's not closed.
 * - Return count of islands that never touched the boundary.
 * 
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N) - Visited matrix and recursion stack.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    bool isClosed;

    void dfs(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int r, int c) {
        int m = grid.size();
        int n = grid[0].size();

        // Out of bounds, water (1), or already visited
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 1 || visited[r][c]) {
            return;
        }

        // Mark current land cell as visited
        visited[r][c] = true;

        // If land touches the boundary, mark island as non-closed
        if (r == 0 || r == m - 1 || c == 0 || c == n - 1) {
            isClosed = false;
        }

        // Continue traversal in all 4 directions
        dfs(grid, visited, r + 1, c);
        dfs(grid, visited, r - 1, c);
        dfs(grid, visited, r, c + 1);
        dfs(grid, visited, r, c - 1);
    }

public:
    int closedIsland(const vector<vector<int>>& grid) {
        if (grid.empty()) return 0;

        int m = grid.size();
        int n = grid[0].size();
        int count = 0;

        // Separate visited array initialized to false
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // Unvisited land found
                if (grid[i][j] == 0 && !visited[i][j]) {
                    isClosed = true;
                    dfs(grid, visited, i, j);
                    if (isClosed) {
                        count++;
                    }
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
