/*
  LeetCode 210: Course Schedule II

  Problem Description:
  There are a total of numCourses courses you have to take, labeled 
  from 0 to numCourses - 1. You are given an array prerequisites 
  where prerequisites[i] = [ai, bi] indicates that you must take 
  course bi first if you want to take course ai.

  For example, the pair [0, 1], indicates that to take course 0 you 
  have to first take course 1.

  Return the ordering of courses you should take to finish all 
  courses. If there are many valid answers, return any of them. If 
  it is impossible to finish all courses, return an empty array.

  Algorithm: Kahn's Algorithm (BFS-based Topological Sort)
  1. Represent prerequisites as a directed graph (Adjacency List).
  2. Calculate the in-degree of every course.
  3. Add all courses with in-degree 0 to a queue.
  4. While queue is not empty:
     - Pop course `u`, add it to the result list.
     - For each neighbor `v` of `u`, decrement `in-degree[v]`.
     - If `in-degree[v]` becomes 0, add `v` to the queue.
  5. If the result list contains all courses, return it; otherwise, 
     a cycle exists (return empty).

  Complexity Analysis:
  - Time Complexity: O(V + E)
    Reason: Building the graph takes O(E). The BFS visits every vertex 
    and edge once.
  - Space Complexity: O(V + E)
    Reason: To store the adjacency list (O(V+E)) and in-degree array (O(V)).

  Alternative Approaches:
  - DFS-based Topological Sort: 
    - Logic: Use three states (unvisited, visiting, visited) to detect 
      cycles and a stack to record the finish order.
    - Time: O(V + E), Space: O(V + E).
    - Comparison: Equally efficient. Kahn's is often easier to understand 
      as it directly simulates "taking courses with no dependencies."

  Brute Force comparison:
  - Repeatedly scan the prerequisites list to find a course with no 
    unsatisfied dependencies, remove it, and repeat.
  - Time Complexity: O(V * E).
  - Comparison: Kahn's Algorithm optimizes this by using a queue and 
    pre-computed in-degrees, achieving linear time.
*/

#include <vector>
#include <unordered_map>
#include <iostream>
#include <queue>

using namespace std;
class Solution {
    unordered_map <int, vector<int>> prereqMap; // prereqMap[a] = b, c, d etc
    unordered_map <int, int> numPrereqs; // numPrereqs[a] = 3; a has 3 pre-req.s

public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {

        // This init is necessary for the courses that have no pre-req.s
        for (int i = 0; i < numCourses; ++i) {
            numPrereqs[i] = 0;
        }
        
        vector <int> courses;
        for (auto vec: prerequisites) {
            auto a = vec[0]; // a depends on b
            auto b = vec[1];
            prereqMap[b].push_back(a);// course 'a' depends on b, b must come before a
            numPrereqs[a]++; // how many does course 'a' depend on?
        }

        queue <int> q;
        for (auto [course, numPrereqs]: numPrereqs) {
            if (numPrereqs == 0) {
                q.push(course);
            }
        }
        while (!q.empty()) {
            int course = q.front(); q.pop();
            courses.push_back(course); // take this class that does not depend on any other prereq
            for (auto dependent : prereqMap[course]) {
                numPrereqs[dependent]--;
                if (numPrereqs[dependent] == 0)
                    q.push(dependent);
            }
        }
        if (courses.size() == numCourses) {
            return true;
        }
        return false;
    } 
};

void testCanFinish() {
    Solution solution;

    vector<vector<int>> v1{{5, 8}, {3, 5}, {1, 9}, {4, 5}, {0, 2}, {7, 8}, {4, 9}};
    vector<vector<int>> v2{{1, 2}, {2, 3}, {3, 1}, {1, 0}};

    int numCourses1 = 10; // Number of courses for v1
    int numCourses2 = 4;  // Number of courses for v2

    // Test case 1
    bool result1 = solution.canFinish(numCourses1, v1);
    cout << "Test case 1: " << (result1 ? "True" : "False") << endl; // Expected output: True

    // Test case 2
    bool result2 = solution.canFinish(numCourses2, v2);
    cout << "Test case 2: " << (result2 ? "True" : "False") << endl; // Expected output: False
}

int main() {
    testCanFinish();
    return 0;
}

