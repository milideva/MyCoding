#include <stdio.h>

/*
  Problem: Custom strlen implementation

  Algorithm: Iterative Count
  1. Initialize `len = 0`.
  2. While the current character is not '\0':
     - Increment `len`.
     - Advance the pointer.
  3. Return `len`.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(1).
*/

size_t customStrlen(const char* s) {
    if (!s) return 0;
    size_t len = 0;
    while (*s++) len++;
    return len;
}

int main() {
    const char* s = "devdattaa";
    printf("String: \"%s\" -> Length: %zu\n", s, customStrlen(s));
    return 0;
}
