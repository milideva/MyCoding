/**
 * @file dfs_cycle_detection.c++
 * @brief Cycle Detection in Directed Graphs using Depth-First Search (DFS).
 *
 * This module implements and compares two primary DFS-based approaches for
 * cycle detection in directed graphs:
 * 1. The classic 2-array approach (visited path tracking).
 * 2. The optimized 3-state coloring approach.
 *
 * ============================================================================
 * Key Terminology & Concepts:
 * ============================================================================
 * - V: Total number of vertices (nodes) in the graph, numbered 0 to V-1.
 * - adj: Adjacency list representation where adj[u] contains all neighbor vertices v
 *        such that there is a directed edge from u to v (u -> v).
 *
 * ============================================================================
 * Why Directed Graph Cycle Detection Differs from Undirected Graph:
 * ============================================================================
 * 1. Path Dependency:
 *    - Undirected Graphs: A cycle exists if we visit an already-visited vertex
 *      that is NOT the immediate parent of the current vertex in the DFS tree.
 *      Since edges are bidirectional, we only need to avoid walking back across
 *      the edge we just traversed (parent).
 *    - Directed Graphs: Simply hitting an already-visited vertex does NOT imply
 *      a cycle. For example, in a "diamond" graph (1 -> 2 -> 4, 1 -> 3 -> 4),
 *      when traversing from 3 to 4, we find 4 already visited, but there is no
 *      cycle. A cycle only exists if we encounter a node that is currently in the
 *      active DFS recursion path (a back-edge).
 *
 * ============================================================================
 * Comparison of Cycle Detection Methods:
 * ============================================================================
 * +------------------------+-------------------+------------------+-----------------------------+
 * | Method                 | Supported Graphs  | Time Complexity  | Space Complexity / Pros/Cons|
 * +------------------------+-------------------+------------------+-----------------------------+
 * | DFS with Path-Tracking | Directed/Undirected| O(V + E)        | O(V)                        |
 * | (visitedPath/coloring) |                   |                  | + Intuitive, handles DAG    |
 * |                        |                   |                  | - Risk of Stack Overflow    |
 * +------------------------+-------------------+------------------+-----------------------------+
 * | Kahn's Algorithm       | Directed Only     | O(V + E)         | O(V)                        |
 * | (BFS-based In-degrees) |                   |                  | + Iterative, gives TopoSort |
 * |                        |                   |                  | - Requires in-degree tracking|
 * +------------------------+-------------------+------------------+-----------------------------+
 * | Disjoint Set Union     | Undirected Only   | O(E * alpha(V))  | O(V)                        |
 * | (DSU / Union-Find)     |                   |                  | + Best for dynamic graphs   |
 * |                        |                   |                  | - Bad for directed graphs   |
 * +------------------------+-------------------+------------------+-----------------------------+
 *
 * ============================================================================
 * Complexity Analysis:
 * ============================================================================
 * Time Complexity (All Methods in this file):
 *   - Worst-Case: O(V + E)
 *     We visit every vertex V once and traverse every directed edge E once.
 *   - Average-Case: O(V + E)
 *   - Best-Case: O(V + E)
 *
 * Space Complexity:
 *   - Worst-Case: O(V)
 *     Used by the tracking arrays and recursion call stack.
 *     - 2-Array Method: uses visited tracker (O(V)) and visitedPath tracker (O(V)).
 *     - 3-Color Method: optimizes space by collapsing both trackers into a single state vector (O(V)).
 * ============================================================================
 */

#include <iostream>
#include <vector>

using namespace std;

class CycleDetector {
private:
    /**
     * @brief Helper function to detect cycles using DFS with explicit path tracking.
     * 
     * ============================================================================
     * Complexity Analysis:
     * ============================================================================
     * Time Complexity:
     *   - Worst-Case: O(V + E)
     *     Traverses each vertex and directed edge at most once.
     * Space Complexity:
     *   - Worst-Case: O(V)
     *     Depth of recursion tree matches number of vertices in a linear graph.
     * ============================================================================
     */
    bool isCyclicDFS(int i, vector<bool>& visited, vector<bool>& visitedPath, const vector<vector<int>>& adj) {
        visited[i] = true;
        visitedPath[i] = true;

        for (int neighbor : adj[i]) {
            if (!visited[neighbor]) {
                if (isCyclicDFS(neighbor, visited, visitedPath, adj)) {
                    return true;
                }
            } else if (visitedPath[neighbor]) {
                return true;
            }
        }

        visitedPath[i] = false;
        return false;
    }

