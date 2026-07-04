#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 405: Convert a Number to Hexadecimal

  Problem Description:
  Given an integer `num`, return its hexadecimal representation. 
  For negative integers, use two's complement.

  Algorithm: Bit Masking and Shifting
  1. Handle 0 as a special case.
  2. Use a string mapping `0123456789abcdef` for hex digits.
  3. Treat the number as unsigned (e.g., `uint32_t`) to automatically 
     handle two's complement for negative values.
  4. While `num` is not 0 and we haven't processed 8 hex digits 
     (for 32-bit):
     - Extract the last 4 bits: `num & 0xf`.
     - Get the corresponding hex character.
     - Shift `num` right by 4 bits.
  5. Concatenate and return.

  Complexity Analysis:
  - Time Complexity: O(1)
    Reason: The loop runs a maximum of 8 times for a 32-bit integer.
  - Space Complexity: O(1) beyond the result string.
*/

class Solution {
public:
    string toHex(int num) {
        if (num == 0) return "0";
        
        string hexDigits = "0123456789abcdef";
        string result = "";
        unsigned int n = (unsigned int)num; // Handle negative via two's complement

        while (n > 0) {
            result += hexDigits[n & 0xf];
            n >>= 4;
        }

        reverse(result.begin(), result.end());
        return result;
    }
};

void test(int n) {
    Solution sol;
    cout << "Integer: " << n << " -> Hex: \"" << sol.toHex(n) << "\"" << endl;
}

int main() {
    test(26);  // 1a
    test(-1);  // ffffffff
    test(0);   // 0
    test(16);  // 10
    return 0;
}
