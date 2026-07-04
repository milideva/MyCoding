/**
 * Problem: Eliminate Specific Substrings
 * Eliminate all 'b' and 'ac' in an array of characters in-place.
 * You are only allowed to iterate over the char array once.
 * 
 * Examples:
 * "abc" -> "ac" -> "" (because 'b' removed, then 'ac' removed)
 * "react" -> "ret"
 * "aaac" -> "aa"
 * 
 * Strategy: Two Pointers (Read and Write)
 * - 'rd' pointer scans the string.
 * - 'wr' pointer maintains the valid prefix.
 * - If we see 'b', skip it.
 * - If we see 'c' and the previous character written was 'a', "pop" the 'a' 
 *   by decrementing 'wr'.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1) in-place.
 */

#include <stdio.h>
#include <string.h>

/**
 * Eliminates 'b' and 'ac' from the string in-place.
 */
void eliminate(char *str) {
    if (!str) return;

    int wr = 0;
    for (int rd = 0; str[rd] != '\0'; rd++) {
        if (str[rd] == 'b') {
            continue;
        } else if (str[rd] == 'c' && wr > 0 && str[wr - 1] == 'a') {
            wr--; // Eliminate 'ac'
        } else {
            str[wr++] = str[rd];
        }
    }
    str[wr] = '\0';
}

int main() {
    char s1[] = "abc";
    eliminate(s1);
    printf("\"abc\" -> \"%s\"\n", s1);

    char s2[] = "react";
    eliminate(s2);
    printf("\"react\" -> \"%s\"\n", s2);

    char s3[] = "aaac";
    eliminate(s3);
    printf("\"aaac\" -> \"%s\"\n", s3);

    char s4[] = "ababcac";
    eliminate(s4);
    printf("\"ababcac\" -> \"%s\"\n", s4);

    return 0;
}
