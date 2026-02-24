/*

Given a set of non-overlapping intervals, insert a new interval into the
intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times. 

Example 1:

Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:

Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

Example 3:

Input: intervals = [], newInterval = [5,7]
Output: [[5,7]]

Example 4:

Input: intervals = [[1,5]], newInterval = [2,3]
Output: [[1,5]]

Example 5:

Input: intervals = [[1,5]], newInterval = [2,7]
Output: [[1,7]]

*/

#include <vector>
#include <iostream>
#include <map>

using namespace std;


class Solution2 {
  // Map to store boundary points. Key is the time/coordinate, value is the change in active intervals.
  // +1 indicates an interval start, -1 indicates an interval end.
  // Using std::map keeps keys sorted, which is essential for the sweep-line algorithm.
  // Note: Since this is a member variable and not cleared, reusing this object for multiple
  // calls will accumulate state and produce incorrect results.
  map <int, int> calMap;
public:
  /*
   * Time Complexity: O(N log N), where N is the number of intervals.
   * - The code iterates through N+1 intervals (the original list plus the new one).
   * - For each interval, it performs two insertions into the `std::map`.
   * - Each map insertion takes O(log K) time, where K is the number of unique
   *   boundary points. In the worst case, K is proportional to N.
   * - Building the map of all boundary points therefore takes O(N log N) time.
   * - The final sweep through the map takes O(N) time.
   * - The dominant factor is the map construction, leading to O(N log N).
   *
   * Space Complexity: O(N)
   * - The `calMap` stores up to 2 * (N + 1) boundary points, resulting in O(N) space.
   */
  vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> res;
    
    // Step 1: Populate the map with boundaries of existing intervals.
    for (auto v :intervals) {
      calMap[v[0]]++; // Increment count at start
      calMap[v[1]]--; // Decrement count at end
    }
    
    // Step 2: Add the boundaries of the new interval to the map.
    // The map automatically handles sorting and aggregating changes at the same point.
    calMap[newInterval[0]]++;
    calMap[newInterval[1]]--;
    
    int count = 0; // Tracks the number of currently active (overlapping) intervals
    int start, end;
    
    // Step 3: Sweep through the sorted boundary points.
    for (auto e : calMap) {
      // If count is 0, we are starting a new merged interval.
      if (count == 0) {
        start = e.first;
      }
      
      // Apply the change at this boundary point.
      count += e.second;
      
      // If count returns to 0, the current merged interval has ended.
      if (count == 0) {
        end = e.first;
        res.push_back({start, end});
      }
    }
    return res;
  }
};

void print_vec(const std::vector<int>& vec) {
  cout << "[ ";
  for (auto x: vec) {
    cout << ' ' << x;
  }
  cout << " ]" << endl;
}

void print_vec_vec (vector<vector<int>>& vec) {
  cout << "[ " << endl;
  for (auto x: vec) {
    print_vec(x);
    cout << ' ' << endl;
  }
  cout << " ]" << endl;
}

int main () {
  class Solution2 sol;
  vector <vector <int>> intervals = {{1,3}, {2,6}, {8,10}, {15,18}};
  vector <int> newIntervals = { 9, 16 };
  vector <vector <int>> res;

  res = sol.insert(intervals, newIntervals);
  print_vec_vec(res);

  return 0;
}
