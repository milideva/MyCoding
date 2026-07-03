/*
  LeetCode 695: Max Area of Island

  Algorithm: DFS (Flood Fill)
  1. Iterate through every cell in the grid.
  2. If the cell contains '1' and hasn't been visited:
     - Start a DFS to find all connected land cells.
     - The DFS returns the total count of cells visited (the area).
  3. Keep track of the maximum area found across all DFS starts.

  Complexity Analysis:
  - Time Complexity: O(M * N)
    Reason: We visit every cell in the grid exactly once.
  - Space Complexity: O(M * N)
    Reason: The `visited` matrix and the recursion stack (worst case is a 
    grid of all land).

  Alternative Approaches:
  - BFS: Use a queue.
    - Time: O(M * N), Space: O(min(M, N)).
  - Union-Find: Maintain component sizes.
    - Time: O(M * N * α(M*N)).
  - In-place DFS: Overwrite '1's with '0's as they are visited to avoid 
    the `visited` matrix.
    - Space: Reduced to O(H) for recursion stack.

  Brute Force comparison:
  - For every cell, calculate the area of the island it belongs to without 
    global state tracking.
  - Time Complexity: O((M*N)^2).
  - Comparison: Standard flood-fill with visited tracking is the optimal O(MN).
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
  vector <vector <bool>> visited;
  int r, c;
  
  bool isSafe (int x, int y) {
    return x < r && x >= 0  && y >= 0 && y < c;
  }
  
  int dfs_2 (vector<vector<int>>& grid, int i, int j) {
    visited[i][j] = true;
    int count = 1;
    
    int rAdj[] = { -1, 0, 0, +1};
    int cAdj[] = { 0, -1, +1, 0};
    
    for (int k = 0; k < 4; k++) {
      int dx = i + rAdj[k];
      int dy = j + cAdj[k];
      if (isSafe(dx, dy) == false)
        continue;
      if (grid[dx][dy] && visited[dx][dy] == false) {
        count += dfs(grid, dx, dy);
      }
    }
    return count; 
  }
  
  int dfs(vector<vector<int>>& grid, int i, int j) {
    // Check all error conditions 
    // 1. Check if off the size
    if (i < 0 || i == grid.size() || j < 0 || j == grid[0].size())
      return 0;
    // 2. Check if grid is not set
    if (grid[i][j] != 1)
      return 0;
    // 3. Check if already visited
    if (visited[i][j])
      return 0;

    // Mark visited first
    visited[i][j] = true;

    // try all 4 paths
    return 1 +
           dfs(grid, i + 1, j) + dfs(grid, i - 1, j) +
           dfs(grid, i, j + 1) + dfs(grid, i, j - 1);
  }

public:
  int maxAreaOfIsland(vector<vector<int>>& grid) {
    r = grid.size();
    c = grid[0].size();
    
    visited.resize(r, vector<bool>(c, false));
    
    if (!r) return 0;
    int maxArea = 0;
    
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (grid[i][j] && visited[i][j] == false)
          maxArea = max(maxArea, dfs_2(grid, i, j));
      }
    }
    return maxArea;
  }
};
  
int main () {
  
  vector<vector<int>> grid = {{0,0,1,0,0,0,0,1,0,0,0,0,0},
                              {0,0,0,0,0,0,0,1,1,1,0,0,0},
                              {0,1,1,0,1,0,0,0,0,0,0,0,0},
                              {0,1,0,0,1,1,0,0,1,0,1,0,0},
                              {0,1,0,0,1,1,0,0,1,1,1,0,0},
                              {0,0,0,0,0,0,0,0,0,0,1,0,0},
                              {0,0,0,0,0,0,0,1,1,1,0,0,0},
                              {0,0,0,0,0,0,0,1,1,0,0,0,0}};
  
  class Solution sol;
  int max = sol.maxAreaOfIsland(grid);
  cout << "Max area of island:" << max << endl;
  
  return 0;
}
