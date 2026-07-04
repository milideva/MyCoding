#include <stdio.h>
#include <limits.h>

/*
  LeetCode 322: Coin Change (Minimum Coins)

  Problem Description:
  Given an integer array `coins` representing coins of different 
  denominations and an integer `amount`, return the fewest number of 
  coins that you need to make up that amount. If not possible, return -1.

  Algorithm: Dynamic Programming (Bottom-Up)
  1. Let `dp[i]` be the minimum coins needed for amount `i`.
  2. Base Case: `dp[0] = 0`.
  3. Initialize `dp` array with `amount + 1` (a value larger than any 
     possible result).
  4. For `i` from 1 to `amount`:
     - For each `coin`:
       - If `i >= coin`:
         - `dp[i] = min(dp[i], dp[i - coin] + 1)`.
  5. Return `dp[amount]` if it's less than `amount + 1`, else -1.

  Complexity Analysis:
  - Time Complexity: O(Amount * N) where N is number of coins.
  - Space Complexity: O(Amount).
*/

int minCoins(int coins[], int n, int amount) {
    int dp[amount + 1];
    for (int i = 0; i <= amount; i++) dp[i] = amount + 1;
    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= coins[j]) {
                int res = dp[i - coins[j]] + 1;
                if (res < dp[i]) dp[i] = res;
            }
        }
    }
    return (dp[amount] > amount) ? -1 : dp[amount];
}

void test(int amount, int coins[], int n, int expected) {
    int result = minCoins(coins, n, amount);
    printf("Amount: %d -> Min Coins: %d", amount, result);
    if (result == expected) printf(" [PASS]\n");
    else printf(" [FAIL] Expected: %d\n", expected);
}

int main() {
    int c1[] = {1, 2, 5};
    test(11, c1, 3, 3); // 5+5+1

    int c2[] = {2};
    test(3, c2, 1, -1);

    int c3[] = {1};
    test(0, c3, 1, 0);

    return 0;
}
