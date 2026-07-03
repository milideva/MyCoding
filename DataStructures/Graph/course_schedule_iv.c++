/*
  LeetCode 1462: Course Schedule IV

  Algorithm: Topological Sort + Ancestor Bitset
  1. Build an adjacency list and calculate in-degrees for all courses.
  2. Use Kahn's algorithm (BFS) for topological sorting.
  3. Maintain a bitset for each course where the i-th bit represents 
     whether course 'i' is an ancestor (direct or indirect prerequisite).
  4. During BFS, when processing an edge `u -> v`, update `ancestors[v]` by 
     ORing it with `ancestors[u]` and setting the bit for `u`.

  Complexity Analysis:
  - Time Complexity: O(V + E + (V * E) / 64)
    Reason: Building the graph is O(V + E). The topological sort visits 
    every edge (E), and for each edge, we perform a bitset OR operation. 
    A bitset OR takes O(V / word_size) where word_size is typically 64. 
    Querying is O(1) per query (Q), so O(V + E + VE/64 + Q).
  - Space Complexity: O(V^2 / 64)
    Reason: We store a bitset of size V for each of the V nodes.

  Alternative Approaches:
  - Floyd-Warshall: Compute the transitive closure of the graph.
    - Time Complexity: O(V^3).
    - Comparison: Efficient for dense graphs with V <= 500, but topological 
      sort with bitset is faster for sparse graphs.
  - BFS/DFS per Query (Brute Force): For each query (u, v), perform a 
    traversal to see if v is reachable from u.
    - Time Complexity: O(Q * (V + E)).
    - Comparison: Extremely slow if Q is large (up to 10^4 queries).

  Comparison:
  - Pre-computing reachability using bitsets and topological sort is the 
    most efficient way to handle a large number of prerequisite queries 
    on a Directed Acyclic Graph (DAG).
*/

#include <vector>
#include <queue>
#include <bitset>
#include <iostream>

using namespace std;


class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector <int> inDegree(numCourses, 0);
        vector <vector <int>> adj(numCourses);
        vector <bitset<100>> ancestors(numCourses);

        for (auto edge : prerequisites) {
            auto pre = edge[0];
            auto course = edge[1];
            adj[pre].push_back(course); // build the adjacency list for the graph
            inDegree[course]++; // count the in-degrees for topological sorting
            ancestors[course].set(pre); // set the bit for the direct prerequisite
        }

        queue <int> q;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) q.push(i);
        }
        while (!q.empty()) {
            int course = q.front(); q.pop();
            for (int dep : adj[course]) {
                // This is the key step - we are doing a topological sort and for each course, we are updating the ancestors of its dependent courses by ORing with the ancestors of the current course. This way, we are effectively propagating the prerequisite information down the graph.
                ancestors[dep] |= ancestors[course];

                if (--inDegree[dep] == 0) {
                    q.push(dep);
                }
            }
        }

        vector <bool> result;
        for (auto query: queries) {
            int pre = query[0];
            int course = query[1];
            result.push_back(ancestors[course].test(pre));
        }
        return result;
    }
};

int main () {
    Solution solution;
    vector<vector<int>> prerequisites = {{1,2},{1,0},{2,0}};
    vector<vector<int>> queries = {{1,0},{1,2}};
    vector<bool> result = solution.checkIfPrerequisite(3, prerequisites, queries);
    for (bool res : result) {
        cout << (res ? "true" : "false") << " ";
    }
    cout << endl;
    return 0;
}