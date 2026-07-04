#include <limits.h>
#include <stdio.h>
#include <stdbool.h>

/*
  Problem: Basic Bitwise Operations

  Description:
  Demonstrate common bitwise operations:
  - `isBitSet`: Check if the bit at a specific position is 1.
  - `setBit`: Set the bit at a specific position to 1.
  - `clearBit`: Set the bit at a specific position to 0.
  - `toggleBit`: Invert the bit at a specific position.

  Complexity Analysis:
  - All operations: O(1).
  - Space Complexity: O(1).
*/

bool isBitSet(unsigned int n, int pos) {
    if (pos < 0 || pos >= (int)(sizeof(n) * CHAR_BIT)) return false;
    return (n & (1U << pos)) != 0;
}

void setBit(unsigned int* n, int pos) {
    if (pos < 0 || pos >= (int)(sizeof(*n) * CHAR_BIT)) return;
    *n |= (1U << pos);
}

void clearBit(unsigned int* n, int pos) {
    if (pos < 0 || pos >= (int)(sizeof(*n) * CHAR_BIT)) return;
    *n &= ~(1U << pos);
}

void toggleBit(unsigned int* n, int pos) {
    if (pos < 0 || pos >= (int)(sizeof(*n) * CHAR_BIT)) return;
    *n ^= (1U << pos);
}

void printBinary(unsigned int n) {
    for (int i = (sizeof(n) * CHAR_BIT) - 1; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i % 8 == 0 && i != 0) printf(" ");
    }
    printf("\n");
}

int main() {
    unsigned int n = 0;
    printf("Initial: "); printBinary(n);

    setBit(&n, 3);
    printf("After setBit(3): "); printBinary(n);

    if (isBitSet(n, 3)) printf("Bit 3 is set.\n");

    toggleBit(&n, 3);
    printf("After toggleBit(3): "); printBinary(n);

    clearBit(&n, 3);
    printf("After clearBit(3): "); printBinary(n);

    return 0;
}
