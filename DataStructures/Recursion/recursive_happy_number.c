#include <stdio.h>
#include <stdbool.h>

/*
  LeetCode 202: Happy Number

  Problem Description:
  A happy number is a number defined by the following process:
  1. Starting with any positive integer, replace the number by the 
     sum of the squares of its digits.
  2. Repeat the process until the number equals 1 (where it will stay), 
     or it loops endlessly in a cycle which does not include 1.
  3. Numbers that end in 1 are happy; others are unhappy.

  Algorithm: Recursion with Cycle Detection
  1. Define a helper function `getSumOfSquares(n)`.
  2. Recursive function `isHappy(n, seen_set)`.
  3. Base Case 1: If `n == 1`, return true.
  4. Base Case 2: If `n` is in `seen_set`, return false (cycle detected).
  5. Recursive Step: Add `n` to `seen_set` and recurse for 
     `getSumOfSquares(n)`.

  Complexity Analysis:
  - Time Complexity: O(log N) for sum calculation, but the overall 
    number of steps to reach 1 or a cycle is hard to bound tightly. 
    Empirically, it is very small.
  - Space Complexity: O(Steps) to store seen numbers in the set.
*/

int getNext(int n) {
    int sum = 0;
    while (n > 0) {
        int d = n % 10;
        sum += d * d;
        n /= 10;
    }
    return sum;
}

// C version uses a known cycle for unhappy numbers: 4, 16, 37, 58, 89, 145, 42, 20...
bool isHappy(int n) {
    if (n == 1) return true;
    if (n == 4) return false; // Known point in the unhappy cycle
    return isHappy(getNext(n));
}

void test(int n) {
    printf("Number: %d -> Happy: %s\n", n, isHappy(n) ? "Yes" : "No");
}

int main() {
    test(19); // Yes
    test(2);  // No
    test(7);  // Yes
    test(1);  // Yes
    return 0;
}
