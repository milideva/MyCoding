#include <string>
#include <stack>
#include <unordered_map>
#include <iostream>

using namespace std;

/*
  LeetCode 20: Valid Parentheses

  Problem Description:
  Given a string `s` containing just the characters '(', ')', '{', '}', 
  '[' and ']', determine if the input string is valid.
  Validity Rules:
  1. Open brackets must be closed by the same type of brackets.
  2. Open brackets must be closed in the correct order.

  Algorithm: Stack
  1. Use a stack to store opening brackets.
  2. Map closing brackets to their corresponding opening brackets.
  3. Iterate through the string:
     - If it's an opening bracket, push it onto the stack.
     - If it's a closing bracket:
       - If the stack is empty, return false (unmatched closing).
       - If the top of the stack is the matching opening bracket, pop it.
       - Otherwise, return false (mismatched type).
  4. After the loop, if the stack is empty, return true.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the string exactly once.
  - Space Complexity: O(N)
    Reason: In the worst case, we push all characters onto the stack 
    (e.g., "(((((").
*/

class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;
        unordered_map<char, char> matching = {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };

        for (char c : s) {
            if (matching.count(c)) {
                // Closing bracket
                if (stk.empty() || stk.top() != matching[c]) return false;
                stk.pop();
            } else {
                // Opening bracket
                stk.push(c);
            }
        }
        return stk.empty();
    }
};

void test(const string& label, string s, bool expected) {
    cout << "Testing: \"" << s << "\"" << endl;
    Solution sol;
    bool result = sol.isValid(s);
    cout << "  [" << (result == expected ? "PASS" : "FAIL") << "] Result: " << boolalpha << result << endl;
}

int main() {
    test("Example 1", "()", true);
    test("Example 2", "()[]{}", true);
    test("Example 3", "(]", false);
    test("Example 4", "([)]", false);
    test("Example 5", "{[]}", true);
    test("Single Opening", "(", false);
    return 0;
}
