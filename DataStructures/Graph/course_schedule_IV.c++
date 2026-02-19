/*
1462. Course Schedule IV

Medium

There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course ai first if you want to take course bi.

For example, the pair [0, 1] indicates that you have to take course 0 before you can take course 1.
Prerequisites can also be indirect. If course a is a prerequisite of course b, and course b is a prerequisite of course c, then course a is a prerequisite of course c.

You are also given an array queries where queries[j] = [uj, vj]. For the jth query, you should answer whether course uj is a prerequisite of course vj or not.

Return a boolean array answer, where answer[j] is the answer to the jth query.

 

Example 1:


Input: numCourses = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
Output: [false,true]
Explanation: The pair [1, 0] indicates that you have to take course 1 before you can take course 0.
Course 0 is not a prerequisite of course 1, but the opposite is true.
Example 2:

Input: numCourses = 2, prerequisites = [], queries = [[1,0],[0,1]]
Output: [false,false]
Explanation: There are no prerequisites, and each course is independent.
Example 3:


Input: numCourses = 3, prerequisites = [[1,2],[1,0],[2,0]], queries = [[1,0],[1,2]]
Output: [true,true]
 

Constraints:

2 <= numCourses <= 100
0 <= prerequisites.length <= (numCourses * (numCourses - 1) / 2)
prerequisites[i].length == 2
0 <= ai, bi <= numCourses - 1
ai != bi
All the pairs [ai, bi] are unique.
The prerequisites graph has no cycles.
1 <= queries.length <= 104
0 <= ui, vi <= numCourses - 1
ui != vi

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