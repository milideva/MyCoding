/**
 * Problem: Power of Four
 * Given an integer n, return true if it is a power of four. 
 * An integer n is a power of four if there exists an integer x such that n == 4^x.
 * 
 * Strategy: Iterative or Bit Manipulation
 * Bitwise property: A power of four must be a power of two (n & (n-1) == 0)
 * and its single set bit must be at an even position (0, 2, 4, ...).
 * (n & 0x55555555) checks if the bit is in an even position.
 * 
 * Time Complexity: O(1) for bitwise, O(log N) for iterative.
 * Space Complexity: O(1).
 */

#include <iostream>

using namespace std;

class Solution {
public:
    /**
     * Bitwise approach: O(1)
     */
    bool isPowerOfFour(int n) {
        return n > 0 && (n & (n - 1)) == 0 && (n & 0x55555555) != 0;
    }

    /**
     * Iterative approach: O(log N)
     */
    bool isPowerOfFourIterative(int n) {
        if (n <= 0) return false;
        while (n % 4 == 0) {
            n /= 4;
        }
        return n == 1;
    }
};

int main() {
    Solution sol;
    int testCases[] = {16, 5, 1, 64, 8};
    
    for (int n : testCases) {
        cout << "n = " << n << ": " << (sol.isPowerOfFour(n) ? "True" : "False") << endl;
    }

    return 0;
}
