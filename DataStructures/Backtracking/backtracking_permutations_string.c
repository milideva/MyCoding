#include <stdio.h>
#include <string.h>

/*
  Problem: String Permutations

  Problem Description:
  Given a string, return all possible permutations of its characters.

  Algorithm: Backtracking (Swap-based)
  1. Similar to integer permutations.
  2. Recursive function `permute(index)`.
  3. Base Case: `index == length`, print string.
  4. Recursive Step: Swap current index with every subsequent index, 
     recurse, and then swap back.

  Complexity Analysis:
  - Time Complexity: O(N * N!)
  - Space Complexity: O(N) for recursion stack.
*/

void swap(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void backtrack(char* s, int start, int end) {
    if (start == end) {
        printf("  %s\n", s);
        return;
    }

    for (int i = start; i <= end; i++) {
        swap(&s[start], &s[i]);
        backtrack(s, start + 1, end);
        swap(&s[start], &s[i]); // Backtrack
    }
}

void test(const char* input) {
    char s[100];
    strncpy(s, input, 99);
    s[99] = '\0';
    printf("Permutations of \"%s\":\n", s);
    backtrack(s, 0, strlen(s) - 1);
}

int main() {
    test("ABC");
    test("XY");
    return 0;
}
