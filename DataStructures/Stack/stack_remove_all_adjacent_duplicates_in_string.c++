#include <string>
#include <iostream>
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

  Algorithm: String as a Stack
  1. Use a string `res` to simulate a stack.
  2. For each character `c` in the input string `s`:
     - If `res` is not empty and the last character of `res` is 
       equal to `c`:
       - Pop the last character from `res`.
     - Else:
       - Push `c` onto `res`.
  3. Return `res`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We iterate through the string once. Each character is 
    added and removed from the "stack" at most once.
  - Space Complexity: O(N) for the result string.
*/

class Solution {
public:
    string removeDuplicates(string s) {
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
