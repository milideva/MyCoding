#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/*
  LeetCode 13: Roman to Integer

  Problem Description:
  Given a Roman numeral string, convert it to an integer.

  Algorithm: Backward Traversal (or Forward with Peek)
  1. Map Roman symbols to their integer values.
  2. Iterate through the string from right to left.
  3. Keep track of the value of the previous character.
  4. For the current character:
     - If its value >= previous character's value, ADD it to the total.
     - If its value < previous character's value, SUBTRACT it from 
       the total (e.g., IV where I < V).
  5. Return the total.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the string exactly once.
  - Space Complexity: O(1)
    Reason: The symbol map is fixed size.
*/

class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> m = {
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
            {'C', 100}, {'D', 500}, {'M', 1000}
        };

        int total = 0;
        int prevValue = 0;

        for (int i = s.length() - 1; i >= 0; i--) {
            int currValue = m[s[i]];
            if (currValue < prevValue) {
                total -= currValue;
            } else {
                total += currValue;
            }
            prevValue = currValue;
        }
        return total;
    }
};

void test(string s) {
    Solution sol;
    cout << "Roman: \"" << s << "\" -> Integer: " << sol.romanToInt(s) << endl;
}

int main() {
    test("III");
    test("IV");
    test("IX");
    test("LVIII");
    test("MCMXCIV");
    return 0;
}
