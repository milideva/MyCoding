#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
  LeetCode 151: Reverse Words in a String

  Problem Description:
  Given an input string `s`, reverse the order of the words. 
  A word is defined as a sequence of non-space characters. The words 
  in `s` will be separated by at least one space.

  Return a string of the words in reverse order concatenated by a 
  single space.

  Algorithm: Reverse All then Reverse Each Word
  1. Reverse the entire string.
  2. Iterate through the reversed string:
     - Find the start and end of each word.
     - Reverse each individual word back to its original form.
  3. Clean up leading, trailing, and multiple spaces (if required by 
     LeetCode version).

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Two passes through the string.
  - Space Complexity: O(1) in-place modification.
*/

void reverseRange(char* s, int start, int end) {
    while (start < end) {
        char temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

void reverseWords(char* s) {
    if (!s) return;
    int n = strlen(s);

    // 1. Reverse the entire string
    reverseRange(s, 0, n - 1);

    // 2. Reverse each word in place
    int start = 0;
    for (int end = 0; end <= n; end++) {
        if (s[end] == ' ' || s[end] == '\0') {
            reverseRange(s, start, end - 1);
            start = end + 1;
        }
    }
}

void test(const char* input) {
    char s[100];
    strcpy(s, input);
    printf("Input:  \"%s\"\n", s);
    reverseWords(s);
    printf("Output: \"%s\"\n\n", s);
}

int main() {
    test("I am a cool dude");
    test("Hello World");
    test("Backtracking");
    return 0;
}
