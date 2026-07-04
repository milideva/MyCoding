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

  Algorithm: Dynamic Programming (Bottom-Up)
  1. Let `dp[i]` be the number of ways to decode prefix `s[0...i-1]`.
  2. Base Case: `dp[0] = 1`.
  3. Recurrence:
     - If `s[i-1] != '0'`, `dp[i] += dp[i-1]`.
     - If `s[i-2...i-1]` is between "10" and "26", `dp[i] += dp[i-2]`.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(N) or O(1).
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
            if (s[i - 1] != '0') {
                dp[i] += dp[i - 1];
            }
            int twoDigit = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
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
    cout << "String: \"" << s << "\" -> Ways: " << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    test("12", 2);
    test("226", 3);
    test("06", 0);
    return 0;
}
