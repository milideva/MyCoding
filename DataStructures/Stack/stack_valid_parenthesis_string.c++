#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
  LeetCode 678: Valid Parenthesis String

  Problem Description:
  Given a string `s` containing only three types of characters: '(', ')' and '*', 
  return true if `s` is valid.
  The following rules define a valid string:
  1. Any left parenthesis '(' must have a corresponding right parenthesis ')'.
  2. Any right parenthesis ')' must have a corresponding left parenthesis '('.
  3. Left parenthesis '(' must go before the corresponding right parenthesis ')'.
  4. '*' could be treated as a single right parenthesis ')' or a single left 
     parenthesis '(' or an empty string "".

  =============================================================================
  METHOD 1: Two Stacks (Tracking Indices)
  =============================================================================
  Intuition:
  We use two stacks: one to store the indices of open parenthesis '(' and another 
  to store the indices of asterisks '*'.
  - When we encounter ')', we prioritize matching it with '(' (from `open_stk`), 
    then with '*' (from `star_stk`) if no '(' is available. If neither exists, 
    the string is invalid.
  - After iterating, some '(' may remain. We must pair each leftover '(' with a 
    leftover '*' that appears AFTER the '(' (i.e., index of '(' < index of '*').

  Complexity Analysis:
  - Time Complexity:
    - Best Case: O(N) where N is the length of the string.
    - Average Case: O(N).
    - Worst Case: O(N).
  - Space Complexity: O(N) auxiliary space for the two stacks.

  =============================================================================
  METHOD 2: Greedy (Two-Counter Tracking) - Highly Optimal
  =============================================================================
  Intuition:
  Instead of tracking exact indices, we can track the range of possible open 
  parentheses '(' that we could have at any step:
  - `min_open`: The minimum possible open '(' we could have (treating '*' as ')' or "").
  - `max_open`: The maximum possible open '(' we could have (treating '*' as '(').
  If `max_open` drops below 0 at any point, there are too many ')' and it is invalid.
  At the end, if 0 is within the possible range (`min_open == 0`), the string is valid.

  Complexity Analysis:
  - Time Complexity:
    - Best Case: O(N).
    - Average Case: O(N).
    - Worst Case: O(N).
  - Space Complexity: O(1) auxiliary space (no extra stack allocation).
*/

class Solution {
public:
    // Method 1: Two Stacks (Requested Stack Implementation)
    bool checkValidString(string s) {
        stack<int> open_stk;
        stack<int> star_stk;

        for (int i = 0; i < (int)s.length(); i++) {
            if (s[i] == '(') {
                open_stk.push(i);
            } else if (s[i] == '*') {
                star_stk.push(i);
            } else { // s[i] == ')'
                if (!open_stk.empty()) {
                    open_stk.pop();
                } else if (!star_stk.empty()) {
                    star_stk.pop();
                } else {
                    return false; // No '(' or '*' available to match ')'
                }
            }
        }

        // Match remaining '(' with '*' that appear AFTER them
        while (!open_stk.empty() && !star_stk.empty()) {
            if (open_stk.top() > star_stk.top()) {
                return false; // '*' is before '(', cannot close it
            }
            open_stk.pop();
            star_stk.pop();
        }

        return open_stk.empty();
    }

    // Method 2: Greedy O(1) Space Alternative
    bool checkValidStringGreedy(string s) {
        int min_open = 0; // Lower bound of open '('
        int max_open = 0; // Upper bound of open '('

        for (char c : s) {
            if (c == '(') {
                min_open++;
                max_open++;
            } else if (c == ')') {
                min_open = max(0, min_open - 1);
                max_open--;
            } else { // '*'
                min_open = max(0, min_open - 1); // Treat '*' as ')' or ""
                max_open++;                      // Treat '*' as '('
            }

            if (max_open < 0) {
                return false; // Too many close parenthesis ')'
            }
        }

        return min_open == 0;
    }
};

void run_test(const string& test_name, const string& input, bool expected, bool actual) {
    bool passed = (expected == actual);
    cout << test_name << " (\"" << input << "\"): Expected: " << (expected ? "true" : "false")
         << " Got: " << (actual ? "true" : "false")
         << " " << (passed ? "PASS" : "FAIL") << endl;
}

int main() {
    Solution sol;

    // Test cases provided in LeetCode description
    cout << "--- Testing Method 1: Two Stacks ---" << endl;
    run_test("Example 1", "()", true, sol.checkValidString("()"));
    run_test("Example 2", "(*)", true, sol.checkValidString("(*)"));
    run_test("Example 3", "(*))", true, sol.checkValidString("(*))"));
    run_test("Example 4", "(", false, sol.checkValidString("("));
    run_test("Corner Case 1", "*(", false, sol.checkValidString("*("));
    run_test("Corner Case 2", "(((**)))", true, sol.checkValidString("(((**)))"));

    cout << "\n--- Testing Method 2: Greedy (O(1) Space) ---" << endl;
    run_test("Example 1", "()", true, sol.checkValidStringGreedy("()"));
    run_test("Example 2", "(*)", true, sol.checkValidStringGreedy("(*)"));
    run_test("Example 3", "(*))", true, sol.checkValidStringGreedy("(*))"));
    run_test("Example 4", "(", false, sol.checkValidStringGreedy("("));
    run_test("Corner Case 1", "*(", false, sol.checkValidStringGreedy("*("));
    run_test("Corner Case 2", "(((**)))", true, sol.checkValidStringGreedy("(((**)))"));

    return 0;
}
