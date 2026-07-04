#include <stdio.h>
#include <limits.h>

/*
  Problem: Bitwise Rotation (Circular Shift)

  Description:
  Rotate bits of an integer to the left or right. Unlike standard 
  shifting, bits that "fall off" one end are inserted back at the 
  other end.

  Algorithm: Bitwise OR of Shifting and Wrapping
  - Rotate Left (n, d): `(n << d) | (n >> (bits - d))`
  - Rotate Right (n, d): `(n >> d) | (n << (bits - d))`
  - Note: `d` must be masked to `bits - 1` to avoid undefined behavior 
    if `d >= bits`.

  Complexity Analysis:
  - Time Complexity: O(1).
  - Space Complexity: O(1).
*/

#define INT_BITS (sizeof(int) * CHAR_BIT)

unsigned int rotateLeft(unsigned int n, unsigned int d) {
    d %= INT_BITS;
    if (d == 0) return n;
    return (n << d) | (n >> (INT_BITS - d));
}

unsigned int rotateRight(unsigned int n, unsigned int d) {
    d %= INT_BITS;
    if (d == 0) return n;
    return (n >> d) | (n << (INT_BITS - d));
}

void printBinary(unsigned int n) {
    for (int i = INT_BITS - 1; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i % 8 == 0 && i != 0) printf(" ");
    }
}

void test(unsigned int n, unsigned int d) {
    printf("Value: 0x%08x Shift: %u\n", n, d);
    unsigned int left = rotateLeft(n, d);
    unsigned int right = rotateRight(n, d);
    printf("  Left:  0x%08x (", left); printBinary(left); printf(")\n");
    printf("  Right: 0x%08x (", right); printBinary(right); printf(")\n\n");
}

int main() {
    test(0x00000034, 30);
    test(0x12345678, 4);
    return 0;
}
