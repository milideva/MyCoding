/*

Given an array of intervals where intervals[i] = [starti, endi], merge all
overlapping intervals, and return an array of the non-overlapping intervals that
cover all the intervals in the input.

 

Example 1:

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].

Example 2:

Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
*/

#include <vector>
#include <iostream>
#include <map>
using namespace std;

class Solution {
  // A map to store the boundary points of the intervals.
  // The key is the time point (start or end of an interval).
  // The value is the change in the number of active intervals at that time.
  // +1 for a start point, -1 for an end point.
  // Note: This map is a member variable and is not cleared between calls to merge(),
  // which can lead to incorrect results if the same Solution object is used for multiple,
  // independent merge operations.
  map <int, int> calMap;
public:
  
  /*
   * LeetCode 56: Merge Intervals
   *
   * Algorithm: Sweep-Line (using std::map)
   * Treat start and end points as events. A merged interval begins when 
   * the active interval count moves from 0 to 1, and ends when it 
   * returns to 0.
   *
   * Complexity Analysis:
   * - Time Complexity: O(N log N)
   *   Reason: Map insertions take O(log N). Sweep takes O(N).
   * - Space Complexity: O(N)
   *   Reason: Map storage for boundary points.
   *
   * Comparison:
   * - Sorting Approach (Standard): Sort intervals by start time. Iterate 
   *   and merge current with previous if `curr.start <= prev.end`.
   *   - Time: O(N log N), Space: O(1) or O(log N).
   *   - Advantage: Generally faster in practice than map due to 
   *     cache-friendly array access.
   *
   * Brute Force Approach:
   * - While there are overlapping intervals:
   *   1. Find two overlapping intervals [a, b] and [c, d].
   *   2. Replace them with [min(a, c), max(b, d)].
   * - Time Complexity: O(N^2) or worse depending on finding logic.
   * - Comparison: Quadratic time is too slow for large interval lists. 
   *   Sweep-line/Sorting reduces this to linearithmic time.
   */
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    // If there are 0 or 1 intervals, no merging is needed.
    int len = intervals.size();
    if (len <=1) return intervals;
    
    // Step 1: Populate the map with boundary counts.
    // For each interval [start, end], increment the count at the start time
    // and decrement it at the end time.
    for (auto v :intervals) {
      calMap[v[0]]++;
      calMap[v[1]]--;
    }
    
    vector<vector<int>> result;
    int count = 0;    // Tracks the number of overlapping intervals.
    int start, end;

    // Step 2: Sweep through the timeline (the sorted map keys).
    for (auto e : calMap) {
      // If count is 0, it means we are at the beginning of a new non-overlapping
      // or merged interval. Record the start time.
      if (count == 0) {
        start = e.first;
      } 
      // Update the active interval count by adding the change at the current time point.
      count += e.second;
      // If count becomes 0, it means a merged interval has just ended.
      // Record the end time and add the [start, end] interval to the result.
      if (count == 0) {
        end = e.first;
        result.push_back({start, end});  
      }
    }
    
    return result;
  }
};

// Helper function to print a vector of integers.
void print_vec(const std::vector<int>& vec) {
  cout << "[ ";
  for (auto x: vec) {
    cout << ' ' << x;
  }
  cout << " ]" << endl;
}

// Helper function to print a vector of vectors of integers.
void print_vec_vec (vector<vector<int>>& vec) {
  cout << "[ " << endl;
  for (auto x: vec) {
    print_vec(x);
    cout << ' ' << endl;
  }
  cout << " ]" << endl;
}

// Main function to test the Solution.
int main () {
  class Solution sol;
  vector <vector <int>> intervals = {{1,3}, {2,6}, {8,10}, {15,18}};

  vector <vector <int>> res;

  res = sol.merge(intervals);
  print_vec_vec(res);

  // Second test case. Add more inervals.
  intervals = {{7,10},{2,4}};
  res = sol.merge(intervals);
  print_vec_vec(res);

  return 0;
}
