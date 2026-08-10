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
    int nr; // #rows
    int nc; // #cols
    vector <vector <bool>> visited;

    void dfs(vector<vector<char>>& grid, int r, int c) {

        if (r < 0 || r >= nr || c < 0 || c >= nc || visited[r][c]) return;

        if (grid[r][c] == '0') return;

        visited[r][c] = true;

        dfs(grid, r + 1, c);
        dfs(grid, r - 1, c);
        dfs(grid, r, c + 1);
        dfs(grid, r, c - 1);
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        nr = grid.size();
        nc = grid[0].size();

        visited.assign(nr, vector<bool> (nc, false));

        int count = 0;

        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                if (grid[i][j] == '1' and !visited[i][j]) {
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