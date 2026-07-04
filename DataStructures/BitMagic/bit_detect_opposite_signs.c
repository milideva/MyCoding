#include <stdio.h>
#include <stdbool.h>

/*
  Problem: Detect if Two Integers have Opposite Signs

  Algorithm: XOR Comparison
  1. Calculate `a ^ b`.
  2. If the result is negative (MSB is 1), then `a` and `b` had 
     different sign bits.
  3. This is because XOR returns 1 if bits are different. Since the 
     sign bit is the MSB in two's complement, XORing two numbers 
     with different signs will result in a number with the MSB set.

  Complexity Analysis:
  - Time Complexity: O(1).
  - Space Complexity: O(1).

  Brute Force comparison:
  - `(a < 0 && b >= 0) || (a >= 0 && b < 0)`.
  - The bitwise XOR approach is more idiomatic in low-level contexts.
*/

bool haveOppositeSigns(int a, int b) {
    return (a ^ b) < 0;
}

void test(int a, int b) {
    printf("a=%d, b=%d -> Opposite Signs: %s\n", a, b, 
           haveOppositeSigns(a, b) ? "Yes" : "No");
}

int main() {
    test(1, -1);
    test(-10, 20);
    test(5, 10);
    test(-5, -10);
    test(0, -1); // 0 is non-negative
    return 0;
}
