#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
  LeetCode 91: Decode Ways

  Problem Description:
  A message containing letters from A-Z is encoded using:
  'A' -> "1", 'B' -> "2", ..., 'Z' -> "26".
  Given a string `s` containing only digits, return the total 
  number of ways to decode it.

  Example 1:
  Input: s = "226"
  Output: 3 (BZ, VF, BBF)

  Algorithm: Dynamic Programming (Bottom-Up)
  1. Let `dp[i]` be the number of ways to decode the prefix `s[0...i-1]`.
  2. Base Case: `dp[0] = 1` (empty string has one way to decode).
  3. For each `i` from 1 to n:
     - Check single digit `s[i-1]`:
       - If `s[i-1] != '0'`, `dp[i] += dp[i-1]`.
     - Check two digits `s[i-2...i-1]`:
       - If `s[i-2...i-1]` is between "10" and "26", `dp[i] += dp[i-2]`.
  4. Return `dp[n]`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Single pass through the string.
  - Space Complexity: O(N) for the DP array. 
    Can be optimized to O(1) by only keeping the last two values.
*/

class Solution {
public:
    int numDecodings(string s) {
        int n = s.length();
        if (n == 0 || s[0] == '0') return 0;

        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;

        for (int i = 2; i <= n; i++) {
            // One digit
            if (s[i - 1] != '0') {
                dp[i] += dp[i - 1];
            }
            // Two digits
            int twoDigit = stoi(s.substr(i - 2, 2));
            if (twoDigit >= 10 && twoDigit <= 26) {
                dp[i] += dp[i - 2];
            }
        }
        return dp[n];
    }
};

void test(string s, int expected) {
    Solution sol;
    int result = sol.numDecodings(s);
    cout << "String: \"" << s << "\" -> Decode Ways: " << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    test("12", 2);
    test("226", 3);
    test("06", 0);
    test("10", 1);
    test("2101", 1);
    return 0;
}
