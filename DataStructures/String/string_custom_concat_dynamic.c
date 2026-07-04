#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
  Problem: Custom String Concatenation with Dynamic Allocation

  Description:
  Concatenate two strings into a new dynamically allocated buffer.

  Algorithm:
  1. Calculate `total_len = strlen(s1) + strlen(s2) + 1`.
  2. Allocate memory using `malloc` or `calloc`.
  3. Copy `s1` into the new buffer.
  4. Append `s2` into the new buffer.
  5. Return the pointer to the new string.

  Complexity Analysis:
  - Time Complexity: O(N + M) where N and M are string lengths.
  - Space Complexity: O(N + M) for the new string.
*/

char* customConcat(const char* s1, const char* s2) {
    if (!s1 || !s2) return NULL;

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char* result = (char*)malloc(len1 + len2 + 1);
    if (!result) return NULL;

    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main() {
    const char* part1 = "Hello, ";
    const char* part2 = "World!";
    
    char* combined = customConcat(part1, part2);
    if (combined) {
        printf("Combined: \"%s\"\n", combined);
        free(combined);
    }

    return 0;
}
