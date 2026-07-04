#include <stdio.h>

/*
  Problem: Next Power of Two

  Problem Description:
  Given an integer `n`, find the smallest power of two that is 
  greater than or equal to `n`.

  Algorithm: Bit Smearing
  1. Decrement `n` by 1. This handles the case where `n` is already 
     a power of two.
  2. Perform a series of right shifts and bitwise ORs to set all 
     bits to the right of the most significant bit to 1.
     - `n |= n >> 1`
     - `n |= n >> 2`
     - `n |= n >> 4`
     - `n |= n >> 8`
     - `n |= n >> 16`
  3. Now `n` is of the form `00...011...1`.
  4. Increment `n` by 1 to get the next power of two.

  Complexity Analysis:
  - Time Complexity: O(1) or O(log(bits)).
    Reason: Fixed number of shift operations.
  - Space Complexity: O(1).

  Example:
  Input: 5 (101)
  1. n = 4 (100)
  2. n |= n >> 1 -> 110
  3. n |= n >> 2 -> 111 (7)
  4. result = 7 + 1 = 8 (1000)
*/

unsigned int nextPowerOf2(unsigned int n) {
    if (n == 0) return 1;
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}

void test(unsigned int n) {
    printf("Number: %u -> Next Power of Two: %u\n", n, nextPowerOf2(n));
}

int main() {
    test(5);  // 8
    test(16); // 16
    test(1);  // 1
    test(0);  // 1
    test(100); // 128
    return 0;
}
