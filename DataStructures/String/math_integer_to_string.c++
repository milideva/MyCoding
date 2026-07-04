#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
  Problem: Integer to String (itoa implementation)

  Problem Description:
  Convert an integer to its string representation without using 
  built-in functions like `to_string`.

  Algorithm: Successive Modulo and Division
  1. Handle 0 as a special case.
  2. Handle negative numbers by converting to positive and 
     prepending '-' later.
  3. While `num > 0`:
     - `digit = num % 10`
     - `char = digit + '0'`
     - Append `char` to result string.
     - `num /= 10`
  4. Reverse the result string (since we extracted digits from 
     right to left).

  Complexity Analysis:
  - Time Complexity: O(log N)
    Reason: The number of digits is proportional to log10(N).
  - Space Complexity: O(log N) to store the result string.
*/

class Solution {
public:
    string intToString(int n) {
        if (n == 0) return "0";
        
        string res = "";
        bool isNegative = false;
        long long num = n; // Use long long to handle INT_MIN negation

        if (num < 0) {
            isNegative = true;
            num = -num;
        }

        while (num > 0) {
            res += (char)((num % 10) + '0');
            num /= 10;
        }

        if (isNegative) res += '-';
        
        reverse(res.begin(), res.end());
        return res;
    }
};

void test(int n) {
    Solution sol;
    cout << "Integer: " << n << " -> String: \"" << sol.intToString(n) << "\"" << endl;
}

int main() {
    test(123);
    test(-456);
    test(0);
    test(2147483647);
    test(-2147483648);
    return 0;
}
