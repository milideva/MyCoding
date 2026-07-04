#include <stdio.h>

/*
  Problem: Parity Check

  Problem Description:
  Parity of a number refers to whether it contains an odd or even 
  number of set bits. 
  - Even Parity: Number of set bits is even (returns 0).
  - Odd Parity: Number of set bits is odd (returns 1).

  Algorithm: Iterative Extraction
  1. Initialize `parity = 0`.
  2. While `n` is not 0:
     - `parity = !parity`
     - `n = n & (n - 1)` (Clear the least significant set bit)
  3. Return `parity`.

  Complexity Analysis:
  - Time Complexity: O(k)
    Reason: k is the number of set bits.
  - Space Complexity: O(1).

  Alternative Approaches:
  - Bitwise XOR folding: 
    - `n ^= n >> 16; n ^= n >> 8; n ^= n >> 4; n ^= n >> 2; n ^= n >> 1;`
    - `return n & 1;`
    - O(log(bits)) steps.
*/

int checkParity(unsigned int n) {
    int parity = 0;
    while (n) {
        parity = !parity;
        n &= (n - 1);
    }
    return parity;
}

void test(unsigned int n) {
    printf("Number: %u (0x%x) -> Parity: %s\n", n, n, 
           checkParity(n) ? "Odd (1)" : "Even (0)");
}

int main() {
    test(11); // 1011 -> 3 bits (Odd)
    test(8);  // 1000 -> 1 bit (Odd)
    test(3);  // 0011 -> 2 bits (Even)
    test(0);  // 0000 -> 0 bits (Even)
    test(0xFFFFFFFF); // 32 bits (Even)
    return 0;
}
