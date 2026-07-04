#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 77: Combinations

  Problem Description:
  Given two integers `n` and `k`, return all possible combinations of 
  `k` numbers out of the range `[1, n]`.

  Example 1:
  Input: n = 4, k = 2
  Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]

  Algorithm: Backtracking (DFS)
  1. Use a recursive function `backtrack(start, current_combination)`.
  2. Base Case: If `current_combination.size() == k`, add to result.
  3. Recursive Step:
     - Iterate from `i = start` to `n`.
     - Pruning optimization: Only iterate up to `n - (k - size) + 1` 
       to ensure enough elements remain.
     - Add `i` to `current_combination`.
     - Recurse: `backtrack(i + 1, current_combination)`.
     - Backtrack: Remove `i` from `current_combination`.

  Complexity Analysis:
  - Time Complexity: O(k * C(n, k))
    Reason: There are C(n, k) combinations, and each takes O(k) 
    to copy into the result.
  - Space Complexity: O(k) for the recursion stack and current 
    combination storage.
*/

class Solution {
    void backtrack(int n, int k, int start, vector<int>& curr, vector<vector<int>>& result) {
        if (curr.size() == k) {
            result.push_back(curr);
            return;
        }

        // Optimization: i <= n - (k - curr.size()) + 1
        for (int i = start; i <= n; i++) {
            curr.push_back(i);
            backtrack(n, k, i + 1, curr, result);
            curr.pop_back(); // Backtrack
        }
    }

public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> curr;
        backtrack(n, k, 1, curr, result);
        return result;
    }
};

void test(int n, int k) {
    cout << "Testing: n=" << n << ", k=" << k << endl;
    Solution sol;
    vector<vector<int>> result = sol.combine(n, k);
    cout << "  Result: [ ";
    for (const auto& v : result) {
        cout << "[";
        for (size_t i = 0; i < v.size(); i++) cout << v[i] << (i == v.size() - 1 ? "" : ",");
        cout << "] ";
    }
    cout << "]" << endl;
}

int main() {
    test(4, 2);
    test(1, 1);
    return 0;
}
