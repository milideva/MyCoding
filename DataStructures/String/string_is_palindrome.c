#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/*
  Problem: Check if a String is a Palindrome (Ignoring Spaces and Case)

  Algorithm: Two Pointers with Skip
  1. Initialize `l = 0` and `r = n - 1`.
  2. While `l < r`:
     - While `l < r` and `!isalnum(s[l])`, increment `l`.
     - While `l < r` and `!isalnum(s[r])`, decrement `r`.
     - If `tolower(s[l]) != tolower(s[r])`, return false.
     - Increment `l`, decrement `r`.
  3. Return true.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(1).
*/

bool isPalindrome(const char* s) {
    if (!s) return false;
    int l = 0, r = strlen(s) - 1;

    while (l < r) {
        if (!isalnum((unsigned char)s[l])) {
            l++;
        } else if (!isalnum((unsigned char)s[r])) {
            r--;
        } else {
            if (tolower((unsigned char)s[l]) != tolower((unsigned char)s[r])) {
                return false;
            }
            l++;
            r--;
        }
    }
    return true;
}

void test(const char* s) {
    printf("String: \"%s\" -> Palindrome: %s\n", s, isPalindrome(s) ? "Yes" : "No");
}

int main() {
    test("A man, a plan, a canal: Panama");
    test("race a car");
    test("amma");
    test("malay ala m");
    test("");
    return 0;
}
