#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

/*
  Problem: Check if Binary Representation is a Palindrome

  Problem Description:
  Given an integer `x`, return true if its binary representation is 
  a palindrome.

  Algorithm: Construct Reverse and Compare
  1. Create a variable `reversed` and initialize it to 0.
  2. Maintain a copy of the original number `n`.
  3. Iterate through all 32 bits (or up to the MSB):
     - Extract LSB of `n` and append it to `reversed`.
     - `reversed = (reversed << 1) | (n & 1)`
     - `n >>= 1`
  4. Compare the original `x` with its `reversed` version.
  5. Note: If we only consider bits up to MSB, we need to find the 
     MSB first.

  Complexity Analysis:
  - Time Complexity: O(bits)
    Reason: Fixed number of iterations (e.g., 32).
  - Space Complexity: O(1).
*/

bool isBinaryPalindrome(unsigned int x) {
    unsigned int reversed = 0;
    unsigned int temp = x;
    
    // For 32-bit fixed width check
    for (int i = 0; i < 32; i++) {
        reversed = (reversed << 1) | (temp & 1);
        temp >>= 1;
    }
    
    return reversed == x;
}

void printBinary(unsigned int n) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i % 8 == 0 && i != 0) printf(" ");
    }
}

void test(unsigned int x) {
    printf("Value: 0x%08x (", x); printBinary(x); printf(")\n");
    printf("  Is Binary Palindrome: %s\n", isBinaryPalindrome(x) ? "Yes" : "No");
}

int main() {
    test(0x80000001); // 100...001 -> Yes
    test(0xFFFFFFFF); // All 1s -> Yes
    test(0x00000000); // All 0s -> Yes
    test(0x12345678); // No
    test(0xAA55AA55); // No (Wait, 1010 1010 0101 0101 ... let's see)
    return 0;
}
