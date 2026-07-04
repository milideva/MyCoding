#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/*
  Problem: Custom String to Uppercase

  Algorithm: Iterative Bit/Math Conversion
  1. For each character `c`:
     - If `c` is between 'a' and 'z':
       - `c = c - ('a' - 'A')`
  2. Alternatively, use `toupper(c)` from `ctype.h`.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(1) in-place or O(N) for new string.
*/

void toUppercaseInPlace(char* s) {
    if (!s) return;
    while (*s) {
        if (*s >= 'a' && *s <= 'z') {
            *s = *s - ('a' - 'A');
        }
        s++;
    }
}

int main() {
    char s[] = "devdatta";
    printf("Original: \"%s\"\n", s);
    toUppercaseInPlace(s);
    printf("Uppercase: \"%s\"\n", s);
    return 0;
}
