/*

Given an array of meeting time intervals where intervals[i] = [starti, endi],
determine if a person could attend all meetings.

Example 1:

Input: intervals = [[0,30],[5,10],[15,20]]
Output: false

Example 2:

Input: intervals = [[7,10],[2,4]]
Output: true

Constraints:
    0 <= intervals.length <= 104
    intervals[i].length == 2
    0 <= starti < endi <= 106
*/

/*
  LeetCode 252: Meeting Rooms

  Algorithm: Sweep-Line (using std::map)
  We treat every start and end time as an event on a timeline. A person can 
  attend all meetings if at any given time, the number of active meetings 
  does not exceed 1.

  Complexity Analysis:
  - Time Complexity: O(N log N)
    Reason: We insert N intervals into the map. Each insertion takes O(log N). 
    Traversing the map takes O(N).
  - Space Complexity: O(N)
    Reason: We store all N boundary points in the map.

  Alternative Approaches:
  - Sorting (Standard): Sort the intervals by start time. A person can 
    attend all if `intervals[i][1] <= intervals[i+1][0]` for all i.
    - Time: O(N log N), Space: O(1) or O(log N) depending on sort.
    - Comparison: Sorting is generally preferred for this simple check as 
      it uses less space than a map.

  Brute Force Approach:
  - Compare every pair of meetings [i, j]. Check if they overlap using:
    `max(start_i, start_j) < min(end_i, end_j)`.
  - Time Complexity: O(N^2).
  - Comparison: This is significantly slower for large inputs (N=10^4). 
    Sorting or Sweep-line is the optimized standard.
*/

#include <vector>
#include <iostream>
#include <map>
using namespace std;

class Solution {
  map <int, int> calMap;
  bool canAdd (int maxConflicts) {
    int count = 0;
    for (auto [t, cnt] : calMap) {
      count += cnt;
      if (count > maxConflicts) 
        return false;
    }
    return true; 
  }
public:
  bool canAttendMeetings(vector<vector<int>>& intervals) {
    if (intervals.size() <= 1) return true;
    
    for (auto v :intervals) {
      calMap[v[0]]++;
      calMap[v[1]]--;
    }
    
    int maxConflicts = 1;
    return canAdd(maxConflicts);
  }
};

int main () {
  class Solution sol;
  vector <vector <int>> intervals = {{0,30},{5,10},{15,20}};
  bool can = sol.canAttendMeetings(intervals);
  cout << "Can attend 1: " << can << endl;
  
  class Solution sol2;
  intervals = {{7,10},{2,4}};
  
  can = sol2.canAttendMeetings(intervals);
  cout << "Can attend 2: " << can << endl;
  
  return 0;
}
