#include <stdio.h>
#include <string.h>

/*
  Problem: Fibonacci Numbers (DP Comparison)

  Description:
  Compute the n-th Fibonacci number using various approaches:
  1. Recursive (Naive)
  2. Memoization (Top-Down)
  3. Tabulation (Bottom-Up)
  4. Space-Optimized DP

  Complexity Analysis:
  - Naive Recursive: O(2^N) time, O(N) space.
  - Top-Down / Bottom-Up: O(N) time, O(N) space.
  - Space-Optimized: O(N) time, O(1) space.
*/

// 1. Naive Recursive
unsigned int fibNaive(unsigned int n) {
    if (n < 2) return n;
    return fibNaive(n - 1) + fibNaive(n - 2);
}

// 2. Top-Down (Memoization)
unsigned int fibMemoHelper(unsigned int n, unsigned int memo[]) {
    if (n < 2) return n;
    if (memo[n] != 0) return memo[n];
    memo[n] = fibMemoHelper(n - 1, memo) + fibMemoHelper(n - 2, memo);
    return memo[n];
}

unsigned int fibMemo(unsigned int n) {
    unsigned int memo[100] = {0};
    return fibMemoHelper(n, memo);
}

// 3. Bottom-Up (Tabulation)
unsigned int fibTabulation(unsigned int n) {
    if (n < 2) return n;
    unsigned int f[n + 1];
    f[0] = 0; f[1] = 1;
    for (int i = 2; i <= n; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    return f[n];
}

// 4. Space-Optimized DP
unsigned int fibOptimized(unsigned int n) {
    if (n < 2) return n;
    unsigned int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

void test(unsigned int n) {
    printf("Fibonacci(%u):\n", n);
    printf("  Naive:     %u\n", (n < 40) ? fibNaive(n) : 0); // Avoid hang
    printf("  Memo:      %u\n", fibMemo(n));
    printf("  Tabular:   %u\n", fibTabulation(n));
    printf("  Optimized: %u\n\n", fibOptimized(n));
}

int main() {
    test(10);
    test(14);
    return 0;
}
