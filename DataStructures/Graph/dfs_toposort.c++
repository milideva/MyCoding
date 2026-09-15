/**
 * @file dfs_toposort.c++
 * @brief Topological Sort implementation using Depth-First Search (DFS) on Directed Graphs.
 *
 * This module implements two approaches for topological sorting:
 * 1. Classic 2-Pass approach: Assumes a DAG (Directed Acyclic Graph) and performs DFS.
 * 2. Integrated 1-Pass approach: Uses 3-state coloring DFS to simultaneously 
 *    perform topological sorting and cycle detection.
 *
 * ============================================================================
 * Key Terminology & Course Prerequisites Mapping:
 * ============================================================================
 * - V: The total number of vertices (nodes) in the graph, numbered from 0 to V-1.
 * - adj: The Adjacency List of the graph, represented as a vector of vectors:
 *        `adj[u]` contains all neighbor vertices `v` such that there exists
 *        a directed edge from `u` to `v` (u -> v).
 *
 * - Real-World Interpretation (Course Prerequisites Example):
 *   Let's map V = 4 to a computer science curriculum:
 *     - Course 0: Intro to Programming (Prerequisite for Data Structures & Architecture)
 *     - Course 1: Data Structures (Prerequisite for Operating Systems)
 *     - Course 2: Computer Architecture (Prerequisite for Operating Systems)
 *     - Course 3: Operating Systems (Requires both Data Structures & Architecture)
 *
 *   This forms the following Directed Acyclic Graph (DAG):
 *
 *          [0: Intro to Prog]
 *              /          \
 *             v            v
 *      [1: Data Struct]   [2: Comp Arch]
 *             \            /
 *              v          v
 *          [3: Operating Systems]
 *
 *   We represent this dependency using directed edges where (u -> v) means 
 *   "u must be taken before v" (u is a prerequisite for v):
 *     - adj[0] = {1, 2}  (Intro to Programming is a prerequisite for Data Struct & Comp Arch)
 *     - adj[1] = {3}     (Data Structures is a prerequisite for Operating Systems)
 *     - adj[2] = {3}     (Computer Architecture is a prerequisite for Operating Systems)
 *     - adj[3] = {}      (Operating Systems has no courses depending on it)
 *
 * ============================================================================
 * Complexity Analysis:
 * ============================================================================
 * Time Complexity (All Methods):
 *   - Worst-Case: O(V + E)
 *     We visit every vertex V once and traverse every directed edge E once.
 *   - Average-Case: O(V + E)
 *   - Best-Case: O(V + E)
 *   where V is the number of vertices and E is the number of edges.
 *
 * Space Complexity (All Methods):
 *   - Worst-Case: O(V)
 *     Used by the visited tracker (O(V)), the stack for topological order (O(V)),
 *     and the recursion call stack (O(V)).
 *   - Auxiliary Space: O(V) (excluding adjacency list input)
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
private:
    /**
     * @brief Helper function to perform DFS traversal and record post-order sequence.
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
    void dfs(int i, vector<bool>& visited, stack<int>& stk, const vector<vector<int>>& adj) {
        visited[i] = true;
        
        for (int neighbor : adj[i]) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited, stk, adj);
            }
        }
        
        stk.push(i);
    }

    /**
     * @brief Helper function to perform 3-state (coloring) DFS to sort and detect cycles simultaneously.
     * 
     * State values:
     *   - 0: Unvisited (White)
     *   - 1: Visiting (Gray - currently in DFS call stack)
     *   - 2: Fully Visited (Black - processed and pushed to topological stack)
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
    bool dfs_cycle_detect(int i, vector<int>& state, stack<int>& stk, const vector<vector<int>>& adj) {
        state[i] = 1; // Mark as 'Visiting'
        
        for (int neighbor : adj[i]) {
            if (state[neighbor] == 0) { // Unvisited
                if (!dfs_cycle_detect(neighbor, state, stk, adj)) {
                    return false; // Propagate cycle discovery up
                }
            } else if (state[neighbor] == 1) { // Visiting (back-edge found!)
                return false;
            }
        }
        
        state[i] = 2; // Mark as 'Fully Visited'
        stk.push(i);
        return true;
    }

public:
    /**
     * @brief Public method to perform topological sort on a DAG.
     * 
     * ============================================================================
     * Complexity Analysis:
     * ============================================================================
     * Time Complexity:
     *   - Worst-Case: O(V + E)
     *     Traverses all vertices V and edges E using DFS.
     * Space Complexity:
     *   - Worst-Case: O(V)
     *     Utilizes boolean visited array (O(V)), linear stack (O(V)), output 
     *     vector (O(V)), and recursion stack (O(V)).
     * ============================================================================
     * 
     * @param V The total number of vertices (nodes) in the graph, numbered from 0 to V-1.
     * @param adj The Adjacency List representing the graph, where adj[u] contains all neighbor
     *            vertices v such that there is a directed edge from u to v (u -> v).
     */
    vector<int> topoSort(int V, const vector<vector<int>>& adj) {
        vector<bool> visited(V, false);
        stack<int> stk;
        vector<int> result;

        // Run DFS from every unvisited node
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs(i, visited, stk, adj);
            }
        }

        // Pop elements from stack to get linear topological ordering
        while (!stk.empty()) {
            result.push_back(stk.top());
            stk.pop();
        }

        return result;
    }

    /**
     * @brief Public method to perform topological sort with integrated cycle detection in a single pass.
     * 
     * ============================================================================
     * Complexity Analysis:
     * ============================================================================
     * Time Complexity:
     *   - Worst-Case: O(V + E)
     *     Simultaneously performs topological sorting and cycle detection.
     * Space Complexity:
     *   - Worst-Case: O(V)
     *     Uses state tracker array (O(V)), linear stack (O(V)), output vector (O(V)),
     *     and recursion stack (O(V)).
     * ============================================================================
     * 
     * @param V The total number of vertices (nodes) in the graph, numbered from 0 to V-1.
     * @param adj The Adjacency List representing the graph, where adj[u] contains all neighbor
     *            vertices v such that there is a directed edge from u to v (u -> v).
     * @return vector<int> The topological ordering of the vertices, or an empty vector
     *                     if a cycle is detected (which means no valid sort exists).
     */
    vector<int> topoSortWithCycleDetection(int V, const vector<vector<int>>& adj) {
        vector<int> state(V, 0); // 0 = Unvisited, 1 = Visiting, 2 = Visited
        stack<int> stk;
        vector<int> result;

        for (int i = 0; i < V; i++) {
            if (state[i] == 0) {
                if (!dfs_cycle_detect(i, state, stk, adj)) {
                    return {}; // Cycle detected, return empty vector
                }
            }
        }

        // Pop elements from stack to get linear topological ordering
        while (!stk.empty()) {
            result.push_back(stk.top());
            stk.pop();
        }

        return result;
    }
};

