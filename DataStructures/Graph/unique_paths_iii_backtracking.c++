/*
  LeetCode 980: Unique Paths III

  Problem Description:
  You are given an m x n integer array grid where grid[i][j] could 
  be:
  - 1 representing the starting square. There is exactly one 
    starting square.
  - 2 representing the ending square. There is exactly one 
    ending square.
  - 0 representing empty squares we can walk over.
  - -1 representing obstacles that we cannot walk over.

  Return the number of 4-directional walks from the starting square 
  to the ending square, that walk over every non-obstacle square 
  exactly once.

  Algorithm: DFS with Backtracking
  1. Count the total number of empty squares.
  2. Perform DFS from the starting point.
  3. In each step:
     - Decrement the empty square count.
     - Mark current cell as visited.
     - If the target is reached and empty count is 0, we found a valid path.
  4. Backtrack: Unmark current cell and increment empty count.

  Complexity Analysis:
  - Time Complexity: O(3^N)
    Reason: Where N is the number of cells. At each cell, we can move in 3 
    directions (excluding the one we came from). 
  - Space Complexity: O(N)
    Reason: Recursion stack depth can reach the total number of cells.

  Comparison:
  - BFS vs DFS: BFS is typically used for shortest paths. Since this 
    problem requires visiting **every** cell, we need to explore all paths 
    to their full length, which is the definition of DFS/Backtracking.
  - Dynamic Programming with Bitmask:
    - Logic: `dp(current_cell, visited_mask)`.
    - Time Complexity: O(N * 2^N).
    - Comparison: If N is small (N <= 20), DP with bitmask can be more 
      efficient by avoiding redundant path calculations. For larger N, 
      backtracking is usually more memory-efficient.

  Brute Force comparison:
  - Generating all possible sequences of moves and checking each one.
  - Time: O(4^N).
  - Comparison: DFS with "empty cell counting" and "visited tracking" is 
    the optimized standard for Hamiltonian path problems on a grid.
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
            
    int isrc, jsrc;
    int m, n;
    int empty;
    vector<vector<bool>> visited;
    
  // Note that every emmpty cell must be covered - so count empty cells 
  // Since ALL empty cells need to be walked, we can not use shorted path => NO BFS, need DFS! 
  void findSrc (vector<vector<int>>& grid) {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 1) {
          isrc = i; jsrc = j;
        }
        if (grid[i][j] == 0)
          empty++;
      }
    }
  }
    
  int dfs (vector<vector<int>>& grid, int i, int j) {
    
    if (grid[i][j] == 2) {
      // reached destination
      if (!empty) 
        return 1; // covered all cells!
      return 0; // we reached shorter path - not covering all empty cells, return 0
    }
    int ret = 0;
    
    visited[i][j] = true;
    if (grid[i][j] == 0) 
      --empty;
    
    for (int k = 0; k < 4; k++) {
      static int rowAdj[] = { -1, 0, 0, +1 };
      static int colAdj[] = { 0, -1, +1, 0 };
      int iAdj = i + rowAdj[k];
      int jAdj = j + colAdj[k];
      if (iAdj < 0 || jAdj < 0 || iAdj >= m || jAdj >= n) 
        continue;
      if (visited[iAdj][jAdj])
        continue;
      if (grid[iAdj][jAdj] == -1) {
        visited[iAdj][jAdj] = true;
        continue;
      }
      ret += dfs(grid, iAdj, jAdj);
    }    
    // Back tracking 
    if (grid[i][j] == 0) 
      empty++;
    visited[i][j] = false; // back track
    return ret;
  }
  
public:
  int uniquePathsIII(vector<vector<int>>& grid) {
    
    m = grid.size();
    n = grid[0].size();
    findSrc(grid);
    visited.resize(m, vector <bool> (n, false));
    return dfs(grid, isrc, jsrc);
  }
};


int main () {
  class Solution sol;
  vector<vector<int>> grid = {{1,0,0,0},{0,0,0,0},{0,0,2,-1}};
  int count = sol.uniquePathsIII(grid);
  cout << "#unique paths: " << count << endl;
  return 0;
}
