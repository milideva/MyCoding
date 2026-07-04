#include <stdio.h>
#include <string.h>

/*
  Problem: Trim All Spaces from a String In-Place

  Algorithm: Two Pointers (Read and Write)
  1. Maintain a `write` pointer at 0.
  2. Iterate through the string with a `read` pointer.
  3. If `s[read]` is not a space:
     - `s[write++] = s[read]`
  4. Null-terminate at `write`.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(1).
*/

void trimAllSpaces(char* s) {
    if (!s) return;
    int write = 0;
    for (int read = 0; s[read] != '\0'; read++) {
        if (s[read] != ' ') {
            s[write++] = s[read];
        }
    }
    s[write] = '\0';
}

int main() {
    char s[] = " Hello  How Are you  ? ";
    printf("Original:  \"%s\"\n", s);
    trimAllSpaces(s);
    printf("Trimmed:   \"%s\"\n", s);
    return 0;
}
