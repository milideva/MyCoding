/*
  LeetCode 547: Friend Circles (Number of Provinces)

  Problem Description:
  There are n cities. Some of them are connected, while some are not. 
  If city a is connected directly with city b, and city b is connected 
  directly with city c, then city a is connected indirectly with city c.

  A province is a group of directly or indirectly connected cities and 
  no other cities outside of the group.

  You are given an n x n matrix isConnected where isConnected[i][j] = 1 
  if the ith city and the jth city are directly connected, and 
  isConnected[i][j] = 0 otherwise.

  Return the total number of provinces.

  Algorithm: DFS on Adjacency Matrix
  1. The input is an N*N adjacency matrix.
  2. We treat each student as a node in a graph. An edge exists if M[i][j] == 1.
  3. We iterate through each student. If a student hasn't been visited, 
     it marks the start of a new "circle" (connected component).
  4. Perform DFS from that student to mark all reachable friends as visited.

  Complexity Analysis:
  - Time Complexity: O(N^2)
    Reason: We visit every cell in the N*N matrix exactly once to check 
    for friendships. Even though we track 'visited' students, the nested 
    loop inside `dfs` always scans N potential friends.
  - Space Complexity: O(N)
    Reason: The `visited` vector of size N and the recursion stack which 
    can reach depth N in a skewed friendship chain.

  Alternative Approaches:
  - BFS: Same logic as DFS but using a queue.
    - Time: O(N^2), Space: O(N).
  - Union-Find (DSU): Iterate through the matrix and `union(i, j)` if they are 
    friends. Count the number of disjoint sets at the end.
    - Time: O(N^2 * α(N)).
    - Comparison: DFS is slightly faster in practice as it avoids the DSU 
      overhead, though both are effectively O(N^2).

  Brute Force comparison:
  - For every student, calculate the set of all reachable friends. Use set 
    unions to merge circles. 
  - This involves significantly more memory and overhead than a simple 
    DFS with a boolean visited array.
*/

#include <vector>
#include <iostream>
using namespace std;

class Solution {

  vector <bool> visited; // 1-D is enough, one bool per student
  
  void dfs (vector<vector<int>>& M, int i) {
    // Mark node as visited
    visited[i] = true;
    
    // For all edges (other friends) 
    for (int j = 0; j < M[i].size(); j++) {
      // If node is a friend and if not visited yet
      if (M[i][j] && visited[j] == false) {
        dfs(M, j);
      }
    }
  }
    
public:
  int findCircleNum (vector <vector<int>>& M) {
    int n = M.size();
    if (!n) return 0;
    
    // Mark all visited as false
    visited.resize(n, false); // dynamic size + init to false

    int count = 0;

    // For each node (each student)
    for (int i = 0; i < n; i++) {
      if (visited[i] == false) {
        // If not visited, pay a visit
        dfs(M, i);
        count++;
      }            
    }
    return count;
  }
};

int main() {

  vector <vector <int>> mat =
    {
      { 1, 0, 0, 1, 0, 0, 0 },
      { 0, 1, 1, 0, 0, 0, 0 },
      { 0, 1, 1, 0, 0, 0, 1 },
      { 1, 0, 0, 1, 1, 0, 1 },
      { 0, 0, 0, 1, 1, 0, 0 },
      { 0, 0, 0, 0, 0, 1, 0 },
      { 0, 0, 1, 1, 0, 0, 1 }
    };

  class Solution sol;
  unsigned dist = sol.findCircleNum(mat);
  
  cout << "#Friend circles : " << dist << endl;
  
  return 0;
}
