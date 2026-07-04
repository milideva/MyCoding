/**
 * Problem: Number of Distinct Islands
 * Given a 2D binary matrix, return the number of distinct islands. 
 * Two islands are distinct if one cannot be translated to equal the other.
 * 
 * Strategy: DFS + Path Serialization
 * - Iterate through the grid. For each unvisited land (1), start a DFS.
 * - During DFS, record the sequence of moves ('u', 'd', 'l', 'r') to form 
 *    a path signature string.
 * - Add a "backtrack" marker (e.g., 'b') whenever returning from a recursive call.
 * - Store all signatures in a hash set to count unique island shapes.
 * 
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N)
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
    void dfs(vector<vector<int>>& grid, int r, int c, char dir, string& signature) {
        int m = grid.size();
        int n = grid[0].size();

        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 0) return;

        grid[r][c] = 0; // Mark as visited
        signature += dir;

        dfs(grid, r + 1, c, 'd', signature);
        dfs(grid, r - 1, c, 'u', signature);
        dfs(grid, r, c + 1, 'r', signature);
        dfs(grid, r, c - 1, 'l', signature);

        signature += 'b'; // Backtrack marker
    }

public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        if (grid.empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        unordered_set<string> shapes;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    string signature = "";
                    dfs(grid, i, j, 's', signature); // 's' for start
                    shapes.insert(signature);
                }
            }
        }
        return shapes.size();
    }
};

int main() {
    vector<vector<int>> grid = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1}
    };
    Solution sol;
    cout << "Number of distinct islands: " << sol.numDistinctIslands(grid) << " (Expected: 1)" << endl;

    return 0;
}
