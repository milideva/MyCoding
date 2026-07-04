#include <stdio.h>

/*
  Problem: Coin Change (Greedy Version)

  Problem Description:
  Form a target sum of money using as few coins as possible from a 
  given set of denominations.

  Algorithm: Largest Denomination First
  1. Sort denominations in descending order.
  2. For each denomination `d`:
     - Number of coins needed: `count = amount / d`.
     - Remaining amount: `amount = amount % d`.
     - Total coins += `count`.

  Note: 
  The greedy approach only works for certain "canonical" coin systems 
  (like the US coin system: 1, 5, 10, 25).
  It fails for others (e.g., coins {1, 3, 4} for sum 6: 
  Greedy gives 4+1+1 (3 coins), while Optimal is 3+3 (2 coins)).

  Complexity Analysis:
  - Time Complexity: O(N) where N is the number of denominations.
  - Space Complexity: O(1).
*/

int minCoinsGreedy(int coins[], int n, int amount) {
    int totalCoins = 0;
    // Assume coins are already sorted descending
    for (int i = 0; i < n; i++) {
        if (amount >= coins[i]) {
            int count = amount / coins[i];
            totalCoins += count;
            amount %= coins[i];
        }
    }
    return (amount == 0) ? totalCoins : -1;
}

void test(int amount, int coins[], int n) {
    printf("Amount: %d -> Coins needed: %d\n", amount, minCoinsGreedy(coins, n, amount));
}

int main() {
    int us_coins[] = {100, 50, 25, 10, 5, 1};
    test(99, us_coins, 6); // 1*50 + 1*25 + 2*10 + 4*1 = 8 coins

    int non_canonical[] = {4, 3, 1};
    test(6, non_canonical, 3); // Greedy: 4+1+1 (3), Optimal: 3+3 (2)
    
    return 0;
}
