#include <stdio.h>
#include <limits.h>

/*
  Problem: Count Leading Zeros (CLZ)

  Problem Description:
  Count the number of consecutive zero bits starting from the most 
  significant bit (MSB) of an integer.

  Algorithm: Iterative Right Shift
  1. Determine the total number of bits in the integer (e.g., 32).
  2. Maintain a `count` of bits seen while right shifting.
  3. While `value` is not 0:
     - `value >>= 1`
     - `count++`
  4. The result is `total_bits - count`.
  5. Note: This logic assumes the highest set bit determines the range. 
     A more robust version handles 0 explicitly.

  Complexity Analysis:
  - Time Complexity: O(log N)
    Reason: We shift the number until it becomes zero.
  - Space Complexity: O(1).

  Alternative Approaches:
  - GCC Built-in: `__builtin_clz(v)`. Note: Undefined for v=0.
  - Binary Search: Check halves of the 32-bit range to find the first 
    set bit. O(log(bits)).
*/

int countLeadingZeros(unsigned int value) {
    if (value == 0) return sizeof(value) * CHAR_BIT;

    unsigned int count = 0;
    unsigned int totalBits = sizeof(value) * CHAR_BIT;

    while (value) {
        value >>= 1;
        count++;
    }
    return totalBits - count;
}

void test(unsigned int n) {
    printf("Value: 0x%08x -> Leading Zeros: %d\n", n, countLeadingZeros(n));
}

int main() {
    test(0x80000008); // 0
    test(0x00000008); // 28 (32 - 4 bits used)
    test(0x00000000); // 32
    test(0x00000001); // 31
    return 0;
}
