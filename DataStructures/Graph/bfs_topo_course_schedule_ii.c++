/**
 * Problem: Course Schedule II
 * Given numCourses and a list of prerequisites, return the ordering of courses 
 * you should take to finish all courses. If impossible, return an empty array.
 * 
 * Strategy: Kahn's Algorithm (BFS Topological Sort)
 * - Build adjacency list and calculate in-degrees.
 * - Enqueue courses with 0 in-degree.
 * - While queue is not empty:
 *   - Pop course, add to result.
 *   - For each dependent course, decrement in-degree.
 *   - If in-degree becomes 0, enqueue it.
 * - If result size matches numCourses, return result; else return empty.
 * 
 * Time Complexity: O(V + E)
 * Space Complexity: O(V + E)
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> inDegree(numCourses, 0);
        vector<vector<int>> adj(numCourses);
        for (const auto& pre : prerequisites) {
            adj[pre[1]].push_back(pre[0]); // pre[1] must be taken before pre[0]
            inDegree[pre[0]]++;
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) q.push(i);
        }

        vector<int> order;
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            order.push_back(curr);

            for (int neighbor : adj[curr]) {
                if (--inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        if (order.size() == (size_t)numCourses) return order;
        return {};
    }
};

int main() {
    int numCourses = 4;
    vector<vector<int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};

    Solution sol;
    vector<int> order = sol.findOrder(numCourses, prerequisites);

    if (order.empty()) {
        cout << "No valid course order found (Cycle detected)." << endl;
    } else {
        cout << "Course order: ";
        for (int c : order) cout << c << " ";
        cout << endl;
    }

    return 0;
}
