/*
  LeetCode 1730: Shortest Path to Get Food

  Problem Description:
  You are starving and you want to eat food as quickly as possible. 
  You want to find the shortest path to arrive at any food cell.
  You are given an m x n character matrix, grid, of these different 
  types of cells:
  - '*' is your location. There is exactly one '*' cell.
  - '#' is a food cell. There may be multiple food cells.
  - 'O' is free space, and you can travel through these cells.
  - 'X' is an obstacle, and you cannot travel through these cells.
  You can travel to any adjacent cell north, east, south, or west 
  of your current location if there is not an obstacle.

  Return the length of the shortest path for you to reach any food 
  cell. If there is no path for you to reach food, return -1.

  Algorithm: Multi-target Breadth-First Search (BFS)
  1. Find the starting position (*).
  2. Perform BFS to find the nearest food cell (#).
  3. BFS naturally finds the shortest path level by level.

  Complexity Analysis:
  - Time Complexity: O(M * N)
    Reason: We visit every cell at most once.
  - Space Complexity: O(M * N)
    Reason: `visited` matrix and BFS queue.

  Comparison:
  - Multi-source BFS: If there were multiple starting positions and one 
    food source, we could add all start positions to the queue. Here, 
    we have one start and multiple targets, which standard BFS handles 
    by returning on the first '#' encountered.
  - DFS: Unsuitable for shortest path as it doesn't guarantee finding the 
    minimum steps without visiting every possible path.

  Brute Force comparison:
  - Naive recursion without memoization would take exponential time. 
    The BFS approach is the standard optimal linear-time solution.
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
    int mr, mc; // max 
    int r, c; // my location 
    int nx[4] = { 0, 0, -1, +1}; // neighbor x
    int ny[4] = { +1, -1, 0, 0}; // neighbor y 

public:
    int getFood(vector<vector<char>>& grid) {
        mr = grid.size();
        mc = grid[0].size();
        r = c = -1;
        for (int i = 0; i < mr; i++) {
            for (int j = 0; j < mc; j++) {
                if (grid[i][j] == '*') {
                    r = i;
                    c = j;
                }
            }
        }
        struct path {
            int i, j, d;
        };

        vector<vector<bool>> visited(mr, vector<bool>(mc, false));

        queue <path> q;
        q.push({r, c, 0});
        visited[r][c] = true; // mark starting node as visited

        while (!q.empty()) {
            auto [ix, jy, d] = q.front(); q.pop();
    
            for (int k = 0; k < 4; k++) {
                int i = ix + nx[k];
                int j = jy + ny[k];
                if (i < 0 or i >= mr or j < 0 or j >= mc) {
                    continue;
                }
                if (visited[i][j] == true) 
                    continue;
                visited[i][j] = true;
                if (grid[i][j] == '#') {
                    return d + 1; // found the food
                }
                if (grid[i][j] == 'X') {
                    continue;
                }
                if (grid[i][j] == 'O') {
                    q.push({i, j, d + 1});
                }
            }
        }
        return -1;
    }
};

// Separate test function to improve readability and maintainability
void test_getFood() {
  // Test case 1: Expected output 3
  vector<vector<char>> grid1 = {
      {'X', 'X', 'X', 'X', 'X', 'X'},
      {'X', '*', 'O', 'O', 'O', 'X'},
      {'X', 'O', 'O', '#', 'O', 'X'},
      {'X', 'X', 'X', 'X', 'X', 'X'}};
  int expected1 = 3;
  int actual1 = Solution().getFood(grid1);
  if (actual1 == expected1) {
    std::cout << "Test 1 Passed!" << std::endl;
  } else {
    std::cout << "Test 1 Failed. Expected: " << expected1 << ", Actual: " << actual1 << std::endl;
  }

  // Test case 2: Expected output -1 (no reachable food)
  vector<vector<char>> grid2 = {
      {'X', 'X', 'X'},
      {'X', '*', 'X'},
      {'X', 'X', 'X'}};
  int expected2 = -1;
  int actual2 = Solution().getFood(grid2);
  if (actual2 == expected2) {
    std::cout << "Test 2 Passed!" << std::endl;
  } else {
    std::cout << "Test 2 Failed. Expected: " << expected2 << ", Actual: " << actual2 << std::endl;
  }

  // Test case 3: Expected output -1 (food unreachable due to obstacle)
  vector<vector<char>> grid3 = {
      {'X', 'X', 'X', 'X', 'X'},
      {'X', '*', 'X', 'O', 'X'},
      {'X', 'O', 'X', '#', 'X'},
      {'X', 'X', 'X', 'X', 'X'}};
  int expected3 = -1;
  int actual3 = Solution().getFood(grid3);
  if (actual3 == expected3) {
    std::cout << "Test 3 Passed!" << std::endl;
  } else {
    std::cout << "Test 3 Failed. Expected: " << expected3 << ", Actual: " << actual3 << std::endl;
  }

  // Test case 4: Expected output 6 (multiple food cells, reach bottom one)
  vector<vector<char>> grid4 = {
      {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
      {'X', '*', 'O', 'X', 'O', '#', 'O', 'X'},
      {'X', 'O', 'O', 'X', 'O', 'O', 'X', 'X'},
      {'X', 'O', 'O', 'O', 'O', '#', 'O', 'X'},
      {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'}};
  int expected4 = 6;
  int actual4 = Solution().getFood(grid4);
  if (actual4 == expected4) {
    std::cout << "Test 4 Passed!" << std::endl;
  } else {
    std::cout << "Test 4 Failed. Expected: " << expected4 << ", Actual: " << actual4 << std::endl;
  }

  // Add more test cases here...
}

int main() {
  test_getFood();
  return 0;
}