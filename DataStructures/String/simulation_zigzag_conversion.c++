#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
  LeetCode 6: Zigzag Conversion

  Problem Description:
  The string "PAYPALISHIRING" is written in a zigzag pattern on a 
  given number of rows.
  P   A   H   N
  A P L S I I G
  Y   I   R
  And then read line by line: "PAHNAPLSIIGYIR"
  Implement the function `convert(string s, int numRows)`.

  Algorithm: Row Simulation
  1. If `numRows == 1` or `numRows >= s.length()`, return `s`.
  2. Create an array of strings, one for each row.
  3. Maintain a `currentRow` and a `direction` (+1 for down, -1 for up).
  4. Iterate through the string:
     - Append the character to the string of `currentRow`.
     - If `currentRow` hits the top (0) or bottom (`numRows - 1`), 
       reverse the `direction`.
     - Update `currentRow += direction`.
  5. Concatenate all row strings to get the final result.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We visit each character exactly once.
  - Space Complexity: O(N)
    Reason: To store the row strings.
*/

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1 || numRows >= (int)s.length()) return s;

        vector<string> rows(numRows, "");
        int currRow = 0;
        bool goingDown = false;

        for (char c : s) {
            rows[currRow] += c;
            if (currRow == 0 || currRow == numRows - 1) {
                goingDown = !goingDown;
            }
            currRow += goingDown ? 1 : -1;
        }

        string result = "";
        for (const string& row : rows) result += row;
        return result;
    }
};

void test(string s, int numRows, string expected) {
    cout << "Testing: \"" << s << "\", Rows=" << numRows << endl;
    Solution sol;
    string result = sol.convert(s, numRows);
    if (result == expected) {
        cout << "  [PASS] Result: \"" << result << "\"" << endl;
    } else {
        cout << "  [FAIL] Result: \"" << result << "\" (Expected: \"" << expected << "\")" << endl;
    }
}

int main() {
    test("PAYPALISHIRING", 3, "PAHNAPLSIIGYIR");
    test("PAYPALISHIRING", 4, "PINALSIGYAHRPI");
    test("A", 1, "A");
    return 0;
}
