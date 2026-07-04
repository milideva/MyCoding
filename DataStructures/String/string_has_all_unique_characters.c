#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*
  Problem: Determine if a String has All Unique Characters

  Algorithm 1: Boolean Array (Hash Map)
  1. Create a boolean array of size 256 (for extended ASCII).
  2. For each character in the string, check if its entry is true.
  3. If true, return false (duplicate found).
  4. Else, set entry to true.

  Algorithm 2: Bitmask (Space Efficient for lowercase a-z)
  1. Use an integer as a bitset (32 bits for 26 letters).
  2. For each character `c`:
     - `val = c - 'a'`
     - If `(mask & (1 << val)) > 0`, return false.
     - `mask |= (1 << val)`

  Algorithm 3: No Extra Data Structures
  1. Sort the string (O(N log N)).
  2. Linearly check adjacent characters.

  Complexity Analysis (Algorithm 1):
  - Time Complexity: O(N)
  - Space Complexity: O(1) (fixed size 256 array).
*/

bool hasUniqueChars(const char* s) {
    if (!s) return true;
    bool seen[256] = {false};
    
    for (int i = 0; s[i] != '\0'; i++) {
        unsigned char c = (unsigned char)s[i];
        if (seen[c]) return false;
        seen[c] = true;
    }
    return true;
}

void test(const char* s) {
    printf("String: \"%s\" -> Unique: %s\n", s, 
           hasUniqueChars(s) ? "Yes" : "No");
}

int main() {
    test("ABCd");
    test("AAAABBBB");
    test("Devdatta");
    test("Unique");
    test("");
    return 0;
}
