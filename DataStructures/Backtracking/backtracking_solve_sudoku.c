#include <stdio.h>
#include <stdbool.h>

/*
  Problem: Sudoku Solver (C version)

  Algorithm: Backtracking (DFS)
  - Same as C++ version but using a 2D integer array.
  - 0 represents an unassigned cell.

  Complexity Analysis:
  - Time Complexity: O(9^N).
  - Space Complexity: O(1) beyond stack.
*/

#define N 9
#define UNASSIGNED 0

bool findUnassignedLocation(int grid[N][N], int* row, int* col) {
    for (*row = 0; *row < N; (*row)++) {
        for (*col = 0; *col < N; (*col)++) {
            if (grid[*row][*col] == UNASSIGNED) return true;
        }
    }
    return false;
}

bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check row
    for (int i = 0; i < N; i++) if (grid[row][i] == num) return false;
    // Check col
    for (int i = 0; i < N; i++) if (grid[i][col] == num) return false;
    // Check 3x3 box
    int boxStartRow = row - row % 3;
    int boxStartCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + boxStartRow][j + boxStartCol] == num) return false;
        }
    }
    return true;
}

bool solveSudoku(int grid[N][N]) {
    int row, col;
    if (!findUnassignedLocation(grid, &row, &col)) return true;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) return true;
            grid[row][col] = UNASSIGNED; // Backtrack
        }
    }
    return false;
}

void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) printf("%2d", grid[row][col]);
        printf("\n");
    }
}

int main() {
    int grid[N][N] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    if (solveSudoku(grid)) printGrid(grid);
    else printf("No solution exists");

    return 0;
}
