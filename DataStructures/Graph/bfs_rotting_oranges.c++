/**
 * Problem: Rotting Oranges
 * Given an M x N grid representing fresh (1), rotten (2), or empty (0) cells, 
 * find the minimum minutes until all fresh oranges are rotten. If impossible, 
 * return -1.
 * 
 * Strategy: Multi-source BFS
 * - Initially enqueue all rotten oranges and count fresh oranges.
 * - Perform BFS level by level. Each level represents one minute.
 * - For each rotten orange, infect its 4-directional neighbors.
 * - If fresh oranges remain after BFS, return -1.
 * 
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N)
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        if (grid.empty()) return 0;
        int M = grid.size();
        int N = grid[0].size();
        int freshCount = 0;
        queue<pair<int, int>> q;

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 2) q.push({i, j});
                else if (grid[i][j] == 1) freshCount++;
            }
        }

        if (freshCount == 0) return 0;

        int minutes = 0;
        int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        while (!q.empty()) {
            int levelSize = q.size();
            bool infected = false;
            for (int i = 0; i < levelSize; i++) {
                auto [r, c] = q.front();
                q.pop();

                for (auto& d : dirs) {
                    int nr = r + d[0];
                    int nc = c + d[1];

                    if (nr >= 0 && nr < M && nc >= 0 && nc < N && grid[nr][nc] == 1) {
                        grid[nr][nc] = 2;
                        q.push({nr, nc});
                        freshCount--;
                        infected = true;
                    }
                }
            }
            if (infected) minutes++;
        }

        return (freshCount == 0) ? minutes : -1;
    }
};

int main() {
    vector<vector<int>> grid1 = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    Solution sol;
    cout << "Minutes to rot all oranges (Example 1): " << sol.orangesRotting(grid1) << " (Expected: 4)" << endl;

    vector<vector<int>> grid2 = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};
    cout << "Minutes to rot all oranges (Example 2): " << sol.orangesRotting(grid2) << " (Expected: -1)" << endl;

    return 0;
}
