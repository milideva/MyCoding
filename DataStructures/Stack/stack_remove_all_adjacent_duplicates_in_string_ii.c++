#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 1209: Remove All Adjacent Duplicates in String II

  Problem Description:
  Given a string `s` and an integer `k`, a `k` duplicate removal 
  consists of choosing `k` adjacent and equal letters from `s` and 
  removing them. Repeatedly make `k` duplicate removals until no 
  more can be made.

  Example 1:
  Input: s = "deeedbbcccbdaa", k = 3
  Output: "aa"

  Algorithm: Stack of Pairs {Character, Count}
  1. Use a stack to store pairs of `{char, frequency}`.
  2. Iterate through each character `c` in `s`:
     - If the stack is not empty and the top character is `c`:
       - Increment the frequency of the top element.
       - If the frequency reaches `k`, pop it from the stack.
     - Else:
       - Push `{c, 1}` onto the stack.
  3. Reconstruct the string from the stack by repeating each 
     character according to its frequency.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We process each character once.
  - Space Complexity: O(N) for the stack.
*/

class Solution {
public:
    string removeDuplicates(string s, int k) {
        // stack of {char, count}
        vector<pair<char, int>> stk;

        for (char c : s) {
            if (!stk.empty() && stk.back().first == c) {
                stk.back().second++;
                if (stk.back().second == k) {
                    stk.pop_back();
                }
            } else {
                stk.push_back({c, 1});
            }
        }

        string result = "";
        for (auto const& p : stk) {
            result.append(p.second, p.first);
        }
        return result;
    }
};

void test(string s, int k, string expected) {
    Solution sol;
    string result = sol.removeDuplicates(s, k);
    cout << "Input: \"" << s << "\" k=" << k << " -> Output: \"" << result << "\"";
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: \"" << expected << "\"";
    cout << endl;
}

int main() {
    test("abcd", 2, "abcd");
    test("deeedbbcccbdaa", 3, "aa");
    test("pbbcggttciiippooaais", 2, "ps");
    return 0;
}
