
/*

122. Best Time to Buy and Sell Stock II

You are given an array prices for which the ith element is the price of a given
stock on day i.

Find the maximum profit you can achieve. You may complete as many transactions
as you like (i.e., buy one and sell one share of the stock multiple times).

Note: You may not engage in multiple transactions simultaneously (i.e., you must
sell the stock before you buy again).

You can buy/sell on the same day.

Example 1:
Input: prices = [7,1,5,3,6,4]
Output: 7
Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.

Example 2:
Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.

Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
engaging multiple transactions at the same time. You must sell before buying
again.

Example 3:
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e., max profit = 0.
 
*/

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (!len) return 0;
        
        int profit = 0;
        for (int i = 1; i < len; i++) {
            if (prices[i] > prices[i - 1])
                profit += prices[i] - prices[i - 1];
        }
        return profit;
    }
};


int main (void) {
  vector <int> vec = {7,1,5,3,6,4};
  Solution sol;
  int maxProfit = sol.maxProfit(vec);

  cout << "MaxProfit: " << maxProfit << endl;
  return 0;
}
