#include <stdio.h>

/*
  Problem: Count Number of Set Bits (Popcount)

  Algorithm: Brian Kernighan's Algorithm
  1. Initialize `count = 0`.
  2. While `v` is not 0:
     - `v = v & (v - 1)` (This operation clears the least significant 
       set bit).
     - `count++`.
  3. This algorithm is more efficient than a linear scan because it 
     runs in time proportional to the number of SET bits, not the 
     total number of bits.

  Complexity Analysis:
  - Time Complexity: O(k)
    Reason: k is the number of set bits in the integer.
  - Space Complexity: O(1).

  Alternative Approaches:
  - Built-in functions: `__builtin_popcount(v)` in GCC/Clang.
  - Precomputed Table (O(1)): Look up set bits for each byte.
  - Brute Force: Iterate through all 32 bits: O(bits).
*/

unsigned int countSetBits(unsigned int v) {
    unsigned int count = 0;
    while (v) {
        v &= (v - 1);
        count++;
    }
    return count;
}

void test(unsigned int n) {
    printf("Number: %u (0x%x) -> Set Bits: %u\n", n, n, countSetBits(n));
}

int main() {
    test(11); // 1011 -> 3
    test(8);  // 1000 -> 1
    test(0);  // 0000 -> 0
    test(0xFFFFFFFF); // 32 ones -> 32
    return 0;
}
