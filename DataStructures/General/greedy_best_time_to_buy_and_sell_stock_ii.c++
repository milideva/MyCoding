#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 122: Best Time to Buy and Sell Stock II

  Problem Description:
  Find the maximum profit you can achieve by buying and selling 
  a stock multiple times. You must sell the stock before you buy 
  it again.

  Algorithm: Simple Greedy (Sum of Positives)
  1. Iterate through the array starting from the second element.
  2. If the current price is higher than the previous day's price:
     - The difference `prices[i] - prices[i-1]` is profit we can capture.
     - Add this difference to the total profit.
  3. This effectively captures every upward slope in the price graph.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(1) auxiliary space.
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        for (size_t i = 1; i < prices.size(); i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }
};

void test(vector<int> prices, int expected) {
    Solution sol;
    int result = sol.maxProfit(prices);
    cout << "Max Profit (II): " << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    test({7, 1, 5, 3, 6, 4}, 7); // (5-1) + (6-3) = 7
    test({1, 2, 3, 4, 5}, 4);    // 4-1 = 4 (or 1+1+1+1)
    test({7, 6, 4, 3, 1}, 0);
    return 0;
}
