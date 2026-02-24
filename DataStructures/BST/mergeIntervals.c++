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
   * This function merges overlapping intervals using a sweep-line algorithm.
   * The core idea is to treat the start and end points of all intervals as events
   * on a timeline. We process these events in chronological order.
   *
   * 1. Boundary Counting: We iterate through all input intervals and use a map (`calMap`)
   *    to store the changes at each boundary. For an interval [start, end], we
   *    increment the count at `start` and decrement the count at `end`.
   *
   * 2. Sweeping the Timeline: We then iterate through the sorted map. A running `count`
   *    tracks the number of currently active/overlapping intervals.
   *    - When we encounter a new potential merged interval (i.e., when the `count` was 0),
   *      we record its start time.
   *    - We update the `count` with the value from the map.
   *    - When the `count` drops back to 0, it signifies the end of a merged interval.
   *      We then add the [start, end] pair to our result.
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
