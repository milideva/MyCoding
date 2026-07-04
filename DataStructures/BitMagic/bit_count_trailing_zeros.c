#include <stdio.h>
#include <limits.h>

/*
  Problem: Count Trailing Zeros (CTZ)

  Problem Description:
  Count the number of consecutive zero bits starting from the least 
  significant bit (LSB) of an integer.

  Algorithm: Iterative Check
  1. If value is 0, return total bits (e.g., 32).
  2. Maintain a `count = 0`.
  3. While `(value & 1) == 0`:
     - `value >>= 1`
     - `count++`
  4. Return `count`.

  Complexity Analysis:
  - Time Complexity: O(bits)
    Reason: We check bits from LSB until we find a 1.
  - Space Complexity: O(1).

  Alternative Approaches:
  - GCC Built-in: `__builtin_ctz(v)`. Undefined for v=0.
  - Modulo/Lookup Table: `count = table[(v & -v) % mapping]`.
  - BitScan (Branch-free): Using binary search on bits.
*/

int countTrailingZeros(unsigned int value) {
    if (value == 0) return sizeof(value) * CHAR_BIT;

    int count = 0;
    while ((value & 1) == 0) {
        value >>= 1;
        count++;
    }
    return count;
}

void test(unsigned int n) {
    printf("Value: 0x%08x -> Trailing Zeros: %d\n", n, countTrailingZeros(n));
}

int main() {
    test(0x80000008); // 3 (1000 at the end)
    test(0x00000008); // 3
    test(0x00000001); // 0
    test(0x00000000); // 32
    return 0;
}
