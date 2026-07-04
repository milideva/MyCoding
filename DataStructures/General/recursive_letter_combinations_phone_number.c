/**
 * Problem: Letter Combinations of a Phone Number
 * Given a string containing digits from 2-9 inclusive, return all possible 
 * letter combinations that the number could represent.
 * 
 * Mapping:
 * 2: "abc", 3: "def", 4: "ghi", 5: "jkl", 6: "mno", 7: "pqrs", 8: "tuv", 9: "wxyz"
 * 
 * Strategy: Backtracking / Recursion
 * - For each digit, explore all possible characters it can represent.
 * - Recursively move to the next digit.
 * - Base case: All digits processed, print/store the combination.
 * 
 * Time Complexity: O(4^N) where N is the number of digits.
 * Space Complexity: O(N) for recursion stack and output buffer.
 */

#include <stdio.h>
#include <string.h>

static const char* mapping[] = {
    "",     // 0
    "",     // 1
    "abc",  // 2
    "def",  // 3
    "ghi",  // 4
    "jkl",  // 5
    "mno",  // 6
    "pqrs", // 7
    "tuv",  // 8
    "wxyz"  // 9
};

/**
 * Recursive function to generate letter combinations.
 */
void generateCombinations(const char* digits, int index, char* output) {
    if (digits[index] == '\0') {
        output[index] = '\0';
        printf("%s ", output);
        return;
    }

    int digit = digits[index] - '0';
    const char* letters = mapping[digit];

    for (int i = 0; letters[i] != '\0'; i++) {
        output[index] = letters[i];
        generateCombinations(digits, index + 1, output);
    }
}

int main() {
    const char* testDigits = "23";
    char output[10];

    printf("Combinations for \"%s\":\n", testDigits);
    generateCombinations(testDigits, 0, output);
    printf("\n\n");

    const char* testDigits2 = "7";
    printf("Combinations for \"%s\":\n", testDigits2);
    generateCombinations(testDigits2, 0, output);
    printf("\n");

    return 0;
}
