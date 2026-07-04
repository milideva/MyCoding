#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

/*
  Problem: Case-Insensitive String Comparison

  Description:
  Compare two strings while ignoring case (e.g., "Apple" == "apple").

  Algorithm: Iterative Character Comparison
  1. Iterate through both strings simultaneously.
  2. For each pair of characters, convert both to lowercase using 
     `tolower()`.
  3. If they differ, return the difference.
  4. If one reaches the end before the other, the strings are 
     different (unless both end simultaneously).

  Complexity Analysis:
  - Time Complexity: O(min(N, M))
  - Space Complexity: O(1).
*/

int compareIgnoreCase(const char* s1, const char* s2) {
    if (!s1 || !s2) return (s1 == s2) ? 0 : (s1 ? 1 : -1);

    while (*s1 && *s2) {
        char c1 = tolower((unsigned char)*s1);
        char c2 = tolower((unsigned char)*s2);

        if (c1 != c2) return c1 - c2;
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

void test(const char* s1, const char* s2) {
    int res = compareIgnoreCase(s1, s2);
    printf("s1: \"%s\", s2: \"%s\" -> %s\n", s1, s2, 
           (res == 0) ? "Equal" : "Different");
}

int main() {
    test("Devdatta", "deVdAttA");
    test("apple", "APPLE");
    test("banana", "cherry");
    test("abc", "abcd");
    return 0;
}
