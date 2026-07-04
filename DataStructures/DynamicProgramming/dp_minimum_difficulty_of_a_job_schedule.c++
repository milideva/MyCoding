#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

/*
  LeetCode 1335: Minimum Difficulty of a Job Schedule

  Problem Description:
  You want to schedule a list of jobs in `d` days. You must finish 
  at least one job every day. The difficulty of a job schedule 
  is the sum of difficulties of each day. The difficulty of a day 
  is the maximum difficulty of a job done that day. 
  Find the minimum difficulty to schedule all jobs.

  Algorithm: Dynamic Programming (Top-Down with Memoization)
  1. Let `dp(index, daysLeft)` be the minimum difficulty to schedule 
     jobs from `index` to `n-1` in `daysLeft` days.
  2. Base Case: If `daysLeft == 1`, return the maximum difficulty 
     among remaining jobs.
  3. Recursive Step:
     - Try finishing `j` jobs on the first day, where `j` ranges 
       from 1 to `n - index - (daysLeft - 1)`.
     - `currentDayMax = max(jobDifficulty[index...index+j-1])`.
     - `res = min(res, currentDayMax + dp(index+j, daysLeft-1))`.
  4. Pruning: If total jobs < `d`, return -1.

  Complexity Analysis:
  - Time Complexity: O(N^2 * D)
    Reason: There are N * D states, and each state takes O(N) to 
    compute.
  - Space Complexity: O(N * D) for memoization table.
*/

class Solution {
    int n;
    int memo[301][11];

    int dp(const vector<int>& jd, int idx, int d) {
        if (d == 1) {
            int max_val = 0;
            for (int i = idx; i < n; i++) max_val = max(max_val, jd[i]);
            return max_val;
        }
        if (memo[idx][d] != -1) return memo[idx][d];

        int res = 1e9;
        int daily_max = 0;
        // Leave at least d-1 jobs for the remaining d-1 days
        for (int i = idx; i <= n - d; i++) {
            daily_max = max(daily_max, jd[i]);
            res = min(res, daily_max + dp(jd, i + 1, d - 1));
        }
        return memo[idx][d] = res;
    }

public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        n = jobDifficulty.size();
        if (n < d) return -1;
        memset(memo, -1, sizeof(memo));
        return dp(jobDifficulty, 0, d);
    }
};

void test(vector<int> jd, int d, int expected) {
    Solution sol;
    int result = sol.minDifficulty(jd, d);
    cout << "Min Difficulty: " << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    test({6, 5, 4, 3, 2, 1}, 2, 7);
    test({9, 9, 9}, 4, -1);
    test({1, 1, 1}, 3, 3);
    test({7, 1, 7, 1, 7, 1}, 3, 15);
    return 0;
}
