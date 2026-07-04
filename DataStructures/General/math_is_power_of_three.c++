/**
 * Problem: Power of Three
 * Given an integer n, return true if it is a power of three.
 * 
 * Strategy: Iterative or Mathematical
 * - Iterative: Keep dividing by 3.
 * - Mathematical: Since 3 is prime, any power of 3 will divide the largest 
 *   possible power of 3 representable by an integer.
 *   3^19 = 1,162,261,467 is the largest power of 3 in a 32-bit signed int.
 * 
 * Time Complexity: O(log N) for iterative, O(1) for mathematical.
 * Space Complexity: O(1).
 */

#include <iostream>

using namespace std;

class Solution {
public:
    /**
     * Iterative approach: O(log N)
     */
    bool isPowerOfThree(int n) {
        if (n <= 0) return false;
        while (n % 3 == 0) {
            n /= 3;
        }
        return n == 1;
    }

    /**
     * Mathematical approach: O(1)
     */
    bool isPowerOfThreeMath(int n) {
        // 1162261467 is 3^19
        return n > 0 && 1162261467 % n == 0;
    }
};

int main() {
    Solution sol;
    int testCases[] = {27, 0, -1, 1, 9, 45};

    for (int n : testCases) {
        cout << "n = " << n << ": " << (sol.isPowerOfThree(n) ? "True" : "False") << endl;
    }

    return 0;
}
