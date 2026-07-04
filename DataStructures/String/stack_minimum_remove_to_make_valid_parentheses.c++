#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 1249: Minimum Remove to Make Valid Parentheses

  Problem Description:
  Given a string `s` of '(', ')' and lowercase English characters. 
  Remove the minimum number of parentheses in any positions so that 
  the resulting string is valid.

  Algorithm: Stack for Mismatched Indices
  1. Use a stack to keep track of the indices of opening parentheses '('.
  2. Maintain a boolean array `toRemove` (initialized to false).
  3. Iterate through the string:
     - If '(': Push its index onto the stack.
     - If ')':
       - If the stack is not empty, pop the matching '(' index.
       - If the stack is empty, this ')' is unmatched; mark it in 
         `toRemove`.
  4. After the loop, any indices remaining in the stack are unmatched '('; 
     mark them in `toRemove`.
  5. Build the final string by skipping characters marked in `toRemove`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the string a few times (linear passes).
  - Space Complexity: O(N)
    Reason: To store the stack of indices and the `toRemove` array.
*/

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int n = s.length();
        vector<bool> toRemove(n, false);
        stack<int> stk;

        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                stk.push(i);
            } else if (s[i] == ')') {
                if (!stk.empty()) {
                    stk.pop();
                } else {
                    toRemove[i] = true;
                }
            }
        }

        // Remaining indices in stack are unmatched '('
        while (!stk.empty()) {
            toRemove[stk.top()] = true;
            stk.pop();
        }

        string result = "";
        for (int i = 0; i < n; i++) {
            if (!toRemove[i]) {
                result += s[i];
            }
        }
        return result;
    }
};

void test(string s, string expected) {
    cout << "Testing: \"" << s << "\"" << endl;
    Solution sol;
    string result = sol.minRemoveToMakeValid(s);
    cout << "  Result: \"" << result << "\"" << endl;
}

int main() {
    test("lee(t(c)o)de)", "lee(t(c)o)de");
    test("a)b(c)d", "ab(c)d");
    test("))((", "");
    return 0;
}
