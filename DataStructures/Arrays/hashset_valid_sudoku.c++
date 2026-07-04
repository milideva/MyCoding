#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

/*
  LeetCode 36: Valid Sudoku

  Problem Description:
  Determine if a 9 x 9 Sudoku board is valid. Only the filled cells 
  need to be validated according to the following rules:
  1. Each row must contain the digits 1-9 without repetition.
  2. Each column must contain the digits 1-9 without repetition.
  3. Each of the nine 3 x 3 sub-boxes of the grid must contain the 
     digits 1-9 without repetition.

  Note: A valid board is not necessarily solvable.

  Algorithm: Hash Sets (or Frequency Arrays)
  1. Use three sets of 9 frequency arrays (or boolean arrays) to track:
     - Digits seen in each row.
     - Digits seen in each column.
     - Digits seen in each 3x3 square.
  2. Iterate through every cell `(i, j)` on the board.
  3. If the cell contains a digit `d`:
     - Calculate square index: `k = (i / 3) * 3 + (j / 3)`.
     - Check if `d` has already been seen in `row[i]`, `col[j]`, 
       or `square[k]`.
     - If yes, return false.
     - Otherwise, mark `d` as seen in all three.
  4. If all cells pass, return true.

  Complexity Analysis:
  - Time Complexity: O(1)
    Reason: The board size is fixed at 9x9 (81 cells).
  - Space Complexity: O(1)
    Reason: Fixed size tracking arrays.

  Brute Force comparison:
  - Check rows, then columns, then squares in separate passes.
  - Time: O(81 * 3) = O(1).
  - Single pass is slightly more elegant.
*/

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool rows[9][9] = {false};
        bool cols[9][9] = {false};
        bool squares[9][9] = {false};

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') continue;

                int d = board[i][j] - '1'; // 0-indexed digit
                int k = (i / 3) * 3 + (j / 3);

                if (rows[i][d] || cols[j][d] || squares[k][d]) {
                    return false;
                }

                rows[i][d] = cols[j][d] = squares[k][d] = true;
            }
        }
        return true;
    }
};

void test(const string& label, vector<vector<char>> board, bool expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    bool result = sol.isValidSudoku(board);
    cout << "  [" << (result == expected ? "PASS" : "FAIL") << "] Result: " << boolalpha << result << endl;
}

int main() {
    vector<vector<char>> board1 = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    test("Valid Board", board1, true);

    vector<vector<char>> board2 = board1;
    board2[0][0] = '8'; // Duplicate 8 in row 0
    test("Invalid Board (Duplicate in Row)", board2, false);

    return 0;
}
