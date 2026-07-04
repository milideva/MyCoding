#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
  LeetCode 22: Generate Parentheses

  Problem Description:
  Given `n` pairs of parentheses, write a function to generate all 
  combinations of well-formed parentheses.

  Example 1:
  Input: n = 3
  Output: ["((()))","(()%)","(())()","()(())","()()()"]

  Algorithm: Backtracking with Constraints
  1. Maintain counts of `open` and `close` parentheses used.
  2. Recursive function `backtrack(current_string, open_count, close_count)`.
  3. Base Case: If `current_string.length() == 2 * n`, add to result.
  4. Decision Rule:
     - If `open_count < n`, we can always add an '('.
     - If `close_count < open_count`, we can add a ')'.
  5. This ensures that we never have more closing parentheses than 
     opening ones at any point, guaranteeing well-formedness.

  Complexity Analysis:
  - Time Complexity: O(4^N / sqrt(N))
    Reason: This is bounded by the N-th Catalan number, which represents 
    the number of valid parentheses sequences.
  - Space Complexity: O(N) for the recursion stack.
*/

class Solution {
    void backtrack(int n, int open, int close, string curr, vector<string>& result) {
        if (curr.length() == 2 * n) {
            result.push_back(curr);
            return;
        }

        if (open < n) {
            backtrack(n, open + 1, close, curr + "(", result);
        }
        if (close < open) {
            backtrack(n, open, close + 1, curr + ")", result);
        }
    }

public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        backtrack(n, 0, 0, "", result);
        return result;
    }
};

void test(int n) {
    cout << "Testing: n=" << n << endl;
    Solution sol;
    vector<string> result = sol.generateParenthesis(n);
    cout << "  Result: [ ";
    for (const string& s : result) cout << "\"" << s << "\" ";
    cout << "]" << endl;
}

int main() {
    test(3);
    test(1);
    return 0;
}
