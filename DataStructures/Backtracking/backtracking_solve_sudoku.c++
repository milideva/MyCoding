#include <vector>
#include <iostream>

using namespace std;

/*
  LeetCode 37: Sudoku Solver

  Problem Description:
  Write a program to solve a Sudoku puzzle by filling the empty cells. 
  The board is a 9x9 grid, and it is guaranteed that a unique solution 
  exists.

  Algorithm: Backtracking (DFS)
  1. Iterate through every cell in the grid.
  2. If a cell is empty ('.'):
     - Try placing each digit from '1' to '9'.
     - Check if the digit is valid in the current row, column, and 
       3x3 box.
     - If valid, place the digit and recurse to solve the rest of 
       the board.
     - If the recursion returns true, the puzzle is solved.
     - Otherwise, backtrack: Reset the cell to '.' and try the 
       next digit.
  3. If all cells are filled, return true.

  Complexity Analysis:
  - Time Complexity: O(9^(N)) where N is the number of empty cells. 
    In practice, pruning makes it much faster.
  - Space Complexity: O(1) beyond the recursion stack (9x9 grid is fixed).
*/

class Solution {
    bool isValid(vector<vector<char>>& board, int row, int col, char c) {
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == c) return false;
            if (board[row][i] == c) return false;
            if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c) return false;
        }
        return true;
    }

public:
    bool solveSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    for (char c = '1'; c <= '9'; c++) {
                        if (isValid(board, i, j, c)) {
                            board[i][j] = c;
                            if (solveSudoku(board)) return true;
                            board[i][j] = '.'; // Backtrack
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
};

void printBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
            if ((j + 1) % 3 == 0 && j < 8) cout << "| ";
        }
        cout << endl;
        if ((i + 1) % 3 == 0 && i < 8) cout << "---------------------" << endl;
    }
}

int main() {
    vector<vector<char>> board = {
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

    Solution sol;
    cout << "Original Board:" << endl;
    printBoard(board);
    
    if (sol.solveSudoku(board)) {
        cout << "\nSolved Board:" << endl;
        printBoard(board);
    } else {
        cout << "\nNo solution exists." << endl;
    }

    return 0;
}
