/**
 * Problem: Friend Circles (Number of Provinces)
 * Given an N x N matrix where M[i][j] = 1 if i and j are direct friends, 
 * return the total number of friend circles.
 * 
 * Strategy: DFS on Adjacency Matrix
 * - Treat each person as a node in a graph.
 * - Iterate through each person. If they haven't been visited, start a DFS.
 * - DFS marks all reachable friends as visited.
 * - Each new DFS start represents a new friend circle.
 * 
 * Time Complexity: O(N^2)
 * Space Complexity: O(N)
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    void dfs(const vector<vector<int>>& isConnected, vector<bool>& visited, int curr) {
        visited[curr] = true;
        for (int neighbor = 0; neighbor < (int)isConnected.size(); neighbor++) {
            if (isConnected[curr][neighbor] == 1 && !visited[neighbor]) {
                dfs(isConnected, visited, neighbor);
            }
        }
    }

public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int count = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(isConnected, visited, i);
                count++;
            }
        }
        return count;
    }
};

int main() {
    vector<vector<int>> matrix = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    Solution sol;
    cout << "Number of friend circles: " << sol.findCircleNum(matrix) << " (Expected: 2)" << endl;

    return 0;
}
