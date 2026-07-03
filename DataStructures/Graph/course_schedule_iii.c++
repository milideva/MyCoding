
/*
  LeetCode 630: Course Schedule III

  Algorithm: Greedy with Priority Queue (Max-Heap)
  1. Sort courses by their deadlines (`lastDay`). This is a greedy choice: 
     always prioritize courses that must be finished earlier.
  2. Iterate through sorted courses, adding their duration to `totalTime`.
  3. Add the current course's duration to a max-heap.
  4. If `totalTime` exceeds the current course's deadline, remove the 
     longest course taken so far (top of max-heap) to save the most time.

  Complexity Analysis:
  - Time Complexity: O(N log N)
    Reason: Sorting takes O(N log N). We then iterate through N courses, 
    performing a push and potentially a pop from the priority queue, 
    each taking O(log N). Total: O(N log N + N log N) = O(N log N).
  - Space Complexity: O(N)
    Reason: The priority queue can store up to N course durations.

  Alternative Approaches:
  - Recursive Backtracking (Brute Force): Try every possible subset of 
    courses and check if they can be scheduled.
    - Time Complexity: O(2^N).
    - Comparison: Completely impractical for N=10^4.
  - Dynamic Programming: `dp[i][t]` could represent the max courses taken 
    using first `i` courses within time `t`.
    - Time Complexity: O(N * MaxDay).
    - Comparison: Since MaxDay can be very large, DP is less efficient 
      than the greedy O(N log N) approach.

  Comparison:
  - The greedy approach with a max-heap is the optimal solution because it 
    optimizes the "current" schedule by always sacrificing the most 
    time-consuming course when a deadline is missed.
*/

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        // 1. Sort courses by their deadlines (lastDay)
        sort(courses.begin(), courses.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        priority_queue<int> maxHeap; // To keep track of durations of taken courses
        int totalTime = 0;

        for (const auto& course : courses) {
            int duration = course[0];
            int lastDay = course[1];

            // Add the current course
            totalTime += duration;
            maxHeap.push(duration);

            // 2. If we exceeded the deadline, drop the longest course taken so far
            if (totalTime > lastDay) {
                totalTime -= maxHeap.top();
                maxHeap.pop();
            }
        }

        // The size of the heap represents the max number of courses we could fit
        return maxHeap.size();
    }
};

int main() {
    Solution solution;
    vector<vector<int>> courses = {{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}};
    int result = solution.scheduleCourse(courses);
    cout << "Maximum number of courses taken: " << result << endl;
    return 0;
}