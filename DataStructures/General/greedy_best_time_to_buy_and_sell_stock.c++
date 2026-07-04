#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

/*
  LeetCode 121: Best Time to Buy and Sell Stock

  Problem Description:
  You are given an array `prices` where `prices[i]` is the price of 
  a given stock on the `i`-th day. You want to maximize your profit 
  by choosing a single day to buy one stock and choosing a different 
  day in the future to sell that stock.

  Algorithm: One Pass (Greedy)
  1. Maintain a `minPrice` variable initialized to a very large value.
  2. Maintain a `maxProfit` variable initialized to 0.
  3. Iterate through the `prices` array:
     - Update `minPrice = min(minPrice, price)`.
     - Update `maxProfit = max(maxProfit, price - minPrice)`.
  4. Return `maxProfit`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the array exactly once.
  - Space Complexity: O(1) auxiliary space.
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = INT_MAX;
        int maxProfit = 0;
        for (int p : prices) {
            if (p < minPrice) minPrice = p;
            else maxProfit = max(maxProfit, p - minPrice);
        }
        return maxProfit;
    }
};

void test(vector<int> prices, int expected) {
    Solution sol;
    int result = sol.maxProfit(prices);
    cout << "Max Profit: " << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    test({7, 1, 5, 3, 6, 4}, 5);
    test({7, 6, 4, 3, 1}, 0);
    return 0;
}
