#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

/*
  LeetCode 759: Employee Free Time

  Problem Description:
  We are given a list `schedule` of employees, which represents the 
  working time for each employee. Each employee has a list of 
  non-overlapping intervals, and these intervals are in sorted order.

  Return the list of finite intervals representing common, 
  positive-length free time for all employees, also in sorted order.

  Example 1:
  Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
  Output: [[3,4]]

  Algorithm 1: Flatten and Sort
  1. Collect all intervals from all employees into a single list.
  2. Sort the list by start time.
  3. Merge overlapping intervals.
  4. The gaps between the merged intervals represent the common 
     free time.

  Algorithm 2: Min-Heap (K-Way Merge) - Optimized
  1. Use a Min-Heap to store the first interval of each employee.
  2. The heap stores `(start_time, employee_index, interval_index)`.
  3. While the heap is not empty:
     - Pop the earliest interval.
     - Check for gap between the `last_end` time and the `current_start`.
     - Update `last_end`.
     - Push the next interval of the same employee into the heap.
  
  Complexity Analysis:
  - Time Complexity: O(N log N) for flatten/sort, or O(N log K) for 
    heap-based merge (where K is the number of employees).
  - Space Complexity: O(N) to store intervals, or O(K) for the heap.

  Brute Force comparison:
  - Check every possible time unit for availability. 
  - Time: O(MaxTime * K), which is inefficient for large time ranges.
*/

class Interval {
public:
    int start;
    int end;
    Interval(int _start, int _end) : start(_start), end(_end) {}
};

class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        vector<Interval> result;
        vector<Interval> all;

        // Flatten all intervals (Algorithm 1)
        for (const auto& emp : schedule) {
            for (const auto& interval : emp) {
                all.push_back(interval);
            }
        }

        sort(all.begin(), all.end(), [](const Interval& a, const Interval& b) {
            return a.start < b.start;
        });

        int lastEnd = all[0].end;
        for (size_t i = 1; i < all.size(); ++i) {
            if (all[i].start > lastEnd) {
                result.emplace_back(lastEnd, all[i].start);
            }
            lastEnd = max(lastEnd, all[i].end);
        }

        return result;
    }
};

void test(const string& label, vector<vector<Interval>> schedule) {
    cout << "Testing: " << label << endl;
    Solution sol;
    vector<Interval> result = sol.employeeFreeTime(schedule);
    cout << "  Free Time: [ ";
    for (const auto& interval : result) {
        cout << "[" << interval.start << "," << interval.end << "] ";
    }
    cout << "]" << endl;
}

int main() {
    test("Example 1", {{{1, 2}, {5, 6}}, {{1, 3}}, {{4, 10}}});
    test("Example 2", {{{1, 3}, {6, 7}}, {{2, 4}}, {{2, 5}, {9, 12}}});
    return 0;
}
