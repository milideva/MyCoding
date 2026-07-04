#include <iostream>
#include <climits>

using namespace std;

/*
  LeetCode 50: Pow(x, n)

  Problem Description:
  Implement `pow(x, n)`, which calculates `x` raised to the power `n`.

  Algorithm: Binary Exponentiation (Fast Power)
  1. Handle the case where `n < 0` by taking `x = 1/x` and `n = -n`.
  2. Use a loop (or recursion) to calculate power:
     - While `n > 0`:
       - If `n` is odd: `res *= x`.
       - `x *= x` (square the base).
       - `n /= 2`.
  3. This reduces the number of multiplications from `n` to `log(n)`.
  4. Use `long long` for `n` to handle `INT_MIN` negation overflow.

  Complexity Analysis:
  - Time Complexity: O(log N)
  - Space Complexity: O(1).
*/

class Solution {
public:
    double myPow(double x, int n) {
        long long N = n;
        if (N < 0) {
            x = 1 / x;
            N = -N;
        }

        double res = 1.0;
        while (N > 0) {
            if (N % 2 == 1) {
                res *= x;
            }
            x *= x;
            N /= 2;
        }
        return res;
    }
};

void test(double x, int n) {
    Solution sol;
    cout << "pow(" << x << ", " << n << ") = " << sol.myPow(x, n) << endl;
}

int main() {
    test(2.0, 10);
    test(2.1, 3);
    test(2.0, -2);
    test(1.0, INT_MIN);
    return 0;
}
