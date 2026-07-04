#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

/*
  LeetCode 9: Palindrome Number

  Problem Description:
  Given an integer `x`, return true if `x` is a palindrome, and 
  false otherwise.

  Algorithm: Reversing Half of the Number
  1. Negative numbers are not palindromes (e.g., -121 -> 121-).
  2. Numbers ending in 0 (except 0 itself) are not palindromes.
  3. Reverse the last half of the digits:
     - While `x > reversedNum`:
       - `reversedNum = reversedNum * 10 + x % 10`
       - `x /= 10`
  4. If `x == reversedNum` (even length) or `x == reversedNum / 10` 
     (odd length), then it's a palindrome.

  Complexity Analysis:
  - Time Complexity: O(log10(N))
  - Space Complexity: O(1).
*/

bool isPalindrome(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) return false;

    int reversedNum = 0;
    while (x > reversedNum) {
        // Prevent overflow by reversing only half
        reversedNum = reversedNum * 10 + x % 10;
        x /= 10;
    }

    return x == reversedNum || x == reversedNum / 10;
}

void test(int x, bool expected) {
    bool result = isPalindrome(x);
    printf("Number: %d -> Palindrome: %s", x, result ? "Yes" : "No");
    if (result == expected) printf(" [PASS]\n");
    else printf(" [FAIL]\n");
}

int main() {
    test(121, true);
    test(-121, false);
    test(10, false);
    test(0, true);
    test(12321, true);
    return 0;
}
