#include <stdio.h>

/*
  Problem: Swap Two Numbers without Temporary Variable

  Algorithm: XOR Swap
  1. `x = x ^ y`
  2. `y = x ^ y` (which is `(x ^ y) ^ y = x`)
  3. `x = x ^ y` (which is `(x ^ y) ^ x = y`)
  
  Note: This works because XOR is commutative and associative, and 
  `a ^ a = 0`, `a ^ 0 = a`.
  Warning: This fails if `x` and `y` point to the same memory location 
  (result would be 0).

  Complexity Analysis:
  - Time Complexity: O(1).
  - Space Complexity: O(1).
*/

void swap(int* x, int* y) {
    if (x == y) return; // Prevent zeroing out if pointers are identical
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}

void test(int a, int b) {
    printf("Before: a=%d, b=%d\n", a, b);
    swap(&a, &b);
    printf("After:  a=%d, b=%d\n\n", a, b);
}

int main() {
    test(10, 20);
    test(-5, 5);
    test(0, 100);
    return 0;
}
