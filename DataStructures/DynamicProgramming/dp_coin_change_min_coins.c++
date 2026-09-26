#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <string>

using namespace std;

/*
  LeetCode 322: Coin Change (Minimum Coins)

  Problem Description:
  Given an integer array `coins` representing coins of different denominations 
  and an integer `amount`, return the fewest number of coins that you need to 
  make up that amount. If that amount of money cannot be made up by any 
  combination of the coins, return -1.

  =============================================================================
  METHOD 1: Bottom-Up Dynamic Programming (Tabulation)
  =============================================================================
  Intuition:
  We build the solution incrementally from the smallest subproblem (amount = 0)
  up to the target amount. For each subproblem `i`, we consider all available 
  coins and pick the coin that minimizes `1 + dp[i - coin]`.

  Complexity Analysis:
  - Time Complexity:
    - Best Case: O(Amount * N) where N is the number of coin denominations.
    - Average Case: O(Amount * N).
    - Worst Case: O(Amount * N).
  - Space Complexity: O(Amount) for the 1D table of size `Amount + 1`.

  =============================================================================
  METHOD 2: Top-Down Dynamic Programming (Memoization / DFS)
  =============================================================================
  Intuition:
  We recursively break down the problem by subtracting each coin's value 
  from the remaining amount. To avoid redundant computations (overlapping 
  subproblems), we cache the minimum coins needed for each amount in a memo table.

  Complexity Analysis:
  - Time Complexity:
    - Best Case: O(Amount * N).
    - Average Case: O(Amount * N).
    - Worst Case: O(Amount * N).
  - Space Complexity: O(Amount) due to the recursive call stack (of maximum depth `Amount`)
    and the memoization table of size `Amount + 1`.
*/

class Solution {
public:
    // Method 1: Bottom-Up Tabulation (Iterative, Space-Optimal)
    int minCoinsBottomUp(const vector<int>& coins, int amount) {
        // dp[i] stores the minimum coins needed to make amount i.
        // Initialize with amount + 1, representing infinity (since the maximum 
        // possible number of coins to form any amount is 'amount' if coin value is 1).
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0; // Base case: 0 coins are needed to make amount 0.

        // Compute the minimum coins for each sub-amount from 1 to 'amount'
        for (int i = 1; i <= amount; ++i) {
            for (int coin : coins) {
                if (i >= coin) {
                    // Min coins for amount i is the minimum of its current value
                    // and taking 1 coin plus the cost of the remaining amount (i - coin)
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        // If the value remains larger than amount, it's impossible to form this amount
        return (dp[amount] > amount) ? -1 : dp[amount];
    }

    // Method 2: Top-Down Memoization (Recursive, Intuitive)
    int minCoinsTopDown(const vector<int>& coins, int amount) {
        // Memoization table of size amount + 1, initialized with -2 (uncalculated status)
        vector<int> memo(amount + 1, -2);
        return solveTopDown(coins, amount, memo);
    }

private:
    int solveTopDown(const vector<int>& coins, int amount, vector<int>& memo) {
        if (amount == 0) return 0;   // Base case: 0 coins needed for amount 0
        if (amount < 0) return -1;   // Invalid amount, cannot be formed
        if (memo[amount] != -2) return memo[amount]; // Return cached result if already calculated

        int min_coins = INT_MAX;
        for (int coin : coins) {
            int sub_res = solveTopDown(coins, amount - coin, memo);
            // If the subproblem had a valid solution, consider this path
            if (sub_res >= 0 && sub_res < min_coins) {
                min_coins = sub_res + 1;
            }
        }

        // Cache the calculated result
        memo[amount] = (min_coins == INT_MAX) ? -1 : min_coins;
        return memo[amount];
    }
};

void run_test(const string& name, int expected, int actual) {
    bool passed = (expected == actual);
    cout << name << ": Expected: " << expected 
         << " Got: " << actual 
         << " " << (passed ? "PASS" : "FAIL") << endl;
}

int main() {
    Solution sol;

    // Test Case 1: Standard case
    vector<int> coins1 = {1, 2, 5};
    cout << "--- Testing Bottom-Up Tabulation ---" << endl;
    run_test("TC1 (Amount: 11)", 3, sol.minCoinsBottomUp(coins1, 11)); // 5+5+1
    run_test("TC2 (Amount: 3 with coin 2)", -1, sol.minCoinsBottomUp({2}, 3));
    run_test("TC3 (Amount: 0 with coin 1)", 0, sol.minCoinsBottomUp({1}, 0));

    cout << "\n--- Testing Top-Down Memoization ---" << endl;
    run_test("TC1 (Amount: 11)", 3, sol.minCoinsTopDown(coins1, 11)); // 5+5+1
    run_test("TC2 (Amount: 3 with coin 2)", -1, sol.minCoinsTopDown({2}, 3));
    run_test("TC3 (Amount: 0 with coin 1)", 0, sol.minCoinsTopDown({1}, 0));

    return 0;
}
