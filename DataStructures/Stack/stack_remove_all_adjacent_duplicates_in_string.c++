#include <string>
#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

/*
  LeetCode 1047: Remove All Adjacent Duplicates In String

  Problem Description:
  Given a string `s` of lowercase letters, a duplicate removal 
  consists of choosing two adjacent and equal letters and removing 
  them. Repeatedly make duplicate removals until no more can be made.

  Example 1:
  Input: "abbaca"
  Output: "ca"
  Explanation: "abbaca" -> "aaca" -> "ca"

  Algorithm: Using std::stack<char>
  1. Use a standard `std::stack<char> stk` to keep track of processed characters.
  2. For each character `c` in the input string `s`:
     - If `stk` is not empty and the top of `stk` is equal to `c`:
       - Pop the matching character from `stk`.
     - Else:
       - Push `c` onto `stk`.
  3. Reconstruct the result string by popping elements from `stk` and then 
     reversing the final string to restore the original chronological order.

  Complexity Analysis:
  - Time Complexity:
    - Best, Average, Worst Case: O(N)
    Reason: We iterate through the input string once (pushing/popping at most 
    once), and then reverse the reconstructed string of length at most N.
  - Space Complexity:
    - O(N) to store the characters inside the stack and the output string.
*/

class Solution {
public:
    string removeDuplicates(string s) {
        stack<char> stk;
        for (char c : s) {
            if (!stk.empty() && stk.top() == c) {
                stk.pop();
            } else {
                stk.push(c);
            }
        }

        string res = "";
        while (!stk.empty()) {
            res.push_back(stk.top());
            stk.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

void test(string s, string expected) {
    Solution sol;
    string result = sol.removeDuplicates(s);
    cout << "Input: \"" << s << "\" -> Output: \"" << result << "\"";
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: \"" << expected << "\"";
    cout << endl;
}

int main() {
    test("abbaca", "ca");
    test("azxxzy", "ay");
    test("pbbcggttciiippooaais", "ps");
    return 0;
}
