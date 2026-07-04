/**
 * Problem: Shortest Path to Get Food
 * Given a grid with your location '*', food '#', obstacles 'X', and free 
 * space 'O', find the shortest path to any food cell.
 * 
 * Strategy: BFS (Shortest Path in Unweighted Graph)
 * - Locate the start position '*'.
 * - Start BFS from that position.
 * - Visit 4-directional neighbors.
 * - Return the distance to the first '#' found.
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
    int getFood(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int startR = -1, startC = -1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '*') {
                    startR = i;
                    startC = j;
                    break;
                }
            }
            if (startR != -1) break;
        }

        queue<pair<int, int>> q;
        q.push({startR, startC});
        grid[startR][startC] = 'X'; // Mark as visited

        int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int distance = 0;

        while (!q.empty()) {
            int size = q.size();
            distance++;
            for (int i = 0; i < size; i++) {
                auto [r, c] = q.front();
                q.pop();

                for (auto& d : dirs) {
                    int nr = r + d[0];
                    int nc = c + d[1];

                    if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                        if (grid[nr][nc] == '#') return distance;
                        if (grid[nr][nc] == 'O') {
                            grid[nr][nc] = 'X'; // Mark as visited
                            q.push({nr, nc});
                        }
                    }
                }
            }
        }

        return -1;
    }
};

int main() {
    vector<vector<char>> grid1 = {
        {'X', 'X', 'X', 'X', 'X', 'X'},
        {'X', '*', 'O', 'O', 'O', 'X'},
        {'X', 'O', 'O', '#', 'O', 'X'},
        {'X', 'X', 'X', 'X', 'X', 'X'}
    };
    Solution sol;
    cout << "Distance to food (Example 1): " << sol.getFood(grid1) << " (Expected: 3)" << endl;

    vector<vector<char>> grid2 = {
        {'X', 'X', 'X'},
        {'X', '*', 'X'},
        {'X', 'X', 'X'}
    };
    cout << "Distance to food (Example 2): " << sol.getFood(grid2) << " (Expected: -1)" << endl;

    return 0;
}
