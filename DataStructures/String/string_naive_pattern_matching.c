#include <stdio.h>
#include <string.h>

/*
  Problem: Naive Pattern Matching

  Problem Description:
  Given a string `txt` and a pattern `pat`, return all indices where 
  `pat` occurs in `txt`.

  Algorithm: Sliding Window / Brute Force
  1. Iterate through `txt` with index `i` from 0 to `N - M`.
  2. For each `i`, check if the substring `txt[i...i+M-1]` matches `pat`.
  3. If matched, record or print the index `i`.

  Complexity Analysis:
  - Time Complexity: O(N * M)
    Reason: We check each possible starting position.
  - Space Complexity: O(1).

  Alternative Approaches:
  - KMP (Knuth-Morris-Pratt): O(N + M) using a failure function.
  - Rabin-Karp: O(N + M) using rolling hash.
*/

void naiveSearch(const char* txt, const char* pat) {
    int N = strlen(txt);
    int M = strlen(pat);

    printf("Searching for \"%s\" in \"%s\":\n", pat, txt);
    bool found = false;
    for (int i = 0; i <= N - M; i++) {
        int j;
        for (j = 0; j < M; j++) {
            if (txt[i + j] != pat[j]) break;
        }
        if (j == M) {
            printf("  Pattern found at index %d\n", i);
            found = true;
        }
    }
    if (!found) printf("  Pattern not found.\n");
}

int main() {
    naiveSearch("AABAACAADAABAAABAA", "AABA");
    naiveSearch("devdatta", "da");
    naiveSearch("abcbcglx", "bcgl");
    return 0;
}
