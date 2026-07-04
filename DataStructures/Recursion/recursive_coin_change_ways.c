#include <stdio.h>

/*
  LeetCode 518: Coin Change II (Number of Ways)

  Problem Description:
  You are given an integer array `coins` representing coins of 
  different denominations and an integer `amount`. Return the 
  number of combinations that make up that amount.

  Algorithm: Pure Recursion (Branching)
  1. Recursive function `countWays(amount, coin_index)`.
  2. For each coin, we have two choices:
     - Include the coin: `countWays(amount - coins[coin_index], coin_index)`
     - Exclude the coin: `countWays(amount, coin_index + 1)`
  3. Base Cases:
     - If `amount == 0`, return 1 (one way found).
     - If `amount < 0` or `coin_index == num_coins`, return 0.

  Complexity Analysis:
  - Time Complexity: O(2^(N + Amount))
    Reason: Exponential growth of the recursion tree. This is 
    extremely inefficient without memoization (Dynamic Programming).
  - Space Complexity: O(Amount) for recursion depth.
*/

int countWaysRecursive(int coins[], int numCoins, int amount, int index) {
    if (amount == 0) return 1;
    if (amount < 0 || index >= numCoins) return 0;

    // Choice 1: Use the current coin
    int include = countWaysRecursive(coins, numCoins, amount - coins[index], index);
    // Choice 2: Skip the current coin
    int exclude = countWaysRecursive(coins, numCoins, amount, index + 1);

    return include + exclude;
}

void test(int amount, int coins[], int n) {
    printf("Amount: %d, Coins: [ ", amount);
    for (int i = 0; i < n; i++) printf("%d ", coins[i]);
    int ways = countWaysRecursive(coins, n, amount, 0);
    printf("] -> Ways: %d\n", ways);
}

int main() {
    int c1[] = {1, 2, 5};
    test(5, c1, 3); // 4 ways: 5, 2+2+1, 2+1+1+1, 1+1+1+1+1

    int c2[] = {2};
    test(3, c2, 1); // 0 ways

    int c3[] = {10};
    test(10, c3, 1); // 1 way

    return 0;
}
