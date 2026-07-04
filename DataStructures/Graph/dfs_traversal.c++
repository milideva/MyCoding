/**
 * Problem: Graph DFS Traversal
 * Implement Depth-First Search (DFS) for a directed/undirected graph.
 * 
 * Strategy: Recursive DFS
 * - Use an adjacency list to represent the graph.
 * - Use a visited set/array to keep track of visited nodes.
 * - Recursively visit all unvisited neighbors of the current node.
 * 
 * Time Complexity: O(V + E)
 * Space Complexity: O(V)
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Graph {
    unordered_map<int, vector<int>> adj;

public:
    void addEdge(int u, int v, bool bidirectional = true) {
        adj[u].push_back(v);
        if (bidirectional) {
            adj[v].push_back(u);
        }
    }

    void dfsHelper(int curr, unordered_set<int>& visited) {
        visited.insert(curr);
        cout << curr << " ";

        for (int neighbor : adj[curr]) {
            if (visited.find(neighbor) == visited.end()) {
                dfsHelper(neighbor, visited);
            }
        }
    }

    void dfs(int startNode) {
        unordered_set<int> visited;
        cout << "DFS Traversal starting from " << startNode << ": ";
        dfsHelper(startNode, visited);
        cout << endl;
    }
};

int main() {
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    g.dfs(2);

    return 0;
}
