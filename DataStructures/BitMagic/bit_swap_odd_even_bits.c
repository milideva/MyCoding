#include <stdio.h>

/*
  Problem: Swap Odd and Even Bits

  Problem Description:
  Given an unsigned integer, swap all odd bits with even bits. 
  (e.g., bit 0 with bit 1, bit 2 with bit 3, etc.)

  Algorithm: Bit Masking and Shifting
  1. Extract all even bits using mask `0x55555555` (0101...0101).
  2. Shift these even bits to the left by 1.
  3. Extract all odd bits using mask `0xAAAAAAAA` (1010...1010).
  4. Shift these odd bits to the right by 1.
  5. Combine the results using bitwise OR.

  Complexity Analysis:
  - Time Complexity: O(1).
  - Space Complexity: O(1).

  Example:
  Input: 23 (00010111)
  - Even bits: 00010101 -> Shift left 1: 00101010 (42)
  - Odd bits: 00000010 -> Shift right 1: 00000001 (1)
  - Result: 42 | 1 = 43 (00101011)
*/

unsigned int swapOddEvenBits(unsigned int n) {
    unsigned int evenBits = n & 0x55555555;
    unsigned int oddBits = n & 0xAAAAAAAA;
    return (evenBits << 1) | (oddBits >> 1);
}

void printBinary(unsigned int n) {
    for (int i = 7; i >= 0; i--) printf("%d", (n >> i) & 1);
}

void test(unsigned int n) {
    unsigned int result = swapOddEvenBits(n);
    printf("Input: %u (", n); printBinary(n); printf(") -> Swapped: %u (", result);
    printBinary(result); printf(")\n");
}

int main() {
    test(23); // 43
    test(1);  // 2
    test(2);  // 1
    test(0xAAAAAAAA); // 0x55555555
    return 0;
}
