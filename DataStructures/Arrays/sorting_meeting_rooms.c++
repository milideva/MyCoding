#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 252: Meeting Rooms

  Problem Description:
  Given an array of meeting time `intervals` where 
  `intervals[i] = [starti, endi]`, determine if a person could 
  attend all meetings.

  Example 1:
  Input: intervals = [[0,30],[5,10],[15,20]]
  Output: false

  Algorithm: Sorting + Overlap Check
  1. Sort the intervals by their start times.
  2. Iterate through the sorted intervals.
  3. For each meeting `i` (starting from the second meeting):
     - Check if its start time is earlier than the end time of 
       meeting `i-1`.
     - `intervals[i].start < intervals[i-1].end`.
     - If yes, there is an overlap; return false.
  4. If no overlaps are found, return true.

  Complexity Analysis:
  - Time Complexity: O(N log N)
    Reason: Sorting takes O(N log N). The overlap check is O(N).
  - Space Complexity: O(1) or O(log N).
    Reason: Ignoring the space for sorting algorithm.

  Brute Force comparison:
  - Compare every pair of meetings for overlap.
  - Time: O(N^2).
  - Sorting reduces this to O(N log N).
*/

class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        if (intervals.size() <= 1) return true;

        // 1. Sort by start time
        sort(intervals.begin(), intervals.end());

        // 2. Check for overlaps
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] < intervals[i - 1][1]) {
                return false;
            }
        }
        return true;
    }
};

void test(const string& label, vector<vector<int>> input, bool expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    bool result = sol.canAttendMeetings(input);
    cout << "  Result: " << boolalpha << result << " (Expected: " << expected << ")" << endl;
}

int main() {
    test("Example 1", {{0, 30}, {5, 10}, {15, 20}}, false);
    test("Example 2", {{7, 10}, {2, 4}}, true);
    test("Adjacent", {{1, 5}, {5, 10}}, true);
    return 0;
}
