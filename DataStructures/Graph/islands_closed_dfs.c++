/*
  LeetCode 1254: Number of Closed Islands

  Problem: Count islands that are completely surrounded by water (1s) and 
  do not touch the grid boundaries.

  Algorithm: DFS with Boundary Check
  1. Iterate through the grid. When an unvisited land (0) is found, start a DFS.
  2. During DFS, mark nodes as visited.
  3. If the DFS reaches any cell on the grid boundary (row 0, col 0, etc.), 
     mark a flag to indicate this island is "open" (not closed).
  4. Only increment the count if the DFS completes without touching a boundary.

  Complexity Analysis:
  - Time Complexity: O(M * N)
    Reason: We visit every cell in the M*N grid at most once.
  - Space Complexity: O(M * N)
    Reason: In the worst case (all land), the recursion stack and the 
    `visited` matrix both take O(M * N) space.

  Alternative Approaches:
  - Boundary-Flood Fill (Pre-processing): 
    1. Perform DFS from all land cells on the edges to mark them and their 
       connected neighbors as "water" or "invalid".
    2. Perform a standard "Number of Islands" count on the remaining grid.
    - Comparison: This is often cleaner to implement and ensures edge 
      cases are handled before the main logic runs.
  - BFS: Use a queue instead of recursion.
    - Time: O(M * N), Space: O(min(M, N)) for the queue on average.

  Brute Force comparison:
  - For every land cell, perform a search to see if it can reach the boundary. 
    Without marking visited cells, this would be highly redundant and 
    take O((M*N)^2) time. Marking visited ensures each component is 
    processed once.
*/

#include <vector>

#include <iostream>

using namespace std;

class Solution {
    int rows, cols;
    vector <vector <bool>> visited;
    
    int x[4] = {-1,0,1,0};
    int y[4] = {0,1,0,-1};
    
    void dfs (int i, int j, vector<vector<int>>& grid, bool &flag) { 
        // First mark the node visited.     
        visited[i][j] = true;

        // A closed island, needs to be completely surrounded by water.
        if (i == 0 or j == 0 or i == rows-1 or j == cols-1) {
            flag = true; // // not a closed island
            return;
        }
        for (int k = 0; k < 4; k++) {
            int xn = x[k] + i;
            int yn = y[k] + j;
            if (xn >= 0 and xn < rows and yn >= 0 and yn < cols) {
                if (grid[xn][yn] == 0 && visited[xn][yn] == false) {
                    dfs(xn, yn, grid, flag);
                }
            }
        }
    }
public:
    int closedIsland(vector<vector<int>>& grid) {
        rows = grid.size();
        if (!rows) return 0;
        cols = grid[0].size();
        int count = 0;
        
        visited.resize(rows, vector<bool> (cols, false));
        
        // Skip edges for closed islands by starting with 1 instead of 0
        // and ending with < rows-1 instead of < rows
        for (int i = 1; i < rows-1; i++) {
            for (int j = 1; j < cols-1; j++) {
                if (grid[i][j] == 0 && visited[i][j] == false) {
                    bool flag = false;
                    dfs(i, j, grid, flag);
                    if (flag == true) {
                        // skip counting it
                    } else {
                        count++;
                    }
                }
            }
        }
        return count;
    }
};


int main (void) {

  vector<vector<int>> myvect = { { 1, 1, 1, 1, 0}, 
                                 { 1, 0, 1, 0, 1}, 
                                 { 1, 1, 0, 1, 0},
                                 { 0, 1, 0, 0, 0},
  };

  Solution sol;
  int count = sol.closedIsland(myvect);
  cout << "Num closeed islands " << count << endl;

  return 0;
}
