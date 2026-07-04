#include <stdio.h>
#include <limits.h>

/*
  LeetCode 7: Reverse Integer

  Problem Description:
  Given a signed 32-bit integer `x`, return `x` with its digits reversed. 
  If reversing `x` causes the value to go outside the signed 32-bit 
  integer range `[-2^31, 2^31 - 1]`, then return 0.

  Algorithm: Successive Modulo and Overflow Check
  1. Initialize `rev = 0`.
  2. While `x != 0`:
     - Pop the last digit: `pop = x % 10`.
     - `x /= 10`.
     - Check for overflow before multiplying by 10:
       - If `rev > INT_MAX/10` or (`rev == INT_MAX/10` and `pop > 7`), return 0.
       - If `rev < INT_MIN/10` or (`rev == INT_MIN/10` and `pop < -8`), return 0.
     - `rev = rev * 10 + pop`.
  3. Return `rev`.

  Complexity Analysis:
  - Time Complexity: O(log10(N))
  - Space Complexity: O(1).
*/

int reverse(int x) {
    int rev = 0;
    while (x != 0) {
        int pop = x % 10;
        x /= 10;
        if (rev > INT_MAX/10 || (rev == INT_MAX/10 && pop > 7)) return 0;
        if (rev < INT_MIN/10 || (rev == INT_MIN/10 && pop < -8)) return 0;
        rev = rev * 10 + pop;
    }
    return rev;
}

void test(int x, int expected) {
    int result = reverse(x);
    printf("Integer: %d -> Reversed: %d", x, result);
    if (result == expected) printf(" [PASS]\n");
    else printf(" [FAIL] Expected: %d\n", expected);
}

int main() {
    test(123, 321);
    test(-123, -321);
    test(120, 21);
    test(1534236469, 0); // Overflow
    return 0;
}
