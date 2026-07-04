#include <stdio.h>
#include <string.h>

/*
  Problem: Climbing Stairs (1, 2, or 3 steps)

  Problem Description:
  A child is running up a staircase with `n` steps and can hop 
  either 1, 2, or 3 steps at a time. Implement a function to count 
  how many possible ways the child can run up the stairs.

  Algorithm: Dynamic Programming (Bottom-Up)
  1. Let `dp[i]` be the number of ways to reach step `i`.
  2. Base Cases:
     - `dp[0] = 1` (Start)
     - `dp[1] = 1`
     - `dp[2] = 2` (1+1, 2)
  3. Recursive Step: `dp[i] = dp[i-1] + dp[i-2] + dp[i-3]`.
  4. Optimization: Only keep the last 3 values to save space.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(1) with optimization.
*/

long long countWays(int n) {
    if (n < 0) return 0;
    if (n == 0 || n == 1) return 1;
    if (n == 2) return 2;

    long long a = 1; // dp[0]
    long long b = 1; // dp[1]
    long long c = 2; // dp[2]
    long long d;

    for (int i = 3; i <= n; i++) {
        d = a + b + c;
        a = b;
        b = c;
        c = d;
    }
    return c;
}

void test(int n) {
    printf("Steps: %d -> Ways: %lld\n", n, countWays(n));
}

int main() {
    test(3); // 4
    test(4); // 7
    test(5); // 13
    test(10); // 274
    return 0;
}
