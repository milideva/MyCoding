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

  Algorithm 1: Using std::stack<char> (Version 1)
  1. Use a standard `std::stack<char> stk` to keep track of processed characters.
  2. For each character `c` in the input string `s`:
     - If `stk` is not empty and the top of `stk` is equal to `c`:
       - Pop the matching character from `stk`.
     - Else:
       - Push `c` onto `stk`.
  3. Reconstruct the result string by popping elements from `stk` and then 
     reversing the final string to restore the original chronological order.

  Algorithm 2: Using std::string directly as a Stack (Version 2 - Optimized)
  1. Use a string `res` to simulate a stack directly.
  2. For each character `c` in the input string `s`:
     - If `res` is not empty and the last character of `res` is equal to `c`:
       - Pop the last character from `res`.
     - Else:
       - Push `c` onto `res`.
  3. This completely avoids extra stack memory overhead and string reversal.

  Complexity Analysis (For Both):
  - Time Complexity:
    - Best, Average, Worst Case: O(N)
    Reason: We iterate through the input string once, performing constant-time O(1) 
    stack operations at each step.
  - Space Complexity:
    - O(N) to store the characters inside the stack and the output string.
*/

class Solution {
public:
    // Version 1: Using std::stack<char>
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

    // Version 2: Using std::string directly as a stack (Optimized)
    string removeDuplicates_2(string s) {
        string res = "";
        for (char c : s) {
            if (!res.empty() && res.back() == c) {
                res.pop_back();
            } else {
                res.push_back(c);
            }
        }
        return res;
    }
};

void test(string s, string expected) {
    Solution sol;
    string result1 = sol.removeDuplicates(s);
    string result2 = sol.removeDuplicates_2(s);
    
    cout << "Input: \"" << s << "\"" << endl;
    cout << "  Version 1 (std::stack):   \"" << result1 << "\"";
    if (result1 == expected) cout << " [PASS]" << endl;
    else cout << " [FAIL] Expected: \"" << expected << "\"" << endl;

    cout << "  Version 2 (std::string):  \"" << result2 << "\"";
    if (result2 == expected) cout << " [PASS]" << endl;
    else cout << " [FAIL] Expected: \"" << expected << "\"" << endl;
    cout << endl;
}

int main() {
    test("abbaca", "ca");
    test("azxxzy", "ay");
    test("pbbcggttciiippooaais", "ps");
    return 0;
}
