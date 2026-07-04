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

  Algorithm: Stack
  1. Use a stack to store opening brackets.
  2. Map closing brackets to their corresponding opening brackets.
  3. Iterate through the string:
     - If it's an opening bracket, push it onto the stack.
     - If it's a closing bracket:
       - If the stack is empty, return false.
       - If the top of the stack matches, pop it.
       - Otherwise, return false.
  4. After the loop, return true if the stack is empty.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(N).
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
                if (stk.empty() || stk.top() != matching[c]) return false;
                stk.pop();
            } else {
                stk.push(c);
            }
        }
        return stk.empty();
    }
};

void test(string s, bool expected) {
    Solution sol;
    bool result = sol.isValid(s);
    cout << "Input: \"" << s << "\" -> Valid: " << boolalpha << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    test("()[]{}", true);
    test("([)]", false);
    test("{[]}", true);
    return 0;
}
