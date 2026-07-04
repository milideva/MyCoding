#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/*
  LeetCode 796: Rotate String

  Problem Description:
  Given two strings `s` and `goal`, return true if and only if `s` 
  can become `goal` after some number of shifts on `s`.

  Algorithm 1: Concatenation
  1. If lengths of `s` and `goal` differ, return false.
  2. Concatenate `s` with itself: `combined = s + s`.
  3. If `goal` is a substring of `combined`, return true.
  
  Algorithm 2: In-Place Reverse Rotation
  1. To rotate by `k`:
     - Reverse `s[0...k-1]`.
     - Reverse `s[k...n-1]`.
     - Reverse `s[0...n-1]`.

  Complexity Analysis (Algorithm 1):
  - Time Complexity: O(N)
    Reason: Substring search (e.g., KMP) takes O(N).
  - Space Complexity: O(N) to store the concatenated string.
*/

bool rotateString(const char* s, const char* goal) {
    if (!s || !goal) return false;
    int lenS = strlen(s);
    int lenG = strlen(goal);
    if (lenS != lenG) return false;
    if (lenS == 0) return true;

    char* combined = (char*)malloc(2 * lenS + 1);
    strcpy(combined, s);
    strcat(combined, s);

    bool res = strstr(combined, goal) != NULL;
    free(combined);
    return res;
}

void test(const char* s, const char* goal) {
    printf("s: \"%s\", goal: \"%s\" -> Rotate: %s\n", s, goal, 
           rotateString(s, goal) ? "Yes" : "No");
}

int main() {
    test("abcde", "cdeab");
    test("abcde", "abced");
    test("apple", "pleap");
    return 0;
}
