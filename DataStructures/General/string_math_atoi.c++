#include <iostream>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

/*
  LeetCode 8: String to Integer (atoi)

  Problem Description:
  Implement the `myAtoi(string s)` function, which converts a string 
  to a 32-bit signed integer.
  1. Read and ignore any leading whitespace.
  2. Check for '-' or '+' to determine the sign.
  3. Read in next digits until a non-digit character or end of string.
  4. Clamp the integer to the range `[-2^31, 2^31 - 1]`.

  Algorithm: Iterative Parsing with Overflow Check
  1. Skip leading whitespaces.
  2. Parse the sign.
  3. Accumulate the number while checking for overflow:
     - `if (res > INT_MAX/10 || (res == INT_MAX/10 && digit > 7))`
  4. Return signed result.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(1).
*/

class Solution {
public:
    int myAtoi(string s) {
        int i = 0, n = s.length();
        while (i < n && s[i] == ' ') i++; // Skip spaces

        if (i == n) return 0;

        int sign = 1;
        if (s[i] == '-' || s[i] == '+') {
            sign = (s[i] == '-') ? -1 : 1;
            i++;
        }

        int res = 0;
        while (i < n && isdigit(s[i])) {
            int digit = s[i] - '0';
            
            // Check overflow
            if (res > INT_MAX / 10 || (res == INT_MAX / 10 && digit > 7)) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }
            
            res = res * 10 + digit;
            i++;
        }

        return res * sign;
    }
};

void test(string s) {
    Solution sol;
    cout << "Input: \"" << s << "\" -> Output: " << sol.myAtoi(s) << endl;
}

int main() {
    test("42");
    test("   -42");
    test("4193 with words");
    test("words and 987");
    test("-91283472332"); // Clamp to INT_MIN
    return 0;
}