int main() {
    Solution sol;

    // --- Scenario 1: Directed Acyclic Graph (DAG) ---
    int V_dag = 4;
    vector<vector<int>> adj_dag(V_dag);
    
    // Graph representation: 
    // 0 (Intro to Prog) is prerequisite for 1 (Data Struct) and 2 (Comp Arch)
    // 1 (Data Struct) is prerequisite for 3 (Operating Systems)
    // 2 (Comp Arch) is prerequisite for 3 (Operating Systems)
    adj_dag[0].push_back(1);
    adj_dag[0].push_back(2);
    adj_dag[1].push_back(3);
    adj_dag[2].push_back(3);

    cout << "=== Classic Two-Pass Topological Sort (Assumes DAG) ===" << endl;
    cout << "--- DAG Test ---" << endl;
    vector<int> order = sol.topoSort(V_dag, adj_dag);
    cout << "Topological Sort Order: ";
    for (int node : order) {
        cout << node << " ";
    }
    cout << endl << endl;

    // --- Scenario 2: Directed Graph with a Cycle ---
    int V_cycle = 4;
    vector<vector<int>> adj_cycle(V_cycle);

    // Graph representation with a cycle: 
    // 0 -> 1, 1 -> 2, 2 -> 3, 3 -> 1 (Prerequisite loop: 1 -> 2 -> 3 -> 1)
    adj_cycle[0].push_back(1);
    adj_cycle[1].push_back(2);
    adj_cycle[2].push_back(3);
    adj_cycle[3].push_back(1); // Back-edge creating cycle: 1 -> 2 -> 3 -> 1

    cout << "=== Single-Pass Integrated Cycle Detection & TopoSort ===" << endl;
    cout << "--- DAG Test (Single-Pass) ---" << endl;
    vector<int> integrated_order_dag = sol.topoSortWithCycleDetection(V_dag, adj_dag);
    if (integrated_order_dag.empty()) {
        cout << "Error: Falsely reported cycle in DAG!" << endl;
    } else {
        cout << "Success: Successfully sorted DAG in single pass." << endl;
        cout << "Topological Sort Order: ";
        for (int node : integrated_order_dag) {
            cout << node << " ";
        }
        cout << endl;
    }

    cout << endl;

    cout << "--- Cyclic Graph Test (Single-Pass) ---" << endl;
    vector<int> integrated_order_cycle = sol.topoSortWithCycleDetection(V_cycle, adj_cycle);
    if (integrated_order_cycle.empty()) {
        cout << "Success: Cycle correctly detected, and empty list returned." << endl;
    } else {
        cout << "Error: Falsely completed topological sort on a cyclic graph!" << endl;
    }

    return 0;
}
