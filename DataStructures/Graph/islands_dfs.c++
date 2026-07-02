/*

  200. Number of Islands

Given an m x n 2D binary grid grid which represents a map of '1's
(land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent
lands horizontally or vertically. You may assume all four edges of the
grid are all surrounded by water.

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
 
Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.

Time: O(mn)
Space: O(mn)

*/

#include <vector>
#include <iostream>

using namespace std;

bool is_safe (vector<vector<char>>& grid, int i, int j) {
  int m = grid.size();
  int n = grid[0].size();
  if (i < 0 || j < 0) return false;
  if (i >= m || j >= n) return false;
  return true;
}
    
bool can_visit (vector<vector<char>>& grid, vector<vector<bool>>& visited, int row, int col) {
  if (is_safe(grid, row, col) == false) {
    return false;
  }
  if (grid[row][col] != '1') {
    return false;
  }
  if (visited[row][col] == true) {
    return false;
  }
  return true;
}

void count_islands_dfs (vector<vector<char>>& grid, 
                        vector<vector<bool>>& visited, int i, int j) {
  // These arrays help to get row and column numbers of 4 neighbors of a given cell
  static int row_adj[] = {-1, 0, 0, 1};
  static int col_adj[] = {0, -1, 1, 0};
  
  // We mark this node as visited and run dfs on its edges
  visited[i][j] = true;
  
  for (int k = 0; k < 4; k++) {
    int row = i + row_adj[k];
    int col = j + col_adj[k];

    // Recur for all connected neighbours
    if (can_visit(grid, visited, row, col)) {
      count_islands_dfs(grid, visited, row, col);
    }
  }
}

int numIslands (vector<vector<char>>& grid) {
  int m = grid.size();
  if (!m) return 0;
  int n = grid[0].size();
  vector<vector<bool>> visited(m, vector<bool> (n, false));
  
  
  int count = 0;
  
  for (int i = 0; i < m; i++ ) {
    for (int j = 0; j < n; j++ ) {
      // If a cell with value '1' is not yet visited, then new island found.
      // Visit all cells in this island and increment island count.
      if (grid[i][j] == '1' && visited[i][j] == false) {
        count_islands_dfs(grid, visited, i, j);
        count++;
      }
    }
  }
  
  return count;
}

int main () {

  vector<vector<char>> myvect = { { '1', '1', '1', '1', '0'}, 
                                 { '1', '1', '0', '1', '0'}, 
                                 { '1', '1', '0', '0', '0'},
                                 { '0', '0', '0', '1', '0'},
  };

  int count = numIslands(myvect);
  cout << "Num islands " << count << endl;
  return 0;
}
