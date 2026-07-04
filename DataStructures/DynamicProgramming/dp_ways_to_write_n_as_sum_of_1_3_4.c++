#include <vector>
#include <iostream>

using namespace std;

/*
  Problem: Ways to write N as sum of {1, 3, 4}

  Problem Description:
  Given an integer `n`, find the number of different ways to write 
  `n` as a sum of 1, 3, and 4. Different orders are counted as 
  different ways.

  Algorithm: Dynamic Programming (Bottom-Up)
  1. Let `dp[i]` be the number of ways to sum up to `i`.
  2. Recurrence: `dp[i] = dp[i-1] + dp[i-3] + dp[i-4]`.
  3. Base Cases:
     - `dp[0] = 1`
     - `dp[1] = 1`
     - `dp[2] = 1`
     - `dp[3] = 2` (1+1+1, 3)

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(N) or O(1) with sliding window optimization.
*/

class Solution {
public:
    long long countWays(int n) {
        if (n < 0) return 0;
        if (n <= 2) return 1;
        if (n == 3) return 2;

        vector<long long> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 1;
        dp[3] = 2;

        for (int i = 4; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 3] + dp[i - 4];
        }
        return dp[n];
    }

    long long countWaysOptimized(int n) {
        if (n < 0) return 0;
        if (n <= 2) return 1;
        if (n == 3) return 2;

        long long d0 = 1, d1 = 1, d2 = 1, d3 = 2, di;
        for (int i = 4; i <= n; i++) {
            di = d3 + d1 + d0; // dp[i-1] + dp[i-3] + dp[i-4]
            d0 = d1;
            d1 = d2;
            d2 = d3;
            d3 = di;
        }
        return di;
    }
};

void test(int n, long long expected) {
    Solution sol;
    long long result = sol.countWays(n);
    cout << "N: " << n << " -> Ways: " << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    test(5, 6);
    test(7, 15);
    test(10, 64);
    return 0;
}
