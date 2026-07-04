#include <stdio.h>
#include <limits.h>

/*
  LeetCode 190: Reverse Bits

  Problem Description:
  Reverse the bits of a given 32-bit unsigned integer.

  Algorithm: Iterative Extraction and Insertion
  1. Initialize `result = 0`.
  2. Iterate 32 times (for each bit):
     - Shift `result` to the left by 1 (make room for next bit).
     - Extract the LSB of `n`: `n & 1`.
     - Add this bit to `result`: `result |= (n & 1)`.
     - Shift `n` to the right by 1.
  3. Return `result`.

  Complexity Analysis:
  - Time Complexity: O(1)
    Reason: The loop runs a fixed number of times (32).
  - Space Complexity: O(1).

  Alternative Approaches:
  - Divide and Conquer (Bit Masking):
    - Swap adjacent bits, then adjacent 2-bit blocks, then 4-bit blocks...
    - This can be done in log(32) = 5 steps using constant masks.
*/

unsigned int reverseBits(unsigned int n) {
    unsigned int res = 0;
    for (int i = 0; i < 32; i++) {
        res = (res << 1) | (n & 1);
        n >>= 1;
    }
    return res;
}

void printBinary(unsigned int n) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i % 8 == 0 && i != 0) printf(" ");
    }
}

void test(unsigned int n) {
    unsigned int result = reverseBits(n);
    printf("Input:  0x%08x (", n); printBinary(n); printf(")\n");
    printf("Output: 0x%08x (", result); printBinary(result); printf(")\n\n");
}

int main() {
    test(0x00000022); // 0010 0010 -> 0100 0100 (in reverse order)
    test(0x4321abcd);
    test(0xFFFFFFFF);
    return 0;
}
