/**
 * Problem: Number of Islands
 * Given an M x N 2D binary grid which represents a map of '1's (land) 
 * and '0's (water), return the number of islands.
 * 
 * Strategy: DFS (Flood Fill)
 * - Iterate through the grid. For each '1' found, start a DFS.
 * - DFS visits all connected '1's and marks them as '0' to avoid re-visiting.
 * - Each DFS start represents one unique island.
 * 
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N) - Recursion stack in worst case.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    void dfs(vector<vector<char>>& grid, int r, int c) {
        int m = grid.size();
        int n = grid[0].size();

        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == '0') return;

        grid[r][c] = '0'; // Mark as visited

        dfs(grid, r + 1, c);
        dfs(grid, r - 1, c);
        dfs(grid, r, c + 1);
        dfs(grid, r, c - 1);
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        int count = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);
                    count++;
                }
            }
        }
        return count;
    }
};

int main() {
    vector<vector<char>> grid = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '1', '0'}
    };
    Solution sol;
    cout << "Number of islands: " << sol.numIslands(grid) << " (Expected: 2)" << endl;

    return 0;
}
