#include <stdio.h>

/*
  Problem: Shift Operators and Signed/Unsigned Behavior

  Description:
  Demonstrate the differences between logical and arithmetic shifts 
  in C.

  Shifting Rules:
  1. Left Shift (<<):
     - Always fills 0s from the right, regardless of type.
     - Multiplication by 2^d.
  2. Right Shift (>>):
     - Unsigned Types: Logical shift. Always fills 0s from the left.
     - Signed Types: Implementation-defined!
       - Most systems use Arithmetic shift (fills with the sign bit).
       - This preserves the sign of negative numbers (Division by 2^d).
*/

void testShifts() {
    // 1. Unsigned Shift
    unsigned int u = 0x80000000;
    printf("Unsigned 0x%08x >> 1 = 0x%08x (Logical)\n", u, u >> 1);

    // 2. Signed Shift
    int s = -2147483648; // 0x80000000 in two's complement
    printf("Signed   0x%08x >> 1 = 0x%08x (Likely Arithmetic)\n", s, s >> 1);

    // 3. Left Shift (same for both)
    printf("Signed   0x00000001 << 1 = 0x%08x\n", 1 << 1);
}

int main() {
    testShifts();
    return 0;
}
