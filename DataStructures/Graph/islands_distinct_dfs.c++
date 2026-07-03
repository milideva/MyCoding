/*
  LeetCode 694: Number of Distinct Islands

  Problem: Count the number of islands with unique shapes. Translation-only 
  equivalence (no rotation/reflection).

  Algorithm 1: Direction-String Serialization (numDistinctIslands)
  - During DFS, record the direction taken ('u', 'd', 'l', 'r') and a marker 
    'n' when a path cannot proceed.
  - The resulting string uniquely represents the "path" taken, which 
    corresponds to the island's shape.
  - Store strings in a hash set to count unique shapes.

  Algorithm 2: Relative Coordinates (numDistinctIslands_2)
  - During DFS, record the coordinates of each cell relative to the 
    island's starting cell (i - i0, j - j0).
  - Store the set of relative coordinates in a `set<vector<pair<int, int>>>`.

  Complexity Analysis:
  - Time Complexity: O(M * N)
    Reason: Every cell is visited once. Set/Map operations on shapes take 
    time proportional to the number of cells in the island.
  - Space Complexity: O(M * N)
    Reason: To store the visited matrix and the shapes in the set.

  Comparison:
  - Direction Strings: Elegant and easy to implement. However, you MUST 
    include a "null/backtrack" marker (like 'n') to distinguish shapes 
    properly (e.g., 'rd' vs 'r' then 'd').
  - Relative Coordinates: More robust and avoids the need for special 
    markers. It represents the shape as a point cloud.

  Brute Force Approach:
  - For every pair of islands, perform a coordinate-wise comparison to 
    see if one can be translated to the other.
  - Time Complexity: O((Number of Islands)^2 * Avg Island Size).
  - Comparison: Hashing shapes (via strings or coordinate lists) is much 
    faster as it reduces comparisons to set lookups.
*/

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <unordered_map> 
#include <set>

using namespace std;

/*
694. Number of Distinct Islands

Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's
(representing land) connected 4-directionally (horizontal or vertical.) You may
assume all four edges of the grid are surrounded by water.

Count the number of distinct islands. An island is considered to be the same as
another if and only if one island can be translated (and not rotated or
reflected) to equal the other.

Example 1:
11000
11000
00011
00011

Given the above grid map, return 1.

Example 2:
11011
10000
00001
11011

Given the above grid map, return 3.

Notice that:
11
1
and
 1
11
are considered different island shapes, because we do not consider reflection / rotation.
Note: The length of each dimension in the given grid does not exceed 50.

*/

void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int i, int j, string& route) {
  visited[i][j] = true;
  
  if (i - 1 >= 0 && grid[i - 1][j] && !visited[i - 1][j]) {
    route.push_back('u');
    dfs(grid, visited, i - 1, j, route);
  } else {
    route.push_back('n');
  }
  
  if (i + 1 < grid.size() && grid[i + 1][j] && !visited[i + 1][j]) {
    route.push_back('d');
    dfs(grid, visited, i + 1, j, route);
  } else {
    route.push_back('n');
  }
  
  if (j - 1 >= 0 && grid[i][j - 1] && !visited[i][j - 1]) {
    route.push_back('l');
    dfs(grid, visited, i, j - 1, route);
  } else {
    route.push_back('n');
  }
  
  if (j + 1 < grid[0].size() && grid[i][j + 1] && !visited[i][j + 1]) {
    route.push_back('r');
    dfs(grid, visited, i, j + 1, route);
  } else {
    route.push_back('n');
  }
}

void print_routes(unordered_map<string, int>& routes) {
  for (auto [r, c] : routes) {
    cout << "route: " << r << " count:" << c << endl;
  }
}

int numDistinctIslands(vector<vector<int>>& grid) {
  if (grid.size() == 0 || grid[0].size() == 0) return 0;
  
  int rows = grid.size();
  int cols = grid[0].size();
  vector<vector<bool>> visited(rows, vector<bool>(cols, false)); // Initialize visited array
  
  unordered_map<string, int> routes;
  
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (grid[i][j] && !visited[i][j]) {
        string route = "";
        dfs(grid, visited, i, j, route);
        routes[route]++;
      }
    }
  }
  
  //print_routes(routes);
  return routes.size();
}

// i0 and j0 are starting point co-ordinates which never change
void dfs_2 (vector<vector<int>>& grid, vector<vector<bool>>& visited, 
            vector <pair <int, int>>& route,
            int i, int j, int i0, int j0) {
  if (i < 0 or i >= grid.size() or j < 0 or j >= grid[0].size())
    return;
  if (visited[i][j] == true)
    return;
  if (grid[i][j] != 1)
    return;

  visited[i][j] = true;

  // save the route wrt initial starting point, which never changes.
  route.push_back({i - i0, j - j0});

  dfs_2(grid, visited, route, i - 1, j, i0, j0);
  dfs_2(grid, visited, route, i + 1, j, i0, j0);
  dfs_2(grid, visited, route, i, j - 1, i0, j0);
  dfs_2(grid, visited, route, i, j + 1, i0, j0);
            
}

int numDistinctIslands_2 (vector<vector<int>>& grid) {
  int r = grid.size();
  int c = grid[0].size();

  vector <vector <bool>> visited(r, vector<bool> (c));

  set <vector <pair <int, int>>> routes;

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      vector <pair <int, int>> route;
      if (grid[i][j] && visited[i][j] == false) {
        dfs_2(grid, visited, route, i, j, i, j);
        routes.insert(route);
      }
    }
  }
  return routes.size();
}

void test (vector<vector<int>> &grid) {
  cout << "Method1: Num islands " << numDistinctIslands(grid) << endl;
  cout << "Method2 : Num islands " << numDistinctIslands_2(grid) << endl;
}

int main () {

  vector<vector<int>> grid = {{1, 1, 0, 0, 0},
                             {1, 1, 0, 0, 0},
                             {0, 0, 0, 1, 1},
                             {0, 0, 0, 1, 1}};
  test(grid);

  grid = { { 1, 1, 1, 1, 0}, 
            { 1, 1, 0, 1, 0}, 
            { 1, 1, 0, 0, 0},
            { 0, 0, 0, 0, 0},
  };
  test(grid);

  grid = {
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
  };
  test(grid); // Expected: 1

  grid = {
    {1, 1, 0, 0},
    {0, 1, 0, 1},
    {1, 0, 1, 0},
    {0, 0, 0, 1}
  };
  test(grid); // Expected: 2

  return 0;
}
