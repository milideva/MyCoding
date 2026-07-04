/**
 * Problem: Remove Duplicate Characters
 * Remove duplicate characters from a string in-place.
 * 
 * Example: "devdatta" -> "devat"
 * 
 * Strategy: Hash Map (Frequency Array) + Two Pointers
 * 1. Use a boolean array of size 256 to track characters already seen.
 * 2. Use two pointers: 'i' for reading and 'j' for writing.
 * 3. For each character at 'i', if it hasn't been seen, write it to 'j' and mark as seen.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1) - Constant space for the boolean array.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Removes duplicate characters from a string in-place.
 */
void removeDuplicates(char *str) {
    if (!str) return;

    bool seen[256] = {false};
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (!seen[c]) {
            seen[c] = true;
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char s1[] = "devdatta";
    printf("Original: %s\n", s1);
    removeDuplicates(s1);
    printf("Removed Duplicates: %s\n", s1);

    char s2[] = "google";
    printf("Original: %s\n", s2);
    removeDuplicates(s2);
    printf("Removed Duplicates: %s\n", s2);

    return 0;
}
