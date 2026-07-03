/*
  LeetCode 200: Number of Islands

  Algorithm: DFS (Flood Fill)
  1. Iterate through the grid.
  2. When a '1' (land) is found, start a DFS to visit all connected '1's.
  3. Mark all visited '1's in a `visited` matrix (or flip them to '0' in-place 
     to save space).
  4. Each DFS start represents one unique island.

  Complexity Analysis:
  - Time Complexity: O(M * N)
    Reason: Every cell in the grid is visited exactly once.
  - Space Complexity: O(M * N)
    Reason: The `visited` matrix of size M*N. The recursion stack can also 
    reach O(M * N) in the worst case (e.g., a grid full of '1's).

  Alternative Approaches:
  - In-place DFS: Modify the input `grid` by changing visited '1's to '0's. 
    This reduces auxiliary space to O(H) for the stack.
  - BFS: Use a queue to process islands level by level. 
    - Space Complexity: O(min(M, N)) for the queue.
  - Union-Find (DSU): Iterate through the grid and `union` adjacent '1' cells. 
    Count the number of disjoint sets.
    - Time: O(M * N * α(M*N)).
    - Comparison: DSU is useful if the grid is being updated dynamically 
      (e.g., land being added).

  Brute Force Approach:
  - For every cell, check if it belongs to any previously identified island 
    by re-traversing all discovered islands.
  - Time Complexity: O((M*N)^2).
  - Comparison: Flood fill (DFS/BFS) is significantly more efficient as it 
    uses a 'visited' state to ensure linear time.
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
