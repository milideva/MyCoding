/*

63. Unique Paths II

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the
diagram below).

The robot can only move either down or right at any point in time. The robot is
trying to reach the bottom-right corner of the grid (marked 'Finish' in the
diagram below).

Now consider if some obstacles are added to the grids. How many unique paths
would there be?

An obstacle and space is marked as 1 and 0 respectively in the grid.


Example 1:

Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right

Example 2:

Input: obstacleGrid = [[0,1],[0,0]]
Output: 1

*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int r = obstacleGrid.size();
        int c = obstacleGrid[0].size();

        if (obstacleGrid[0][0] == 1 || obstacleGrid[r-1][c-1] == 1) return 0;

        vector <vector <int> > gridSum(r, vector<int>(c, 0));

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                // 1. If there's an obstacle, it's unreachable (0)
                if (obstacleGrid[i][j] == 1) {
                    gridSum[i][j] = 0;
                    continue;
                }
                // 2. Base case: The start
                if (i == 0 && j == 0) {
                    gridSum[i][j] = 1;
                    continue;
                }
                // 3. First row: depends on the cell to the left
                if (i == 0) {
                    gridSum[i][j] = gridSum[i][j- 1];
                    continue;
                }
                // 4. First column: depends on the cell above
                if (j == 0) { 
                    gridSum[i][j] = gridSum[i-1][j];
                    continue;
                }
                // 5. Middle cells: sum of top and left
                gridSum[i][j] = gridSum[i - 1][j] + gridSum[i][j - 1];
            }
        }
        return gridSum[r-1][c-1];
    }   

};


int main () {
  class Solution sol;
  int count;
  vector <vector <int>> grid = { {0,0,0}, {0,1,0}, {0,0,0} };
  count = sol.uniquePathsWithObstacles(grid);
  cout << "#Unique paths: " << count << endl;

  return 0;
}
