/*
Given an array of meeting time intervals consisting of start and end times
[[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms
required.

Example 1:

Input: [[0, 30],[5, 10],[15, 20]]
Output: 2

Example 2:

Input: [[7,10],[2,4]]
Output: 1
*/

/*
  LeetCode 253: Meeting Rooms II

  Algorithm: Sweep-Line (using std::map)
  We map every start and end time to its impact on the room count. 
  +1 for start, -1 for end. The maximum cumulative sum during a timeline 
  sweep is the minimum number of rooms required.

  Complexity Analysis:
  - Time Complexity: O(N log N)
    Reason: N intervals, each with two map insertions (O(log N)). 
    Final sweep takes O(N).
  - Space Complexity: O(N)
    Reason: Map stores 2N boundary points.

  Alternative Approaches:
  - Priority Queue (Min-Heap): Sort intervals by start time. Store 
    meeting end-times in a min-heap. For each new meeting, if the 
    earliest end-time in the heap is <= current start, reuse the room 
    (pop from heap). Always push current end-time. Result is heap size.
    - Time: O(N log N).
  - Chronological Order (Two Arrays): Store starts and ends in two 
    separate arrays and sort them. Use two pointers to simulate the sweep.
    - Time: O(N log N), Space: O(N).

  Brute Force Approach:
  - Simulate every minute of the day. If max time is T, check every meeting 
    for every minute.
  - Time Complexity: O(N * T).
  - Comparison: If T is large (e.g., 10^9 as in some problems), this 
    is unusable. The sweep-line approach only processes critical 
    time-points, making it much more efficient.
*/

#include <vector>
#include <iostream>
#include <map>

using namespace std;

class Solution {
  map <int, int> calMap;
  
  int canAdd () {
    int count = 0;
    int maxK = 0;
    
    for (auto e : calMap) {
      count += e.second;
      maxK = max(maxK, count);
    }
    return maxK;
  }
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int len = intervals.size();
        if (len == 0) return 0;
        if (len == 1) return true;

        for (auto v :intervals) {
          calMap[v[0]]++;
          calMap[v[1]]--;
        }
        return canAdd();
    }
};

int main () {
  class Solution sol;
  vector <vector <int>> intervals = {{0,30},{5,10},{15,20}};
  int min = sol.minMeetingRooms(intervals);
  cout << "Min meeting roooms 1: " << min << endl;

  class Solution sol2;
  intervals = {{7,10},{2,4}};

  min = sol2.minMeetingRooms(intervals);
  cout << "Min meeting rooms 2: " << min << endl;

  return 0;
}
