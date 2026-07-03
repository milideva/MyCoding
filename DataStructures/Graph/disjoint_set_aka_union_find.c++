#include <iostream>
#include <stdlib.h>

using namespace std;

/*
  Problem: Disjoint Set Union (DSU) / Union-Find

  Problem Description:
  Implement a Disjoint Set Union (DSU) data structure that supports 
  `find` and `union` operations. This structure is used to manage 
  a partition of a set into disjoint subsets and to efficiently 
  determine connectivity.

  Algorithm: Union-Find with Path Compression
  1. `find(x)`: Recursively finds the representative of the set containing x. 
     Path compression flattens the tree structure by making every node in 
     the path point directly to the root.
  2. `union(x, y)`: Merges two sets. (Note: The current implementation uses 
     simple union; Union by Rank/Size would further optimize it).

  Complexity Analysis:
  - Time Complexity: O(E * log V) or O(E * α(V))
    Reason: With path compression alone, find/union take O(log V) on average. 
    With both Path Compression and Union by Rank, the time per operation 
    becomes nearly constant O(α(V)), where α is the inverse Ackermann function.
  - Space Complexity: O(V)
    Reason: To store the `parent` array of size V.

  Alternative Approaches:
  - DFS/BFS for Connectivity: To check if two nodes are connected, perform 
    a traversal.
    - Time: O(V + E) per check.
    - Comparison: DSU is much faster for multiple dynamic connectivity 
      queries as it maintains the structure incrementally.

  Brute Force comparison:
  - For every query (u, v), run a full DFS from u to see if v is reachable. 
    For Q queries, this is O(Q * (V + E)). 
  - Union-Find reduces this significantly, making it the preferred 
    choice for Kruskal's algorithm and dynamic connectivity.
*/

struct edge {
  int src, dest;
};

struct graph {
  int v, e;
  struct edge *edge;
};

struct graph * create_graph (int v, int e) {
  struct graph *g = (struct graph *) calloc(1, sizeof *g);
  if (!g) return g;
  g->v = v;
  g->e = e;
  g->edge = (struct edge *) calloc(1, e * sizeof *g->edge);
  if (!g->edge) {
    free(g);
    return nullptr;
  }
  return g;
}

// Find returns the representative of the set that contains i
// if (find(a) == find(b)) -> they are in the same set 
// else they're in disjoint sets.
// Find if x and y are connected - check find(x) == ? find (y)
// O(n)
#if 0
int g_find (int parent[], int i) {
  if (parent[i] == -1) return i;
  return g_find(parent, parent[i]);
}
#endif 

// O(log n) aka path compression 
int g_find (int parent[], int i) {
  if (parent[i] == -1) return i;
  int x = g_find(parent, parent[i]);
  parent[i] = x;
  return x;
}
// Merges a set that contains x with a set that contains y
// Needs optimization of Union by Rank (attach shorter tree to the root of taller tree
void g_union (int parent[], int x, int y) {
  parent[x] = y;
/*
  int rank = abs(g_find(y));
  rank = -1 * (rank+1);
  parent[y] = rank;
*/
}

bool is_cycle (struct graph* graph) {

  int parent[graph->v];
  memset(parent, -1, sizeof(int) * graph->v);
 
    // Iterate through all edges of graph, find subset of
    // both vertices of every edge, if both subsets are
    // same, then there is cycle in graph.
    for (int i = 0; i < graph->e; ++i) {
        int x = g_find(parent, graph->edge[i].src);
        int y = g_find(parent, graph->edge[i].dest);
 
        if (x == y)
            return true;
 
        g_union(parent, x, y);
    }
    return false;
}

void driver (void) {
    /* Let us create the following graph
        0
        | \
        |  \
        1---2 */
    int V = 3, E = 3;
    struct graph* graph = create_graph(V, E);
 
    // add edge 0-1
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
 
    // add edge 1-2
    graph->edge[1].src = 1;
    graph->edge[1].dest = 2;
 
    // add edge 0-2
    graph->edge[2].src = 0;
    graph->edge[2].dest = 2;
 
    if (is_cycle(graph))
        cout << "This graph contains a cycle!" << endl;
    else
        cout << "This graph doesn't contain a cycle." << endl;
 }

int main () {
  driver();
  return 0;
}
