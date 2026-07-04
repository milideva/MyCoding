#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 885: Spiral Matrix III

  Problem Description:
  You start at `(rStart, cStart)` on an `rows x cols` grid facing east. 
  You walk in a clockwise spiral shape to visit every position in 
  this grid. Whenever you move outside the grid, you continue your 
  walk outside but eventually return. Return the coordinates in the 
  order they were visited.

  Example 1:
  Input: rows = 1, cols = 4, rStart = 0, cStart = 0
  Output: [[0,0],[0,1],[0,2],[0,3]]

  Algorithm: Layered Simulation
  1. The spiral pattern for steps in each direction is: 1, 1, 2, 2, 3, 3, 4, 4...
     (1 East, 1 South, 2 West, 2 North, 3 East...)
  2. Maintain `(r, c)` coordinates and a `step` size.
  3. Every two directions, increment the `step` size.
  4. Direction order: East (0,1), South (1,0), West (0,-1), North (-1,0).
  5. For each step in a direction:
     - Update `(r, c)`.
     - If `(r, c)` is within grid boundaries, add to result.
  6. Stop when the result contains `rows * cols` coordinates.

  Complexity Analysis:
  - Time Complexity: O(max(R, C)^2)
    Reason: We visit all cells in the grid, but also walk outside the 
    grid. The total steps walked is roughly the square of the larger 
    dimension.
  - Space Complexity: O(1) auxiliary space (excluding result).

  Brute Force comparison:
  - N/A. Simulation is the most direct way to generate the spiral path.
*/

class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        vector<vector<int>> result;
        int dr[] = {0, 1, 0, -1};
        int dc[] = {1, 0, -1, 0};
        int r = rStart, c = cStart;
        int dir = 0; // East
        int steps = 1;
        
        result.push_back({r, c});
        
        while (result.size() < rows * cols) {
            // Two directions per step size increase
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < steps; ++j) {
                    r += dr[dir];
                    c += dc[dir];
                    if (r >= 0 && r < rows && c >= 0 && c < cols) {
                        result.push_back({r, c});
                    }
                }
                dir = (dir + 1) % 4; // Turn clockwise
            }
            steps++; // Increase step size
        }
        return result;
    }
};

void test(const string& label, int rows, int cols, int rStart, int cStart) {
    cout << "Testing: " << label << endl;
    Solution sol;
    vector<vector<int>> result = sol.spiralMatrixIII(rows, cols, rStart, cStart);
    cout << "  Path size: " << result.size() << " Result: [ ";
    for (const auto& v : result) cout << "[" << v[0] << "," << v[1] << "] ";
    cout << "]" << endl;
}

int main() {
    test("Example 1", 1, 4, 0, 0);
    test("Example 2", 5, 6, 1, 4);
    return 0;
}
