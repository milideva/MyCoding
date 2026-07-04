/**
 * Problem: Minimum Degree of a Connected Trio in a Graph
 * A connected trio is a set of three nodes where there is an edge between 
 * every pair of them. The degree of a connected trio is the number of edges 
 * incident to at least one of these nodes, but not incident to any node 
 * in the trio. Return the minimum degree of a connected trio.
 * 
 * Strategy: Brute Force with Adjacency Matrix
 * - Use an adjacency matrix for O(1) edge lookups.
 * - Store degrees of all nodes.
 * - Iterate through all possible triplets (i, j, k).
 * - If they form a trio, degree = degree(i) + degree(j) + degree(k) - 6.
 * 
 * Time Complexity: O(V^3)
 * Space Complexity: O(V^2)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        vector<vector<bool>> adj(n + 1, vector<bool>(n + 1, false));
        vector<int> degree(n + 1, 0);

        for (const auto& e : edges) {
            adj[e[0]][e[1]] = adj[e[1]][e[0]] = true;
            degree[e[0]]++;
            degree[e[1]]++;
        }

        int minDegree = INT_MAX;

        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (!adj[i][j]) continue;
                for (int k = j + 1; k <= n; k++) {
                    if (adj[i][k] && adj[j][k]) {
                        int currentDegree = degree[i] + degree[j] + degree[k] - 6;
                        minDegree = min(minDegree, currentDegree);
                    }
                }
            }
        }

        return (minDegree == INT_MAX) ? -1 : minDegree;
    }
};

int main() {
    int n = 6;
    vector<vector<int>> edges = {{1, 2}, {1, 3}, {3, 2}, {4, 1}, {5, 2}, {3, 6}};

    Solution sol;
    cout << "Min trio degree: " << sol.minTrioDegree(n, edges) << " (Expected: 3)" << endl;

    return 0;
}
