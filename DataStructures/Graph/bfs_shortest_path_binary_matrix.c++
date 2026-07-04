/*
  LeetCode 1091: Shortest Path in Binary Matrix

  Problem Description:
  In an N by N square grid, each cell is either empty (0) or blocked (1).
  A clear path from top-left to bottom-right has length k if and only 
  if it is composed of cells C_1, C_2, ..., C_k such that:
  - Adjacent cells C_i and C_{i+1} are connected 8-directionally 
    (ie., they are different and share an edge or corner)
  - C_1 is at location (0, 0) (ie. has value grid[0][0])
  - C_k is at location (N-1, N-1) (ie. has value grid[N-1][N-1])
  - If C_i is located at (r, c), then grid[r][c] is empty (ie. grid[r][c] == 0).

  Return the length of the shortest such clear path from top-left to 
  bottom-right. If such a path does not exist, return -1.

  Algorithm: Breadth-First Search (BFS) with 8-Connectivity
  1. Standard BFS starting from (0, 0).
  2. Neighbors include all 8 adjacent cells (horizontal, vertical, and diagonal).
  3. Path is only valid if cells contain 0.

  Complexity Analysis:
  - Time Complexity: O(N^2)
    Reason: We visit every cell in the N*N matrix exactly once.
  - Space Complexity: O(N^2)
    Reason: `visited` matrix and queue.

  Alternative Approaches:
  - A* Search:
    - Logic: Use a heuristic (like Chebyshev distance to destination) to 
      prioritize the search.
    - Comparison: Faster in practice for large grids, but has the same 
      worst-case complexity as BFS.
  - In-place BFS:
    - Logic: Mark visited cells by changing `grid[x][y]` to 1.
    - Space: O(1) auxiliary space (excluding queue), but modifies input.

  Brute Force comparison:
  - DFS: Exploring all paths in an 8-directional grid is extremely slow 
    and doesn't guarantee the shortest path without exhaustive searching. 
    BFS is the optimal choice for unweighted shortest paths.
*/

#include <iostream>
#include <queue>
#include <climits>
#include <cstring>
using namespace std;

class Solution {
    struct Path {
        int i, j, d;
    };
public:

    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {

        int row = grid.size();
        if (row == 0) return -1;
        int col = grid[0].size();
        if (col == 0) return -1;
        if (grid[0][0] != 0 || grid[row-1][col-1] != 0) return -1; // start must be empty/unblocked(0)
        if (row == 1 && col == 1 &&  grid[0][0] == 0) return 1;
        
        // Needs a visited state because you may not be able to modify input grid
        vector<vector<bool>> visited(row, vector<bool> (col, false));
        queue <Path> q;
        
        q.push({0, 0, 1});
        visited[0][0] = true;
        
        vector <pair<int, int>> dirs = { {-1, -1}, {-1, 0}, {-1, 1},
                                        {0, -1},  {0, 1}, 
                                        {1, -1}, {1, 0}, {1, 1} };
        
        while (!q.empty()) {

            auto [i, j, d] = q.front(); q.pop();
            // First Check if we reached the target
            if (i == row-1 && j == col-1) {
                return d;
            }          
            // Check all neighbors 
            for (auto [dx, dy] : dirs) {
                int x = i+dx, y = j+dy;
                if (x < 0 || x > row-1 || y < 0 || y > col-1) 
                    continue;
                if (grid[x][y] == 1) 
                    continue;
                if (visited[x][y] == true)
                    continue;
                // Push unvisited neighbor to the queue with increased distance
                q.push({x, y, d+1});
                // Mark visited 
                visited[x][y] = true;
            }
        }
        return -1;
    }

};

int main() {
	// input maze
	vector<vector<int>> grid =
	{
		{ 0, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 1, 1, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
		{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 0, 1, 1, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 1, 0, 1 },
		{ 0, 1, 1, 1, 0, 1, 1, 1, 0, 0 },
		{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 0, 0, 1, 0, 0, 1, 1, 0, 0, 0 },
	};
        class Solution sol;
        int dist = sol.shortestPathBinaryMatrix(grid);

        cout << "Distance : " << dist << endl;

	return 0;
}

