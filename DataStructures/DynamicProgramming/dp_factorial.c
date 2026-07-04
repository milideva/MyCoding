#include <stdio.h>

/*
  Problem: Factorial (DP vs Recursion)

  Algorithm:
  1. Recursive: f(n) = n * f(n-1)
  2. Iterative (DP): Build up from 1 to n.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(N) for recursion stack, O(1) for iterative.
*/

unsigned long long factorialRecursive(unsigned int n) {
    if (n <= 1) return 1;
    return (unsigned long long)n * factorialRecursive(n - 1);
}

unsigned long long factorialIterative(unsigned int n) {
    unsigned long long res = 1;
    for (unsigned int i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

void test(unsigned int n) {
    printf("Factorial(%u):\n", n);
    printf("  Recursive: %llu\n", factorialRecursive(n));
    printf("  Iterative: %llu\n\n", factorialIterative(n));
}

int main() {
    test(5);
    test(10);
    test(20);
    return 0;
}
