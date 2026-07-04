/**
 * Problem: Shortest Path in a Maze
 * Given a 2D binary matrix where 1 represents a path and 0 represents a wall, 
 * find the length of the shortest path from source to destination.
 * 
 * Strategy: BFS (Shortest Path in Unweighted Graph)
 * - Start BFS from source.
 * - Explore 4-directional neighbors.
 * - Use a distance matrix or store distance in the queue.
 * 
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N)
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int r, c, dist;
};

class Solution {
public:
    int shortestPath(vector<vector<int>>& maze, pair<int, int> start, pair<int, int> end) {
        int m = maze.size();
        int n = maze[0].size();

        if (maze[start.first][start.second] == 0 || maze[end.first][end.second] == 0) return -1;

        queue<Node> q;
        q.push({start.first, start.second, 0});
        maze[start.first][start.second] = 0; // Mark as visited

        int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        while (!q.empty()) {
            Node curr = q.front();
            q.pop();

            if (curr.r == end.first && curr.c == end.second) return curr.dist;

            for (auto& d : dirs) {
                int nr = curr.r + d[0];
                int nc = curr.c + d[1];

                if (nr >= 0 && nr < m && nc >= 0 && nc < n && maze[nr][nc] == 1) {
                    maze[nr][nc] = 0; // Mark as visited
                    q.push({nr, nc, curr.dist + 1});
                }
            }
        }

        return -1;
    }
};

int main() {
    vector<vector<int>> maze = {
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {0, 0, 1, 0, 1, 1, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {0, 0, 1, 0, 0, 1, 1, 0, 0, 1}
    };

    Solution sol;
    cout << "Shortest path (7,3) to (7,5): " 
         << sol.shortestPath(maze, {7, 3}, {7, 5}) << " (Expected: 2)" << endl;

    return 0;
}
