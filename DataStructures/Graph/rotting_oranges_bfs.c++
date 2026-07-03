/*
  LeetCode 994: Rotting Oranges

  Algorithm: Multi-source Breadth-First Search (BFS)
  1. Identify all rotten oranges (2) and add them to a queue. Count total 
     fresh oranges (1).
  2. Perform BFS. In each step (minute), all rotten oranges spread rot to 
     their fresh neighbors simultaneously.
  3. Decrement the fresh orange count as they rot.
  4. The number of levels in the BFS represents the minutes elapsed.

  Complexity Analysis:
  - Time Complexity: O(M * N)
    Reason: Every cell is scanned once at the start, and every orange 
    is enqueued and dequeued at most once.
  - Space Complexity: O(M * N)
    Reason: The queue can store up to O(M * N) oranges in the worst case.

  Alternative Approaches:
  - Brute Force (Repeated Scans): Every minute, scan the entire grid to 
    find oranges that should rot.
    - Time Complexity: O((M * N)^2).
    - Comparison: BFS is far superior as it only processes the "frontier" 
      of the infection.

  Comparison:
  - BFS vs DFS: DFS is unsuitable for this problem because we need the 
    **minimum** time for **all** sources to spread. DFS would find 
    the time for one branch, but wouldn't easily handle the simultaneous 
    nature of the spreading. BFS naturally simulates time steps.
*/

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

/*
  Time : O(m * n)
  Space : O(m * n)
*/

class Solution {
public:
  int orangesRotting(vector<vector<int>>& grid) {
    const int m = grid.size();
    const int n = grid[0].size();
    int ans = 0;
    int countFresh = 0;
    queue<pair<int, int>> q;

    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j)
        if (grid[i][j] == 1)
          ++countFresh;
        else if (grid[i][j] == 2)
          q.emplace(i, j);

    if (countFresh == 0)
      return 0;

    constexpr int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (!q.empty()) {
      ++ans;
      for (int sz = q.size(); sz > 0; --sz) {
        const auto [i, j] = q.front();
        q.pop();
        for (const auto& [dx, dy] : dirs) {
          const int x = i + dx;
          const int y = j + dy;
          if (x < 0 || x == m || y < 0 || y == n)
            continue;
          if (grid[x][y] != 1)
            continue;
          grid[x][y] = 2;   // Mark grid[x][y] as rotten.
          q.emplace(x, y);  // Push the newly rotten orange to the queue.
          --countFresh;     // Decrease the count of fresh oranges by 1.
        }
      }
    }

    return countFresh == 0 ? ans - 1 : -1;
  }
};


int main () {
  
  class Solution sol;

  vector <vector <int>> grid = {{2,1,1},{1,1,0},{0,1,1}};
  int min = sol.orangesRotting(grid);

  cout << "Minutes :" << min  << endl;

  return 0;
}
