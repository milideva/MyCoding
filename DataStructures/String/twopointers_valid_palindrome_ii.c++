#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 680: Valid Palindrome II

  Problem Description:
  Given a string `s`, return true if the string can be a palindrome 
  after deleting at most one character from it.

  Example 1:
  Input: s = "abca"
  Output: true
  Explanation: You could delete the character 'c'.

  Algorithm: Two Pointers with One-time Skip
  1. Initialize two pointers, `l = 0` and `r = n - 1`.
  2. While `l < r`:
     - If `s[l] == s[r]`, increment `l` and decrement `r`.
     - If `s[l] != s[r]`:
       - We must delete either `s[l]` or `s[r]`.
       - Check if the remaining substring `s[l+1...r]` or 
         `s[l...r-1]` is a palindrome.
       - If either is true, return true.
       - Otherwise, return false.
  3. If the loop completes without a mismatch, return true.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the string at most twice.
  - Space Complexity: O(1) auxiliary space.
*/

class Solution {
    bool isPalindrome(const string& s, int l, int r) {
        while (l < r) {
            if (s[l++] != s[r--]) return false;
        }
        return true;
    }

public:
    bool validPalindrome(string s) {
        int l = 0, r = s.length() - 1;
        while (l < r) {
            if (s[l] != s[r]) {
                // Try deleting s[l] or deleting s[r]
                return isPalindrome(s, l + 1, r) || isPalindrome(s, l, r - 1);
            }
            l++;
            r--;
        }
        return true;
    }
};

void test(string s, bool expected) {
    cout << "Testing: \"" << s << "\"" << endl;
    Solution sol;
    bool result = sol.validPalindrome(s);
    if (result == expected) {
        cout << "  [PASS] Result: " << boolalpha << result << endl;
    } else {
        cout << "  [FAIL] Result: " << boolalpha << result << " (Expected: " << expected << ")" << endl;
    }
}

int main() {
    test("aba", true);
    test("abca", true);
    test("abc", false);
    test("tebbem", false); 
    test("tebbe", true); // delete 't' -> "ebbe"
    return 0;
}
