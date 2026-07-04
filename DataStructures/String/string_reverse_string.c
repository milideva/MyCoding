#include <stdio.h>
#include <string.h>

/*
  Problem: Reverse a String In-Place

  Algorithm: Two Pointers (Left and Right)
  1. Initialize `left = 0` and `right = n - 1`.
  2. While `left < right`:
     - Swap `s[left]` and `s[right]`.
     - Increment `left`, decrement `right`.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(1).
*/

void reverseString(char* s) {
    if (!s) return;
    int len = strlen(s);
    if (len <= 1) return;

    int left = 0, right = len - 1;
    while (left < right) {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++;
        right--;
    }
}

void test(const char* input) {
    char s[100];
    strcpy(s, input);
    printf("Original:  \"%s\"\n", s);
    reverseString(s);
    printf("Reversed:  \"%s\"\n\n", s);
}

int main() {
    test("devdatta");
    test("A");
    test("ABCDE");
    test("");
    return 0;
}
