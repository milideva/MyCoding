/**
 * Problem: Shortest Path in Binary Matrix
 * Given an N x N binary matrix, return the length of the shortest clear path 
 * from top-left (0,0) to bottom-right (N-1, N-1). A clear path only contains 0s. 
 * You can move in 8 directions.
 * 
 * Strategy: BFS (Shortest Path in Unweighted Graph)
 * - Start BFS from (0,0) if it's 0.
 * - Explore all 8 neighbors.
 * - Mark visited cells or modify the grid to 1 to avoid cycles.
 * - The first time (N-1, N-1) is reached, return the current distance.
 * 
 * Time Complexity: O(N^2)
 * Space Complexity: O(N^2)
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) return -1;
        if (n == 1) return 1;

        queue<pair<int, int>> q;
        q.push({0, 0});
        grid[0][0] = 1; // Mark as visited with distance 1

        int dirs[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        int distance = 1;

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto [r, c] = q.front();
                q.pop();

                if (r == n - 1 && c == n - 1) return distance;

                for (auto& d : dirs) {
                    int nr = r + d[0];
                    int nc = c + d[1];

                    if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0) {
                        grid[nr][nc] = 1; // Mark as visited
                        q.push({nr, nc});
                    }
                }
            }
            distance++;
        }

        return -1;
    }
};

int main() {
    vector<vector<int>> grid1 = {{0, 1}, {1, 0}};
    Solution sol;
    cout << "Shortest path (Example 1): " << sol.shortestPathBinaryMatrix(grid1) << " (Expected: 2)" << endl;

    vector<vector<int>> grid2 = {{0, 0, 0}, {1, 1, 0}, {1, 1, 0}};
    cout << "Shortest path (Example 2): " << sol.shortestPathBinaryMatrix(grid2) << " (Expected: 4)" << endl;

    return 0;
}
