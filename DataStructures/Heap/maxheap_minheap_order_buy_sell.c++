#include <queue>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
  LeetCode 1801: Number of Orders in the Backlog

  Problem Description:
  You are given a 2D integer array `orders`, where each 
  `orders[i] = [pricei, amounti, orderTypei]` denotes that `amounti` 
  orders have been placed of type `orderTypei` at the price `pricei`. 
  `orderTypei` is 0 for BUY and 1 for SELL.

  - BUY order: Match with the smallest price SELL order in backlog. 
    If `sell_price <= buy_price`, they match and are removed.
  - SELL order: Match with the largest price BUY order in backlog. 
    If `buy_price >= sell_price`, they match and are removed.
  - If no match, add to backlog.

  Return the total amount of orders in the backlog modulo 10^9 + 7.

  Algorithm: Two Heaps (Max-Heap for BUY, Min-Heap for SELL)
  1. Use a Max-Heap to keep BUY orders (prioritize highest price).
  2. Use a Min-Heap to keep SELL orders (prioritize lowest price).
  3. For each incoming order:
     - If BUY: Check `sell_heap.top()`. If `sp <= bp`, match as many as possible.
     - If SELL: Check `buy_heap.top()`. If `bp >= sp`, match as many as possible.
     - Add any remaining amount of the incoming order to its respective heap.
  4. Sum all amounts in both heaps at the end.

  Complexity Analysis:
  - Time Complexity: O(N log N)
    Reason: We process N batches of orders. Each batch involves heap 
    operations (push/pop/top) which take O(log N).
  - Space Complexity: O(N)
    Reason: To store the backlog of orders in two heaps.

  Brute Force comparison:
  - Maintain a sorted list for both BUY and SELL orders.
  - Time Complexity: O(N^2) due to insertions into sorted lists.
  - The heap approach is significantly more efficient for large N (10^5).
*/

class Solution {
    struct Order {
        int price;
        int amount;
        bool operator<(const Order& other) const { return price < other.price; }
        bool operator>(const Order& other) const { return price > other.price; }
    };

public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        priority_queue<Order> buyBacklog; // Max-Heap
        priority_queue<Order, vector<Order>, greater<Order>> sellBacklog; // Min-Heap
        long totalBacklog = 0;
        const int MOD = 1e9 + 7;

        for (const auto& ord : orders) {
            int price = ord[0];
            int amount = ord[1];
            int type = ord[2];

            if (type == 0) { // BUY
                while (amount > 0 && !sellBacklog.empty() && sellBacklog.top().price <= price) {
                    Order sell = sellBacklog.top();
                    sellBacklog.pop();
                    int match = min(amount, sell.amount);
                    amount -= match;
                    sell.amount -= match;
                    totalBacklog -= match;
                    if (sell.amount > 0) {
                        sellBacklog.push(sell);
                    }
                }
                if (amount > 0) {
                    buyBacklog.push({price, amount});
                    totalBacklog += amount;
                }
            } else { // SELL
                while (amount > 0 && !buyBacklog.empty() && buyBacklog.top().price >= price) {
                    Order buy = buyBacklog.top();
                    buyBacklog.pop();
                    int match = min(amount, buy.amount);
                    amount -= match;
                    buy.amount -= match;
                    totalBacklog -= match;
                    if (buy.amount > 0) {
                        buyBacklog.push(buy);
                    }
                }
                if (amount > 0) {
                    sellBacklog.push({price, amount});
                    totalBacklog += amount;
                }
            }
        }
        return totalBacklog % MOD;
    }
};

void test(const string& label, vector<vector<int>> orders, int expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    int result = sol.getNumberOfBacklogOrders(orders);
    cout << "  Result: " << result << " (Expected: " << expected << ")" << endl;
}

int main() {
    test("Example 1", {{10, 5, 0}, {15, 2, 1}, {25, 1, 1}, {30, 4, 0}}, 6);
    test("Example 2", {{7, 1000000000, 1}, {15, 3, 0}, {5, 999999995, 0}, {5, 1, 1}}, 999999984);
    return 0;
}
