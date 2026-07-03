/*
  Problem: Shortest Path in a Maze

  Algorithm: Breadth-First Search (BFS)
  1. Use a queue to store the current cell coordinates and its distance 
     from the source.
  2. Starting from the source, visit all 4-directional neighbors.
  3. Mark visited cells to avoid cycles and redundant work.
  4. The first time the destination is reached, the current distance 
     is guaranteed to be the shortest path.

  Complexity Analysis:
  - Time Complexity: O(M * N)
    Reason: In the worst case, we may visit every cell in the M*N matrix.
  - Space Complexity: O(M * N)
    Reason: To store the `visited` matrix and the BFS queue.

  Alternative Approaches:
  - Depth-First Search (DFS): 
    - Logic: Explore all paths from source to destination and keep 
      track of the minimum length found.
    - Time Complexity: O(4^(M*N)) - Exponential.
    - Comparison: DFS is highly inefficient for shortest paths as it must 
      exhaustively search all possible paths. BFS stops as soon as the 
      target is found.
  - Dijkstra's Algorithm:
    - Logic: Generalization of BFS for weighted graphs.
    - Time: O(E log V).
    - Comparison: Since all edge weights are 1 in this maze, standard BFS 
      is more efficient as it avoids the priority queue overhead.

  Brute Force comparison:
  - Recursive backtracking without pruning or visited tracking would 
    result in infinite recursion or astronomical time complexity. 
    BFS provides the optimal O(MN) solution.
*/

#include <iostream>
#include <queue>
#include <climits>
#include <cstring>
using namespace std;

// g++ -std=c++14 shortest_path_bfs.cpp

#define ROWS 10
#define COLS 10

typedef struct node_ {
    int i, j;
    unsigned int dist;
} node_t;

static bool check_valid (int i, int j, int arr[][COLS], vector <vector <bool>>& visited) {

    return i >= 0 && i < ROWS && j >= 0 && j < COLS && arr[i][j] && !visited[i][j];
}

unsigned int BFS (int arr[] [COLS], int rows, int cols, int isrc, int jsrc, int idst, int jdst) {

    vector <vector <bool>> visited;
    visited.resize(rows, vector<bool> (cols, false));

    queue <node_t> q;

    visited[isrc][jsrc] = true;

    q.push( { isrc, jsrc, 0 });

    while (!q.empty()) {
        node_t curr = q.front(); q.pop();
        // Found it, terminating condition
        if (curr.i == idst && curr.j == jdst) {
            return curr.dist;
        }

        // Check each neighbor
        for (int k = 0; k < 4; k++) {
            static int rowAdj[] = { -1, 0, 0, +1 };
            static int colAdj[] = { 0, -1, +1, 0 };
            int iAdj = curr.i + rowAdj[k];
            int jAdj = curr.j + colAdj[k];
            bool is_valid = check_valid(iAdj, jAdj, arr, visited);

            if (is_valid) {
                visited[iAdj][jAdj] = true;
                q.push( { iAdj, jAdj, curr.dist + 1 } );
            }
        }
    }

    return 0;
}


int main() {
  // input maze
  int mat[ROWS][COLS] =
    {
      { 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
      { 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
      { 0, 0, 1, 0, 1, 1, 1, 0, 0, 1 },
      { 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
      { 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
      { 1, 0, 1, 1, 1, 0, 0, 1, 1, 0 },
      { 0, 0, 0, 0, 1, 0, 0, 1, 0, 1 },
      { 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
      { 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
      { 0, 0, 1, 0, 0, 1, 1, 0, 0, 1 },
    };
  
  // Find shortest path from source (7, 3) to
  // destination (7, 5)
  unsigned dist = BFS(mat, ROWS, COLS, 7, 3, 7, 5);
  cout << "Distance : " << dist << endl;
  
  return 0;
}

