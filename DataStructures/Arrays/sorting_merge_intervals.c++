#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 56: Merge Intervals

  Problem Description:
  Given an array of `intervals` where `intervals[i] = [starti, endi]`, 
  merge all overlapping intervals, and return an array of the 
  non-overlapping intervals that cover all the intervals in the input.

  Example 1:
  Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
  Output: [[1,6],[8,10],[15,18]]

  Algorithm: Sorting + Single Pass
  1. Sort the intervals based on their start times.
  2. Maintain a `result` vector of merged intervals.
  3. Initially, add the first interval to the `result`.
  4. For each subsequent interval `curr`:
     - Let `last` be the last interval in `result`.
     - If `curr.start <= last.end`, they overlap. Update `last.end` 
       to `max(last.end, curr.end)`.
     - Otherwise, they don't overlap. Add `curr` to `result`.

  Complexity Analysis:
  - Time Complexity: O(N log N)
    Reason: Sorting takes O(N log N), and merging takes O(N).
  - Space Complexity: O(log N) or O(N) auxiliary space.
    Reason: To store the sorted intervals (if not sorting in-place) 
    and for the sorting algorithm's recursion stack.

  Brute Force comparison:
  - Represent intervals as nodes in a graph and find connected components.
  - Time: O(N^2), Space: O(N^2).
  - Sorting provides the most efficient approach for this problem.
*/

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};

        // 1. Sort by start time
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> merged;
        merged.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); ++i) {
            // 2. Check for overlap with the last merged interval
            if (intervals[i][0] <= merged.back()[1]) {
                merged.back()[1] = max(merged.back()[1], intervals[i][1]);
            } else {
                merged.push_back(intervals[i]);
            }
        }
        return merged;
    }
};

void test(const string& label, vector<vector<int>> input) {
    cout << "Testing: " << label << endl;
    Solution sol;
    vector<vector<int>> result = sol.merge(input);
    cout << "  Result: [ ";
    for (const auto& v : result) cout << "[" << v[0] << "," << v[1] << "] ";
    cout << "]" << endl;
}

int main() {
    test("Example 1", {{1,3}, {2,6}, {8,10}, {15,18}});
    test("Adjacent", {{1,4}, {4,5}});
    test("Nested", {{1,10}, {2,3}, {4,5}});
    test("Empty", {});
    return 0;
}
