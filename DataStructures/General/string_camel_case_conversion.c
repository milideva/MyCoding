/**
 * Problem: CamelCase to Underscore Notation
 * Convert a CamelCase string to underscore_notation (snake_case).
 * Do not add an underscore if the first letter is uppercase.
 * 
 * Example: "DevdattaAjgaonkar" -> "devdatta_ajgaonkar"
 * 
 * Strategy: Linear Scan
 * - Iterate through the string.
 * - If an uppercase letter is found (and it's not the first character), 
 *   prepend an underscore and convert it to lowercase.
 * - Otherwise, just convert/copy the character.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N) for the output string.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Converts CamelCase to underscore_notation.
 * The caller is responsible for ensuring 'out' has enough space.
 */
void camelToSnake(const char *in, char *out) {
    if (!in || !out) return;

    int i = 0, j = 0;
    while (in[i] != '\0') {
        if (isupper(in[i])) {
            // Add underscore if it's not the first character
            if (i != 0) {
                out[j++] = '_';
            }
            out[j++] = tolower(in[i]);
        } else {
            out[j++] = in[i];
        }
        i++;
    }
    out[j] = '\0';
}

int main() {
    const char *input = "DevdattaAjgaonkar";
    char output[100];

    camelToSnake(input, output);
    printf("Input: %s\nOutput: %s\n", input, output);

    const char *input2 = "thisIsACamelCaseString";
    camelToSnake(input2, output);
    printf("Input: %s\nOutput: %s\n", input2, output);

    return 0;
}
