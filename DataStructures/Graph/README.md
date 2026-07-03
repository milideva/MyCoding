# Graph Traversal: BFS vs. DFS

This document provides a comprehensive overview of the two fundamental graph traversal algorithms: **Breadth-First Search (BFS)** and **Depth-First Search (DFS)**.

---

## 1. Depth-First Search (DFS)

### Characteristics
DFS explores as far as possible along each branch before backtracking. It behaves like a person navigating a maze by following a path until a dead end is reached, then returning to the last junction to try a different route.

### Implementation
DFS is most naturally implemented using **recursion** (which uses the call stack) or an explicit **stack** data structure.

#### Recursive Implementation (C++ Style)
```cpp
void DFS_recur(int curr, vector<vector<int>>& adj, vector<bool>& visited) {        
    visited[curr] = true; // Mark current node as visited
    
    // Explore all neighbors
    for(int neighbor : adj[curr]) {
        if(!visited[neighbor]) {
            DFS_recur(neighbor, adj, visited);
        }
    }
}

void DFS(int n, vector<vector<int>>& adj) {        
    vector<bool> visited(n, false);
    for(int i = 0; i < n; ++i) {
        if(!visited[i]) {
            DFS_recur(i, adj, visited);
        }
    }
}
```

### Key Use Cases
1.  **Topological Sort:** Essential for scheduling tasks with dependencies. Nodes are pushed onto a stack in post-order (after all neighbors are visited).
2.  **Backtracking:** Used in puzzles (Sudoku), games (Chess/Tic-Tac-Toe), and simulations to explore move sequences.
3.  **Connected Components:** Finding all reachable nodes in a graph.
4.  **Cycle Detection:** Using recursion stack states (Visiting/Visited) to identify back-edges.

### Advantages & Disadvantages
*   **Pros:** 
    *   Uses less memory than BFS on very wide trees (space is proportional to the maximum depth, $O(H)$).
    *   Easier to implement via recursion.
    *   Better for deep solutions or finding "complete" configurations (leaves).
*   **Cons:**
    *   Can suffer from non-termination on infinite graphs (e.g., web crawling).
    *   Does **not** guarantee the shortest path.
    *   Can lead to stack overflow on extremely deep trees.

---

## 2. Breadth-First Search (BFS)

### Characteristics
BFS explores all neighbors at the present depth before moving on to the nodes at the next depth level. It visits nodes in concentric "layers" or "waves" emanating from the source.

### Implementation
BFS is **iterative** and uses a **queue** data structure.

#### Iterative Implementation (C++ Style)
```cpp
void BFS(int startNode, vector<vector<int>>& adj, int target) {
    int n = adj.size();
    vector<bool> visited(n, false);
    queue<pair<int, int>> q; // Pair: {node, distance}

    q.push({startNode, 0});
    visited[startNode] = true;

    while (!q.empty()) {
        auto [curr, dist] = q.front();
        q.pop();

        if (curr == target) return; // Shortest path found

        for (int neighbor : adj[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push({neighbor, dist + 1});
            }
        }
    }
}
```

### Key Use Cases
1.  **Shortest Path:** Guaranteed to find the shortest path in an **unweighted** graph.
2.  **Peer-to-Peer Networks:** Finding nearby neighbors (e.g., BitTorrent).
3.  **Social Networks:** Finding "friends of friends" within a specific degree of separation.
4.  **GPS Systems:** Finding the nearest locations (Points of Interest).

### Advantages & Disadvantages
*   **Pros:**
    *   Guaranteed shortest path for unweighted graphs.
    *   Handles infinite graphs better (never goes "arbitrarily deep").
*   **Cons:**
    *   Memory intensive for very wide graphs ($O(W)$), as it must store the entire "frontier" in a queue.

---

## 3. Comparison Summary

| Feature | DFS | BFS |
| :--- | :--- | :--- |
| **Data Structure** | Stack (or Recursion) | Queue |
| **Search Strategy** | Deepest first | Widest first |
| **Memory Complexity** | $O(H)$ (Height of tree) | $O(W)$ (Width of tree) |
| **Time Complexity** | $O(V + E)$ | $O(V + E)$ |
| **Shortest Path?** | No | Yes (unweighted) |
| **Best For...** | Deep trees, Backtracking, Games | Shallow trees, Shortest Path |

### Intuition: When to choose what?
*   **Choose BFS if:**
    *   The target is likely near the source.
    *   You need the shortest path.
    *   The graph is extremely deep but not too wide.
*   **Choose DFS if:**
    *   The graph is extremely wide but not too deep.
    *   You need to visit every node (Topological Sort).
    *   You are looking for rare solutions deep in the tree (Backtracking).

---

## 4. Advanced Concepts

### Iterative Deepening DFS (IDDFS)
Combines the space-efficiency of DFS with the shortest-path guarantee of BFS. It performs a DFS up to a certain depth, then increases the depth limit and repeats. Useful for game trees with large branching factors.

---

## 5. Implementation Standards in this Repo

1.  **Search Prefixes**: Filenames are prefixed with `dfs_`, `bfs_`, `dsu_`, or `greedy_` to indicate the primary algorithm used (e.g., `bfs_rotting_oranges.c++`).
2.  **Complexity Headers**: Every source file contains a detailed Time/Space analysis and comparison with brute-force approaches.
3.  **Visual Consistency**: ASCII diagrams and detailed problem descriptions are included in all complex implementations.
