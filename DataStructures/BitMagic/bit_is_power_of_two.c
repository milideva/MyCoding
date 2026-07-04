#include <stdio.h>
#include <stdbool.h>

/*
  Problem: Is Power of Two

  Algorithm: n & (n - 1)
  1. A power of two in binary has exactly one bit set (e.g., 8 = 1000).
  2. `n - 1` has all bits to the right of the original set bit as 1s, 
     and the original set bit as 0 (e.g., 7 = 0111).
  3. Thus, `n & (n - 1)` will be 0 if and only if `n` is a power of 2.
  4. Also handle `n = 0` (not a power of 2).

  Complexity Analysis:
  - Time Complexity: O(1).
  - Space Complexity: O(1).
*/

bool isPowerOfTwo(unsigned int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

void test(unsigned int n) {
    printf("Number: %u (0x%x) is power of two: %s\n", n, n, 
           isPowerOfTwo(n) ? "Yes" : "No");
}

int main() {
    test(1);  // 2^0
    test(2);  // 2^1
    test(16); // 2^4
    test(3);  // No
    test(0);  // No
    return 0;
}
