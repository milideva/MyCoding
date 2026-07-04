#include <stdio.h>
#include <string.h>

/*
  Problem: Common Hash Functions Examples

  Description:
  Demonstrate various string hash functions commonly used in 
  hash tables.

  Complexity Analysis:
  - Time Complexity: O(length of string).
  - Space Complexity: O(1).
*/

// 1. DJB2 Hash (Daniel J. Bernstein)
// Known for being simple and having good distribution.
unsigned long hash_djb2(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

// 2. SDBM Hash
// Used in the SDBM database; also good for string hashing.
unsigned long hash_sdbm(const char* str) {
    unsigned long hash = 0;
    int c;
    while ((c = *str++)) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

// 3. Simple Sum Hash (Poor distribution, shown for educational purposes)
unsigned int hash_sum(const char* str) {
    unsigned int hash = 0;
    while (*str) hash += *str++;
    return hash;
}

int main() {
    const char* s1 = "apple";
    const char* s2 = "banana";

    printf("String: %s\n", s1);
    printf("  DJB2: %lu\n", hash_djb2(s1));
    printf("  SDBM: %lu\n", hash_sdbm(s1));
    printf("  Sum:  %u\n", hash_sum(s1));

    printf("\nString: %s\n", s2);
    printf("  DJB2: %lu\n", hash_djb2(s2));
    printf("  SDBM: %lu\n", hash_sdbm(s2));
    printf("  Sum:  %u\n", hash_sum(s2));

    return 0;
}
