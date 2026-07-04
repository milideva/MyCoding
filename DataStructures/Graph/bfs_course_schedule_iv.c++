/**
 * Problem: Course Schedule IV
 * Given numCourses and a list of prerequisites, answer multiple queries 
 * asking if course U is a prerequisite of course V.
 * 
 * Strategy: Topological Sort + Bitset for Reachability
 * - Build adjacency list and in-degrees.
 * - Use Kahn's algorithm (BFS) for topological sort.
 * - For each node, maintain a bitset of all its ancestors (prerequisites).
 * - During BFS, when edge U -> V is processed, V's bitset = V's bitset | U's bitset | {U}.
 * 
 * Time Complexity: O(V + E + (V * E) / 64 + Q)
 * Space Complexity: O(V^2 / 64)
 */

#include <iostream>
#include <vector>
#include <queue>
#include <bitset>

using namespace std;

class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<int> inDegree(numCourses, 0);
        vector<vector<int>> adj(numCourses);
        // Using bitset of size 100 as per constraints (numCourses <= 100)
        vector<bitset<100>> ancestors(numCourses);

        for (const auto& pre : prerequisites) {
            adj[pre[0]].push_back(pre[1]);
            inDegree[pre[1]]++;
            ancestors[pre[1]].set(pre[0]);
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) q.push(i);
        }

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int neighbor : adj[curr]) {
                // Propagate reachability
                ancestors[neighbor] |= ancestors[curr];
                if (--inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        vector<bool> result;
        for (const auto& query : queries) {
            result.push_back(ancestors[query[1]].test(query[0]));
        }
        return result;
    }
};

int main() {
    int numCourses = 3;
    vector<vector<int>> prerequisites = {{1, 2}, {1, 0}, {2, 0}};
    vector<vector<int>> queries = {{1, 0}, {1, 2}, {0, 1}};

    Solution sol;
    vector<bool> result = sol.checkIfPrerequisite(numCourses, prerequisites, queries);

    cout << "Reachability queries:" << endl;
    for (size_t i = 0; i < queries.size(); i++) {
        cout << queries[i][0] << " -> " << queries[i][1] << ": " 
             << (result[i] ? "True" : "False") << endl;
    }

    return 0;
}
