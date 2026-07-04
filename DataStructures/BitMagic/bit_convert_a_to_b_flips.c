#include <stdio.h>

/*
  Problem: Number of Bit Flips to Convert A to B

  Problem Description:
  Given two integers `A` and `B`, find the number of bits that 
  need to be flipped to convert `A` to `B`.

  Algorithm: XOR and Popcount
  1. Calculate `C = A ^ B`.
  2. The bits set in `C` are the bits that are different between 
     `A` and `B`.
  3. Count the number of set bits in `C` (Popcount).
  4. Use Brian Kernighan's algorithm for efficient counting.

  Complexity Analysis:
  - Time Complexity: O(k)
    Reason: k is the number of different bits.
  - Space Complexity: O(1).
*/

unsigned int countBitFlips(unsigned int a, unsigned int b) {
    unsigned int diff = a ^ b;
    unsigned int count = 0;
    while (diff) {
        diff &= (diff - 1);
        count++;
    }
    return count;
}

void test(unsigned int a, unsigned int b, unsigned int expected) {
    unsigned int result = countBitFlips(a, b);
    printf("A: %u, B: %u -> Flips needed: %u\n", a, b, result);
    if (result == expected) printf("  [PASS]\n");
    else printf("  [FAIL] Expected: %u\n", expected);
}

int main() {
    test(29, 15, 2); // 11101 ^ 01111 = 10010 (2 bits)
    test(7, 10, 3);  // 0111 ^ 1010 = 1101 (3 bits)
    test(0, 0xFFFFFFFF, 32);
    return 0;
}
