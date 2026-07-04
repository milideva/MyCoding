#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
  LeetCode 12: Integer to Roman

  Problem Description:
  Given an integer, convert it to a Roman numeral. 
  Input is guaranteed to be within the range from 1 to 3999.

  Algorithm: Greedy Subtraction
  1. Define two parallel arrays: `values` and `symbols`, sorted 
     from largest to smallest.
  2. Iterate through the `values` array:
     - While `num >= values[i]`:
       - Append `symbols[i]` to the result string.
       - Subtract `values[i]` from `num`.
  3. This naturally handles both standard symbols (M, D, C...) 
     and subtractive cases (CM, CD, XC...).

  Complexity Analysis:
  - Time Complexity: O(1)
    Reason: The number of Roman numeral symbols is fixed, and the 
    maximum value is 3999.
  - Space Complexity: O(1).
*/

class Solution {
public:
    string intToRoman(int num) {
        int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        string symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        
        string res = "";
        for (int i = 0; i < 13; i++) {
            while (num >= values[i]) {
                num -= values[i];
                res += symbols[i];
            }
        }
        return res;
    }
};

void test(int num) {
    Solution sol;
    cout << "Number: " << num << " -> Roman: \"" << sol.intToRoman(num) << "\"" << endl;
}

int main() {
    test(3);
    test(4);
    test(9);
    test(58);
    test(1994);
    return 0;
}
