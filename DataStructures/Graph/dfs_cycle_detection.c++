/*
  Problem: Finding Minimum Trio Degree (Amazon Pattern)

  Problem Description:
  You are given an undirected graph. A "Trio" is a group of 3 nodes 
  where every node is connected to the other two. The degree of a 
  node is the number of edges connected to it. 
  The "Trio Degree" is the number of edges connected to the three 
  nodes minus the edges within the trio (i.e., sum(degree(u)-2) 
  for each node u in the trio).
  Find the minimum trio degree in the graph.

  Algorithm 1: Brute Force (findCycle)
  - Iterates through all combinations of 3 nodes (i, j, k).
  - Checks if an edge exists between (i,j), (j,k), and (k,i).

  Complexity Analysis (Brute Force):
  - Time Complexity: O(V^3)
    Reason: Three nested loops from 1 to V. The edge check is O(1) using 
    an adjacency matrix or set.
  - Space Complexity: O(V + E) for adjacency structure.

  Algorithm 2: DFS Based (findCycle_dfs)
  - Uses DFS to find cycles.
  - If a cycle of length 3 is detected, calculates its score.

  Complexity Analysis (DFS):
  - Time Complexity: O(V + E) to traverse the graph, but O(V * E) or O(E^1.5) 
    to find all 3-cycles specifically.
  - Space Complexity: O(V + E).

  Brute Force comparison:
  - If the graph is dense (E ≈ V^2), O(V^3) is comparable to checking 
    all edges. 
  - For sparse graphs, O(V^3) is wasteful. A better approach is to iterate 
    over every edge (u, v) and find the intersection of neighbors(u) 
    and neighbors(v).
  - Intersection approach: O(Σ degree(u)^2) or O(E * sqrt(E)).

  Comparison:
  - The O(V^3) brute force is acceptable for the constraint V=500, but 
    the intersection-based approach is significantly faster for larger, 
    sparser graphs.
*/

#include <vector>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include <stack>

using namespace std;

/*

Amazon is trying to understand customer shopping patterns and offer items that
are regularly bought together to new customers. Each item that has been bought
together can be represented as an undirected graph where edges join often
bundled products. A group of n products is uniquely numbered from 1 of
product_nodes. A trio is defined as a group of three related products that all
connected by an edge. Trios are scored by counting the number of related
products outside of the trio, this is referred as a product sum.

Given product relation data, determine the minimum product sum for all trios of
related products in the group. If no such trio exists, return -1.

Example
products_nodes = 6
products_edges = 6
products_from = [1,2,2,3,4,5]
products_to = [2,4,5,5,5,6]
image
A graph of n = 6 products where the only trio of related products is (2, 4, 5).

The product scores based on the graph above are:
image
In the diagram above, the total product score is 1 + 0 + 2 = 3 for the trio (2, 4, 5).

Function Description

Complete the function getMinScore in the editor below.

getMinScore has the following parameter(s):

int products_nodes: the total number of products

int products_edges the total number of edges representing related products

int products_from[products_nodes]: each element is a node of one side of an edge.

int products_to[products edges]: each products_to[i] is a node connected to products_from[i]

Returns:

int: the minimum product sum for all trios of related products in the group. If no such trio exists, return -1.

Constraints

1 <= products_nodes <= 500
1 <= products_edges <= min(500, (products_nodes * (products_nodes - 1)) / 2)
1 <= products_from[i], products to[i] <= products_nodes
products_from[i] != products_to[i]

Sample Case 0

STDIN Funtion

5 6 -> products_nodes = 5 products_edges = 6
1 2 -> products_from[0] = 1 products_to[0] = 2
1 3 -> products_from[1] = 1 products_to[1] = 3
2 3 -> products_from[2] = 2 products_to[2] = 3
2 4 -> products_from[3] = 2 products_to[3] = 4
3 4 -> products_from[4] = 3 products_to[4] = 4
4 5 -> products_from[5] = 4 products_to[5] = 5

Sample Output

2

Explanation

There are two possible trios: {1,2,3} and {2,3,4}

The score for {1,2,3} is 0 + 1 + 1 = 2.

The score for {2,3,4} is 1 + 1 + 1 = 3.

Return 2.

*/

class Solution {

  unordered_map <int, unordered_set<int>> adj; // adjacency map < node_i --> set { node_a, node_b, node_c } etc >
  unordered_set <int> nodes; // set of all nodes 
  unordered_map <int, bool>  visited; // map < node_i -> visited boolean>

  int min_score;

void build_graph (int num, vector<int>& from, vector<int> & to) {
    // Build adj graph first
    for (int i = 0; i < from.size(); i++){
      int u = from[i], v = to[i];  // u -> v

      adj[u].insert(v);
      adj[v].insert(u);

      nodes.insert(u);
      nodes.insert(v);

      visited[u] = false;
      visited[v] = false;
    }

    min_score = INT_MAX;
}

public:

  // Brute force  O(n^3)
  int findCycle (int num, vector<int>& from, vector<int> & to) {

    build_graph(num, from, to);

    for (int i = 1; i <= num - 2; i++) {
      for (int j = i+1; j <= num - 1; j++) {
        for (int k = j+1; k <= num; k++) {
          
          if (adj[i].count(j) && adj[j].count(k) && adj[k].count(i)) {
            int score = adj[i].size() + adj[j].size() + adj[k].size() - 6;
            min_score = min(score, min_score);
          }
        }
      }   
    }

    return min_score == INT_MAX ? -1 : min_score;
  }

  // Time Complexity: O(V+E)  Space Complexity: O(V). 
  bool dfs_is_cycle (int node, int parent, stack <int>& stk) {

    visited[node] = true;
    stk.push(node);
    
    // for each edge e in node's adj
    for (auto e : adj[node]) {
      if (visited[e] == false) {
        if (dfs_is_cycle(e, node, stk)) 
          return true;
      } 
      if (e != parent && parent != -1)  {
        stk.push(e); // mark the duplicate
        return true; // Found cycle, visiting parent again
      }
    }
    return false;
  }

  int findCycle_dfs (int num, vector<int>& from, vector<int> & to) {


    build_graph(num, from, to);

    // DFS for each node in graph
    for (auto n : nodes) {
      if (visited[n] == false) {
        int parent = -1;
        stack <int> stk;

        if (dfs_is_cycle(n, parent, stk) == true) {

          int top = stk.top(); stk.pop();
          int cnt = 1;
          int score = adj[top].size() - 2; 
          while (!stk.empty()) {
            auto i = stk.top(); stk.pop();
            if (i == top) 
              break;
            cnt++;
            if (cnt > 3) 
              break; // count only 3 in a loop
            score += adj[i].size() - 2;
          }
          if (cnt == 3) 
            min_score = min(score, min_score);

        }
      }
    }
    return min_score == INT_MAX ? -1 : min_score;

  }

};


int main () {

  class Solution sol;
//  vector <int> from = { 1, 1, 2, 2, 3, 4};
//  vector <int> to = { 2, 3, 3, 4, 4, 5};

  int min;


  vector <int> from = { 1, 2, 2, 3, 4, 5 };
  vector <int> to = { 2, 4, 5, 5, 5, 6};

  min = sol.findCycle_dfs(6, from, to);
  cout << "DFS min product score:" << min << endl;

  min = sol.findCycle(5, from, to);
  cout << "Brute force min product score:" << min << endl;

  return 0;
}
