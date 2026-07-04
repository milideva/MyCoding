#include <vector>
#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

/*
  LeetCode 621: Task Scheduler

  Problem Description:
  Given a characters array `tasks`, representing the tasks a CPU needs 
  to do, where each letter represents a different task. Tasks could 
  be done in any order. Each task is done in one unit of time. For 
  each unit of time, the CPU could complete either one task or just 
  be idle.

  However, there is a non-negative integer `n` that represents the 
  cooldown period between two same tasks (the same letter in the 
  array), that is that there must be at least `n` units of time 
  between any two same tasks.

  Return the least number of units of times that the CPU will take 
  to finish all the given tasks.

  Algorithm: Greedy with Max-Heap
  1. Count the frequency of each task using a hash map.
  2. Use a Max-Heap to store frequencies. We want to prioritize tasks 
     with the highest remaining frequency to minimize idle time.
  3. In each "cycle" of length `n + 1`:
     - Try to pick up to `n + 1` unique tasks from the max-heap.
     - For each task picked, decrement its frequency.
     - Keep track of used tasks that still have remaining work in a 
       temporary list.
     - If we picked `k` tasks and still have more work overall, but 
       exhausted unique tasks for this cycle, the CPU stays idle 
       for `(n + 1) - k` units.
  4. Push back the remaining tasks into the max-heap and repeat.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: N is the total number of tasks. Although we use a heap, 
    the number of unique tasks is constant (at most 26 letters). 
    Each task is pushed and popped a constant number of times.
  - Space Complexity: O(1)
    Reason: The hash map and heap store at most 26 entries.

  Alternative Approaches (Mathematical):
  - Logic: The total time is primarily determined by the most 
    frequent task(s). If `max_freq` is the highest frequency, 
    the structure looks like: `(TaskA, ..., TaskA, ..., TaskA)`.
    There are `max_freq - 1` gaps, each requiring `n + 1` slots. 
    The last occurrence of TaskA and any other tasks with the same 
    `max_freq` don't need a cooling period afterward.
  - Formula: `(max_freq - 1) * (n + 1) + (number of tasks with max_freq)`.
  - Comparison: The mathematical formula is O(N) time and O(1) space, 
    and much simpler to implement.
*/

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> counts;
        for (char t : tasks) counts[t]++;

        priority_queue<int> pq;
        for (auto const& [task, count] : counts) pq.push(count);

        int totalTime = 0;
        while (!pq.empty()) {
            vector<int> remaining;
            int cycle = n + 1;
            int tasksInCycle = 0;

            while (cycle > 0 && !pq.empty()) {
                int freq = pq.top();
                pq.pop();
                if (freq > 1) {
                    remaining.push_back(freq - 1);
                }
                tasksInCycle++;
                cycle--;
            }

            for (int r : remaining) pq.push(r);

            // If pq is empty, we don't add idle time for the last cycle
            totalTime += pq.empty() ? tasksInCycle : (n + 1);
        }
        return totalTime;
    }
};

void test(const string& label, vector<char> tasks, int n, int expected) {
    cout << "Testing: " << label << " (n=" << n << ")" << endl;
    Solution sol;
    int result = sol.leastInterval(tasks, n);
    cout << "  Result: " << result << " (Expected: " << expected << ")" << endl;
}

int main() {
    test("Example 1", {'A','A','A','B','B','B'}, 2, 8);
    test("Example 2", {'A','A','A','B','B','B'}, 0, 6);
    test("Example 3", {'A','A','A','A','A','A','B','C','D','E','F','G'}, 2, 16);
    return 0;
}