    /**
     * @brief Helper function to detect cycles using 3-state (coloring) DFS.
     * 
     * State values:
     *   - 0: Unvisited (White)
     *   - 1: Visiting/Active Path (Gray)
     *   - 2: Fully Visited (Black)
     * 
     * ============================================================================
     * Complexity Analysis:
     * ============================================================================
     * Time Complexity:
     *   - Worst-Case: O(V + E)
     *     Traverses each vertex and directed edge at most once.
     * Space Complexity:
     *   - Worst-Case: O(V)
     *     Depth of recursion tree matches number of vertices in a linear graph.
     * ============================================================================
     */
    bool isCyclic_3color_DFS(int i, vector<int>& state, const vector<vector<int>>& adj) {
        state[i] = 1; // Mark as 'Visiting' (Gray)
        
        for (int neighbor : adj[i]) {
            if (state[neighbor] == 0) { // Unvisited (White)
                if (isCyclic_3color_DFS(neighbor, state, adj)) {
                    return true;
                }
            } else if (state[neighbor] == 1) { // Visiting/Active Path (Gray) - cycle detected!
                return true;
            }
        }
        
        state[i] = 2; // Mark as 'Fully Visited' (Black)
        return false;
    }

public:
    /**
     * @brief Public method to check if the graph contains any cycle using the 2-array approach.
     * 
     * ============================================================================
     * Complexity Analysis:
     * ============================================================================
     * Time Complexity:
     *   - Worst-Case: O(V + E)
     *     Checks cycle status for all vertices and edges.
     * Space Complexity:
     *   - Worst-Case: O(V)
     *     Uses visited array (O(V)), visitedPath recursion-state tracker (O(V)), 
     *     and recursion stack (O(V)).
     * ============================================================================
     */
    bool isCyclic(int V, const vector<vector<int>>& adj) {
        vector<bool> visited(V, false);
        vector<bool> visitedPath(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (isCyclicDFS(i, visited, visitedPath, adj)) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * @brief Public method to check if the graph contains any cycle using the 3-state coloring approach.
     * 
     * This method is an optimization over the 2-array approach as it collapses
     * the 'visited' and 'visitedPath' arrays into a single state vector of integers.
     * 
     * ============================================================================
     * Complexity Analysis:
     * ============================================================================
     * Time Complexity:
     *   - Worst-Case: O(V + E)
     *     Checks cycle status for all vertices and edges.
     * Space Complexity:
     *   - Worst-Case: O(V)
     *     Uses single state array (O(V)) and recursion stack (O(V)).
     * ============================================================================
     */
    bool isCyclic_3color(int V, const vector<vector<int>>& adj) {
        vector<int> state(V, 0); // 0 = Unvisited, 1 = Visiting, 2 = Visited

        for (int i = 0; i < V; i++) {
            if (state[i] == 0) {
                if (isCyclic_3color_DFS(i, state, adj)) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    CycleDetector detector;

    // --- Scenario 1: Directed Acyclic Graph (DAG) ---
    int V_dag = 4;
    vector<vector<int>> adj_dag(V_dag);
    adj_dag[0].push_back(1);
    adj_dag[0].push_back(2);
    adj_dag[1].push_back(3);
    adj_dag[2].push_back(3);

    cout << "=== Test Series 1: Two-Array Approach ===" << endl;
    cout << "--- DAG Test ---" << endl;
    if (detector.isCyclic(V_dag, adj_dag)) {
        cout << "Error: Cycle detected in a DAG!" << endl;
    } else {
        cout << "Success: No cycles detected in the DAG." << endl;
    }

    // --- Scenario 2: Directed Graph with a Cycle ---
    int V_cycle = 4;
    vector<vector<int>> adj_cycle(V_cycle);
    adj_cycle[0].push_back(1);
    adj_cycle[1].push_back(2);
    adj_cycle[2].push_back(3);
    adj_cycle[3].push_back(1); // Back-edge creating cycle: 1 -> 2 -> 3 -> 1

    cout << "--- Cyclic Graph Test ---" << endl;
    if (detector.isCyclic(V_cycle, adj_cycle)) {
        cout << "Success: Cycle correctly detected in the cyclic graph!" << endl;
    } else {
        cout << "Error: Failed to detect cycle in the cyclic graph!" << endl;
    }

    cout << endl;

    cout << "=== Test Series 2: Pure 3-Color Cycle Detection ===" << endl;
    cout << "--- DAG Test (3-Color) ---" << endl;
    if (detector.isCyclic_3color(V_dag, adj_dag)) {
        cout << "Error: Cycle detected in a DAG using 3-Color!" << endl;
    } else {
        cout << "Success: No cycles detected in the DAG using 3-Color." << endl;
    }

    cout << "--- Cyclic Graph Test (3-Color) ---" << endl;
    if (detector.isCyclic_3color(V_cycle, adj_cycle)) {
        cout << "Success: Cycle correctly detected in the cyclic graph using 3-Color!" << endl;
    } else {
        cout << "Error: Failed to detect cycle in the cyclic graph using 3-Color!" << endl;
    }

    return 0;
}
