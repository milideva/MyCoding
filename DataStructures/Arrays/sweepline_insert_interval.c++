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
   * LeetCode 57: Insert Interval
   *
   * Algorithm: Sweep-Line (using std::map)
   * We use a map to store the net change in active intervals at each 
   * boundary point. +1 for start, -1 for end. Traversing the sorted map 
   * allows us to merge all overlapping segments.
   *
   * Complexity Analysis:
   * - Time Complexity: O(N log N)
   *   Reason: Each of the N intervals is inserted into the Red-Black Tree 
   *   (std::map). Each insertion is O(log N).
   * - Space Complexity: O(N)
   *   Reason: Storing 2N boundary points in the map.
   *
   * Comparison:
   * - Greedy Linear Scan (Optimized): Since the input is already sorted, 
   *   we can solve this in O(N) time and O(1) extra space (excluding result) 
   *   by iterating once and merging only the intervals that overlap with 
   *   the 'newInterval'.
   * - Brute Force: Append the new interval to the list, sort all intervals 
   *   by start time (O(N log N)), then perform a standard O(N) merge pass. 
   *   The sweep-line approach is essentially a variation of this but uses 
   *   a tree to handle sorting.
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
