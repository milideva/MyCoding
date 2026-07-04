#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

/*
  LeetCode 1423: Maximum Points You Can Obtain from Cards

  Problem Description:
  There are several cards arranged in a row. In each step, you can 
  take one card from either the beginning or the end of the row. 
  You must take exactly `k` cards. Return the maximum score you can 
  obtain.

  Algorithm: Sliding Window (Inverse Approach)
  1. Total number of cards is `n`. If we take `k` cards from the ends, 
     we leave `n - k` contiguous cards in the middle.
  2. To maximize the score of `k` cards, we must MINIMIZE the sum of 
     the `n - k` cards in the middle.
  3. Use a sliding window of size `n - k` to find the minimum 
     subarray sum.
  4. The result is `TotalSum - MinSubarraySum`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Single pass to calculate total sum and one pass for 
    sliding window.
  - Space Complexity: O(1) auxiliary space.
*/

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int windowSize = n - k;
        
        int totalSum = 0;
        for (int x : cardPoints) totalSum += x;
        
        if (k == n) return totalSum;

        int currentWindowSum = 0;
        for (int i = 0; i < windowSize; i++) {
            currentWindowSum += cardPoints[i];
        }

        int minWindowSum = currentWindowSum;
        for (int i = windowSize; i < n; i++) {
            currentWindowSum += cardPoints[i] - cardPoints[i - windowSize];
            minWindowSum = min(minWindowSum, currentWindowSum);
        }

        return totalSum - minWindowSum;
    }
};

void test(vector<int> cardPoints, int k, int expected) {
    Solution sol;
    int result = sol.maxScore(cardPoints, k);
    cout << "K: " << k << " -> Max Score: " << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    test({1, 2, 3, 4, 5, 6, 1}, 3, 12);
    test({2, 2, 2}, 2, 4);
    test({9, 7, 7, 9, 7, 7, 9}, 7, 55);
    test({1, 1000, 1}, 1, 1);
    test({1, 79, 80, 1, 1, 1, 200, 1}, 3, 202);
    return 0;
}
