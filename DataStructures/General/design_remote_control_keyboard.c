/**
 * Problem: Remote Control Keyboard
 * Given an onscreen keyboard with letters 'a' through 'z' laid out in 6 rows and 5 columns:
 * a b c d e
 * f g h i j
 * k l m n o
 * p q r s t
 * u v w x y
 * z
 * 
 * Using a remote control (up - 'u', down - 'd', left - 'l', right - 'r', enter - '!'), 
 * produce the sequence of key presses required to type out a given word.
 * 
 * Strategy: Manhattan Distance / Coordinate Calculation
 * - Map each character to (row, col) coordinates.
 * - Calculate horizontal and vertical moves required to reach the target character.
 * - Special handling for 'z' which is on its own row.
 * 
 * Time Complexity: O(Length of string)
 * Space Complexity: O(1)
 */

#include <stdio.h>
#include <ctype.h>

#define COLS 5

/**
 * Produces the sequence of key presses to move from current to target character and press enter.
 */
static void getPath(char current, char target) {
    if (current == target) {
        printf("! ");
        return;
    }

    int curr_idx = tolower(current) - 'a';
    int target_idx = tolower(target) - 'a';

    int curr_row = curr_idx / COLS;
    int curr_col = curr_idx % COLS;

    int target_row = target_idx / COLS;
    int target_col = target_idx % COLS;

    // To handle 'z' safely (it's at row 5, col 0), it's often better to move left/up 
    // before moving right/down if the target is 'z', or move up/right first if moving from 'z'.
    
    // Vertical moves
    while (curr_row < target_row) {
        // Special case: don't move down to row 5 unless col is 0
        if (curr_row == 4 && target_row == 5 && curr_col != 0) break; 
        printf("d ");
        curr_row++;
    }
    while (curr_row > target_row) {
        printf("u ");
        curr_row--;
    }

    // Horizontal moves
    while (curr_col < target_col) {
        printf("r ");
        curr_col++;
    }
    while (curr_col > target_col) {
        printf("l ");
        curr_col--;
    }

    // Final vertical move if we were blocked by 'z' row constraint
    while (curr_row < target_row) {
        printf("d ");
        curr_row++;
    }

    printf("! ");
}

/**
 * Prints the full sequence for a word.
 */
void printRemoteSequence(const char *word) {
    if (!word || !*word) return;

    printf("Sequence for \"%s\":\n", word);
    char current = 'a'; // Start at 'a'
    for (int i = 0; word[i] != '\0'; i++) {
        getPath(current, word[i]);
        current = word[i];
    }
    printf("\n\n");
}

int main() {
    printRemoteSequence("zebra");
    printRemoteSequence("leet");
    printRemoteSequence("code");
    return 0;
}
