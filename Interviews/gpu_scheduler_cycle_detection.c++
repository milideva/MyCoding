/**
 * @file gpu_scheduler_cycle_detection.c++
 * @brief Circular Dependency (Deadlock) Detection for Pods in a GPU Cluster.
 *
 * Why Directed Graph Cycle Detection Differs from Undirected Graph:
 * 1. Path Dependency:
 *    - Undirected Graphs: A cycle exists if we visit an already-visited vertex that is 
 *      NOT the immediate parent of the current vertex in the DFS tree.
 *    - Directed Graphs: Simply hitting an already-visited vertex does NOT imply a cycle. 
 *      A cycle only exists if we encounter a node that is currently in the active DFS 
 *      recursion path (a back-edge).
 *
 * Comparison of Cycle Detection Methods:
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
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// State representation for 3-state (coloring) graph traversal
enum class NodeState {
    UNVISITED = 0, // White / Unvisited
    VISITING = 1,  // Gray / Currently in DFS recursion path
    VISITED = 2    // Black / Fully processed (no cycles possible from here)
};

class PodDependencyCycleDetector {
private:
    unordered_map<int, vector<int>> adj; // pod_id -> list of pod_ids it depends on

    // Helper function to detect cycles using DFS with 2-set path tracking.
    // Time Complexity:  O(V + E) - Traverses each unique Pod and dependency edge once.
    // Space Complexity: O(V)     - Recursion stack and tracking sets bounded by unique Pods.
    bool isCyclicDFS(int u, unordered_set<int>& visited, unordered_set<int>& visitedPath) {
        visited.insert(u);
        visitedPath.insert(u);

        if (adj.find(u) != adj.end()) {
            for (int v : adj[u]) {
                if (visited.find(v) == visited.end()) { // Unvisited
                    if (isCyclicDFS(v, visited, visitedPath)) {
                        return true;
                    }
                } else if (visitedPath.find(v) != visitedPath.end()) { // Back-edge found
                    return true;
                }
            }
        }

        visitedPath.erase(u); // Backtrack
        return false;
    }

    // Helper function to detect cycles using 3-state coloring DFS.
    // Time Complexity:  O(V + E) - Traverses each unique Pod and dependency edge once.
    // Space Complexity: O(V)     - Recursion stack and state map bounded by unique Pods.
    bool isCyclic_3color_DFS(int u, unordered_map<int, NodeState>& state) {
        state[u] = NodeState::VISITING; // Mark as 'Visiting' (Gray)

        if (adj.find(u) != adj.end()) {
            for (int v : adj[u]) {
                NodeState v_state = NodeState::UNVISITED;
                if (state.find(v) != state.end()) {
                    v_state = state[v];
                }

                if (v_state == NodeState::UNVISITED) {
                    if (isCyclic_3color_DFS(v, state)) {
                        return true;
                    }
                } else if (v_state == NodeState::VISITING) { // Back-edge found
                    return true;
                }
            }
        }

        state[u] = NodeState::VISITED; // Mark as 'Fully Visited' (Black)
        return false;
    }

public:
    void add_dependency(int u, int v) {
        adj[u].push_back(v);
        if (adj.find(v) == adj.end()) {
            adj[v] = {};
        }
    }

    // Public method to check circular dependencies using 2-set path tracking.
    // Time Complexity:  O(V + E)
    // Space Complexity: O(V)
    bool has_circular_dependency() {
        unordered_set<int> visited;
        unordered_set<int> visitedPath;

        for (const auto& [u, _] : adj) {
            if (visited.find(u) == visited.end()) {
                if (isCyclicDFS(u, visited, visitedPath)) {
                    return true;
                }
            }
        }
        return false;
    }

    // Public method to check circular dependencies using 3-state coloring.
    // Time Complexity:  O(V + E)
    // Space Complexity: O(V)
    bool has_circular_dependency_3color() {
        unordered_map<int, NodeState> state;

        for (const auto& [u, _] : adj) {
            NodeState u_state = NodeState::UNVISITED;
            if (state.find(u) != state.end()) {
                u_state = state[u];
            }

            if (u_state == NodeState::UNVISITED) {
                if (isCyclic_3color_DFS(u, state)) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    cout << "=== GPU Scheduler Circular Dependency (Deadlock) Detector ===" << endl << endl;

    // --- Scenario 1: A Valid Pipeline (DAG of Pods, No Deadlocks) ---
    PodDependencyCycleDetector valid_pipeline;
    valid_pipeline.add_dependency(102, 101);
    valid_pipeline.add_dependency(103, 102);

    cout << "--- Test Series 1: Valid Pod Pipeline (No Cycles) ---" << endl;
    cout << "  - Method 1 (2-Set):   " 
         << (valid_pipeline.has_circular_dependency() ? "DEADLOCK DETECTED! (Error)" : "Success: No deadlock found.") 
         << endl;
    cout << "  - Method 2 (3-Color): " 
         << (valid_pipeline.has_circular_dependency_3color() ? "DEADLOCK DETECTED! (Error)" : "Success: No deadlock found.") 
         << endl << endl;

    // --- Scenario 2: A Circular Dependency (Deadlock Loop) ---
    PodDependencyCycleDetector cyclic_pipeline;
    cyclic_pipeline.add_dependency(201, 202);
    cyclic_pipeline.add_dependency(202, 203);
    cyclic_pipeline.add_dependency(203, 201);

    cout << "--- Test Series 2: Cyclic Pod Pipeline (Deadlock Loop) ---" << endl;
    cout << "  - Method 1 (2-Set):   " 
         << (cyclic_pipeline.has_circular_dependency() ? "Success: Deadlock correctly detected!" : "Error: Failed to find deadlock!") 
         << endl;
    cout << "  - Method 2 (3-Color): " 
         << (cyclic_pipeline.has_circular_dependency_3color() ? "Success: Deadlock correctly detected!" : "Error: Failed to find deadlock!") 
         << endl << endl;

    return 0;
}
