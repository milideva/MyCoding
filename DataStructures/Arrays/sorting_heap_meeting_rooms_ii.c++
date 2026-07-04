#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

/*
  LeetCode 253: Meeting Rooms II

  Problem Description:
  Given an array of meeting time intervals `intervals` where 
  `intervals[i] = [starti, endi]`, return the minimum number of 
  conference rooms required.

  Example 1:
  Input: intervals = [[0,30],[5,10],[15,20]]
  Output: 2

  Algorithm 1: Min-Heap
  1. Sort the intervals by start time.
  2. Use a Min-Heap to store the end times of meetings currently in 
     progress.
  3. For each meeting:
     - If the heap is not empty and the earliest meeting in the heap 
       ends before the current meeting starts (`heap.top() <= start`):
       - Remove that meeting from the heap (reuse the room).
     - Add the current meeting's end time to the heap.
  4. The size of the heap at the end is the number of rooms needed.

  Algorithm 2: Two-Pointer (Chronological Order)
  1. Extract all start times and end times into two separate arrays.
  2. Sort both arrays.
  3. Iterate through start times:
     - If `start[i] < end[j]`, a new room is needed.
     - Otherwise, a room is freed; increment `j`.

  Complexity Analysis:
  - Time Complexity: O(N log N)
    Reason: Sorting takes O(N log N). Heap operations also take 
    O(N log N) in total.
  - Space Complexity: O(N) to store the heap or separate arrays.

  Brute Force comparison:
  - Check every possible time point and count overlaps. 
  - Since time can be large, this is inefficient.
*/

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;

        // 1. Sort by start time
        sort(intervals.begin(), intervals.end());

        // 2. Min-Heap for end times
        priority_queue<int, vector<int>, greater<int>> minHeap;

        for (const auto& interval : intervals) {
            // If the earliest ending meeting has finished, reuse the room
            if (!minHeap.empty() && minHeap.top() <= interval[0]) {
                minHeap.pop();
            }
            // Add the current meeting's end time
            minHeap.push(interval[1]);
        }

        return minHeap.size();
    }
};

void test(const string& label, vector<vector<int>> input, int expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    int result = sol.minMeetingRooms(input);
    cout << "  Result: " << result << " (Expected: " << expected << ")" << endl;
}

int main() {
    test("Example 1", {{0, 30}, {5, 10}, {15, 20}}, 2);
    test("Example 2", {{7, 10}, {2, 4}}, 1);
    test("Overlapping ends", {{1, 10}, {2, 7}, {3, 19}, {8, 12}, {10, 20}}, 3);
    return 0;
}
