/**
 * @file gpu_scheduler_cycle_detection.c++
 * @brief Circular Dependency (Deadlock) Detection for Pods in a GPU Cluster.
 *
 * In high-performance GPU clusters, workloads (represented as Pods) are 
 * often co-scheduled or executed in a pipelined fashion where certain Pods 
 * depend on the output or completion of other Pods.
 * 
 * If these inter-pod dependencies form a circular loop (e.g., Pod A depends on 
 * Pod B, Pod B on Pod C, and Pod C on Pod A), none of the Pods can ever be 
 * scheduled, resulting in a system-wide Scheduling Deadlock.
 *
 * This module implements a Cycle Detector that analyzes the pod dependency 
 * graph using two DFS-based approaches adapted for arbitrary integer Pod IDs:
 * 1. The classic 2-set visited/path approach.
 * 2. The optimized 3-state coloring approach using unordered maps.
 *
 * ============================================================================
 * Key Terminology:
 * ============================================================================
 * - Pod ID: Arbitrary integer ID representing a workload.
 * - Dependency (u -> v): Pod u depends on Pod v (v must complete before u starts).
 * - Deadlock: A cyclic dependency path where u can reach u via directed edges.
 *
 * ============================================================================
 * Complexity Analysis:
 * ============================================================================
 * Time Complexity (Both Methods):
 *   - Worst-Case: O(V + E)
 *     Where V is the number of unique Pods and E is the number of dependency 
 *     edges. We visit each Pod once and traverse each dependency edge once.
 *   - Average-Case: O(V + E)
 *   - Best-Case: O(V + E)
 *
 * Space Complexity:
 *   - Worst-Case: O(V)
 *     Used to store the tracking states/sets and the recursion call stack.
 *     - 2-Set Method: uses visited set (O(V)), visitedPath set (O(V)), and stack (O(V)).
 *     - 3-Color Method: collapses sets into a single state map (O(V)) and stack (O(V)).
 * ============================================================================
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
    // Adjacency list: pod_id -> list of pod_ids it depends on
    unordered_map<int, vector<int>> adj;

    /**
     * @brief Helper function to detect cycles using 2-set path tracking DFS.
     * 
     * ============================================================================
     * Complexity Analysis:
     * ============================================================================
     * Time Complexity:
     *   - Worst-Case: O(V + E)
     *     Traverses each unique Pod and dependency edge at most once.
     * Space Complexity:
     *   - Worst-Case: O(V)
     *     Recursion stack depth and tracking sets bounded by the number of Pods.
     * ============================================================================
     */
    bool isCyclicDFS(int u, unordered_set<int>& visited, unordered_set<int>& visitedPath) {
        visited.insert(u);
        visitedPath.insert(u);

        // Check all dependencies of u
        if (adj.find(u) != adj.end()) {
            for (int v : adj[u]) {
                if (visited.find(v) == visited.end()) { // Unvisited
                    if (isCyclicDFS(v, visited, visitedPath)) {
                        return true;
                    }
                } else if (visitedPath.find(v) != visitedPath.end()) { // On active path!
                    return true;
                }
            }
        }

        visitedPath.erase(u); // Backtrack: remove from active path
        return false;
    }

    /**
     * @brief Helper function to detect cycles using 3-state coloring DFS.
     * 
     * ============================================================================
     * Complexity Analysis:
     * ============================================================================
     * Time Complexity:
     *   - Worst-Case: O(V + E)
     *     Traverses each unique Pod and dependency edge at most once.
     * Space Complexity:
     *   - Worst-Case: O(V)
     *     Recursion stack depth and state map storage are bounded by unique Pods.
     * ============================================================================
     */
    bool isCyclic_3color_DFS(int u, unordered_map<int, NodeState>& state) {
        state[u] = NodeState::VISITING; // Mark as 'Visiting' (Gray)

        if (adj.find(u) != adj.end()) {
            for (int v : adj[u]) {
                // Determine current state of the dependency
                NodeState v_state = NodeState::UNVISITED;
                if (state.find(v) != state.end()) {
                    v_state = state[v];
                }

                if (v_state == NodeState::UNVISITED) {
                    if (isCyclic_3color_DFS(v, state)) {
                        return true;
                    }
                } else if (v_state == NodeState::VISITING) { // On active path - cycle detected!
                    return true;
                }
            }
        }

        state[u] = NodeState::VISITED; // Mark as 'Fully Visited' (Black)
        return false;
    }

public:
    // Add a dependency: u depends on v
    void add_dependency(int u, int v) {
        adj[u].push_back(v);
        // Ensure v is registered in the adjacency list keys so we know it exists
        if (adj.find(v) == adj.end()) {
            adj[v] = {};
        }
    }

    /**
     * @brief Checks if there are circular dependencies (deadlocks) in the registered Pods
     *        using the 2-set approach.
     * 
     * ============================================================================
     * Complexity Analysis:
     * ============================================================================
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     * ============================================================================
     */
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

    /**
     * @brief Checks if there are circular dependencies (deadlocks) in the registered Pods
     *        using the 3-state coloring approach.
     * 
     * ============================================================================
     * Complexity Analysis:
     * ============================================================================
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     * ============================================================================
     */
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
    // Pipeland Flow: Pod 101 (Pre-processing) -> Pod 102 (Training) -> Pod 103 (Evaluation)
    // Edges: 102 depends on 101, 103 depends on 102
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
    // Circular Loop: Pod 201 depends on Pod 202, Pod 202 depends on Pod 203, Pod 203 depends on Pod 201
    PodDependencyCycleDetector cyclic_pipeline;
    cyclic_pipeline.add_dependency(201, 202);
    cyclic_pipeline.add_dependency(202, 203);
    cyclic_pipeline.add_dependency(203, 201); // Back-dependency causing deadlock!

    cout << "--- Test Series 2: Cyclic Pod Pipeline (Deadlock Loop) ---" << endl;
    cout << "  - Method 1 (2-Set):   " 
         << (cyclic_pipeline.has_circular_dependency() ? "Success: Deadlock correctly detected!" : "Error: Failed to find deadlock!") 
         << endl;
    cout << "  - Method 2 (3-Color): " 
         << (cyclic_pipeline.has_circular_dependency_3color() ? "Success: Deadlock correctly detected!" : "Error: Failed to find deadlock!") 
         << endl << endl;

    return 0;
}
