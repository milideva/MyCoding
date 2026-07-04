#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
  Problem: Check if Two Strings are Anagrams (C version)

  Description:
  An anagram is a word or phrase formed by rearranging the letters 
  of a different word or phrase, typically using all the original 
  letters exactly once.

  Algorithm: Frequency Array
  1. If lengths differ, they cannot be anagrams.
  2. Use an array of size 256 to count character occurrences.
  3. Increment for string 1, decrement for string 2.
  4. If all counts are zero, they are anagrams.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(1) (fixed size frequency array).
*/

bool isAnagram(const char* s1, const char* s2) {
    if (!s1 || !s2) return false;
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 != len2) return false;

    int count[256] = {0};
    for (int i = 0; i < len1; i++) {
        count[(unsigned char)s1[i]]++;
        count[(unsigned char)s2[i]]--;
    }

    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) return false;
    }
    return true;
}

void test(const char* s1, const char* s2) {
    printf("s1: \"%s\", s2: \"%s\" -> Anagram: %s\n", s1, s2, 
           isAnagram(s1, s2) ? "Yes" : "No");
}

int main() {
    test("listen", "silent");
    test("apple", "pale");
    test("Devdatta", "dattaDev"); // Case sensitive
    test("A", "a");
    return 0;
}
