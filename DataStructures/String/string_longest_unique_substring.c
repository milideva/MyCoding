#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
  Problem: Longest Substring with Exactly K Unique Characters

  Problem Description:
  Given a string and an integer K, find the length of the longest 
  substring that contains exactly K unique characters.

  Algorithm: Sliding Window
  1. Use two pointers `left` and `right` to define a window.
  2. Use a frequency array (size 256) to track characters in the window.
  3. Maintain a `uniqueCount` of characters currently in the window.
  4. Iterate with `right` from 0 to N-1:
     - Add `s[right]` to window. If frequency becomes 1, increment `uniqueCount`.
     - While `uniqueCount > K`:
       - Remove `s[left]` from window. If frequency becomes 0, decrement `uniqueCount`.
       - Increment `left`.
     - If `uniqueCount == K`, update `maxLen = max(maxLen, right - left + 1)`.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(1) (fixed size 256 array).
*/

int longestKUnique(const char* s, int k) {
    if (!s || k <= 0) return 0;
    int n = strlen(s);
    int freq[256] = {0};
    int uniqueCount = 0;
    int maxLen = -1;
    int left = 0;

    for (int right = 0; right < n; right++) {
        if (freq[(unsigned char)s[right]] == 0) uniqueCount++;
        freq[(unsigned char)s[right]]++;

        while (uniqueCount > k) {
            freq[(unsigned char)s[left]]--;
            if (freq[(unsigned char)s[left]] == 0) uniqueCount--;
            left++;
        }

        if (uniqueCount == k) {
            int currLen = right - left + 1;
            if (currLen > maxLen) maxLen = currLen;
        }
    }
    return maxLen;
}

void test(const char* s, int k) {
    int res = longestKUnique(s, k);
    printf("String: \"%s\", K: %d -> Max Length: %d\n", s, k, res);
}

int main() {
    test("aabbcc", 1); // 2 ("aa")
    test("aabbcc", 2); // 4 ("aabb")
    test("aabbcc", 3); // 6 ("aabbcc")
    test("aabacbebebe", 3); // 7 ("cbebebe")
    return 0;
}
