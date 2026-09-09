/**
 * @file dfs_toposort.c++
 * @brief Topological Sort and Cycle Detection implementation using Depth-First Search (DFS) on Directed Graphs.
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
 *     the recursion stack (O(V)), and the recursion recursion-stack tracker for
 *     cycle detection (O(V)).
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
     * @brief Helper function to detect cycles using DFS.
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
    bool isCyclicDFS(int i, vector<bool>& visited, vector<bool>& recStack, const vector<vector<int>>& adj) {
        visited[i] = true;
        recStack[i] = true;

        for (int neighbor : adj[i]) {
            if (!visited[neighbor]) {
                if (isCyclicDFS(neighbor, visited, recStack, adj)) {
                    return true;
                }
            } else if (recStack[neighbor]) {
                return true;
            }
        }

        recStack[i] = false;
        return false;
    }

    /**
     * @brief Helper function to perform 3-state (coloring) DFS to sort and detect cycles simultaneously.
     * 
     * State values:
     *   - 0: Unvisited
     *   - 1: Visiting (currently in DFS call stack)
     *   - 2: Fully Visited (processed and pushed to topological stack)
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
     *   - Average-Case: O(V + E)
     *   - Best-Case: O(V + E)
     * Space Complexity:
     *   - Worst-Case: O(V)
     *     Utilizes boolean visited array (O(V)), linear stack (O(V)), output 
     *     vector (O(V)), and recursion stack (O(V)).
     * ============================================================================
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
     * @brief Public method to check if the graph contains any cycle.
     * 
     * ============================================================================
     * Complexity Analysis:
     * ============================================================================
     * Time Complexity:
     *   - Worst-Case: O(V + E)
     *     Checks cycle status for all vertices and edges.
     *   - Average-Case: O(V + E)
     *   - Best-Case: O(V + E)
     * Space Complexity:
     *   - Worst-Case: O(V)
     *     Uses visited array (O(V)), recStack recursion-state tracker (O(V)), 
     *     and recursion stack (O(V)).
     * ============================================================================
     */
    bool isCyclic(int V, const vector<vector<int>>& adj) {
        vector<bool> visited(V, false);
        vector<bool> recStack(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (isCyclicDFS(i, visited, recStack, adj)) {
                    return true;
                }
            }
        }
        return false;
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
     *   - Average-Case: O(V + E)
     *   - Best-Case: O(V + E)
     * Space Complexity:
     *   - Worst-Case: O(V)
     *     Uses state tracker array (O(V)), linear stack (O(V)), output vector (O(V)),
     *     and recursion stack (O(V)).
     * ============================================================================
     * 
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
    
    // Graph representation: 0 -> 1, 0 -> 2, 1 -> 3, 2 -> 3
    adj_dag[0].push_back(1);
    adj_dag[0].push_back(2);
    adj_dag[1].push_back(3);
    adj_dag[2].push_back(3);

    cout << "=== Test Series 1: Two-Pass Approach ===" << endl;
    cout << "--- DAG Test ---" << endl;
    if (sol.isCyclic(V_dag, adj_dag)) {
        cout << "Error: Cycle detected in a DAG!" << endl;
    } else {
        cout << "Success: No cycles detected in the DAG." << endl;
        vector<int> order = sol.topoSort(V_dag, adj_dag);
        cout << "Topological Sort Order: ";
        for (int node : order) {
            cout << node << " ";
        }
        cout << endl;
    }

    cout << endl;

    // --- Scenario 2: Directed Graph with a Cycle ---
    int V_cycle = 4;
    vector<vector<int>> adj_cycle(V_cycle);

    // Graph representation with a cycle: 0 -> 1, 1 -> 2, 2 -> 3, 3 -> 1
    adj_cycle[0].push_back(1);
    adj_cycle[1].push_back(2);
    adj_cycle[2].push_back(3);
    adj_cycle[3].push_back(1); // Back-edge creating cycle: 1 -> 2 -> 3 -> 1

    cout << "--- Cyclic Graph Test ---" << endl;
    if (sol.isCyclic(V_cycle, adj_cycle)) {
        cout << "Success: Cycle correctly detected in the cyclic graph!" << endl;
    } else {
        cout << "Error: Failed to detect cycle in the cyclic graph!" << endl;
    }

    cout << endl;

    cout << "=== Test Series 2: Single-Pass Integrated Cycle Detection & TopoSort ===" << endl;
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
