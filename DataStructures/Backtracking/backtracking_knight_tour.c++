#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

/*
  Problem: Knight's Tour

  Problem Description:
  A knight is placed on the first block of an empty board. Moving 
  according to the rules of chess, the knight must visit every 
  square on the board exactly once. Print the sequence of moves.

  Algorithm: Backtracking (DFS)
  1. Represent the board as a 2D array, initialized to -1.
  2. Start at `(0, 0)` with `move_count = 0`.
  3. For the current position, try all 8 possible knight moves.
  4. If a move is within bounds and the cell is unvisited:
     - Mark the cell with `move_count`.
     - Recurse for the next move.
     - If recursion returns true (tour complete), we are done.
     - Otherwise, backtrack: Reset the cell to -1.
  5. Base Case: `move_count == N * N`.

  Complexity Analysis:
  - Time Complexity: O(8^(N^2))
    Reason: In the worst case, we explore a massive search tree. 
    However, pruning and move ordering (Warnsdorff's rule) can 
    significantly speed it up.
  - Space Complexity: O(N^2) for the board.
*/

#define BOARD_SIZE 5

class KnightTour {
    int board[BOARD_SIZE][BOARD_SIZE];
    int xMove[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int yMove[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    bool isSafe(int x, int y) {
        return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && board[x][y] == -1);
    }

    bool solveKTUtil(int x, int y, int moveCount) {
        if (moveCount == BOARD_SIZE * BOARD_SIZE) {
            return true;
        }

        for (int k = 0; k < 8; k++) {
            int nextX = x + xMove[k];
            int nextY = y + yMove[k];
            if (isSafe(nextX, nextY)) {
                board[nextX][nextY] = moveCount;
                if (solveKTUtil(nextX, nextY, moveCount + 1)) {
                    return true;
                }
                board[nextX][nextY] = -1; // Backtrack
            }
        }
        return false;
    }

public:
    void solve() {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) board[i][j] = -1;
        }

        board[0][0] = 0; // Start position
        if (solveKTUtil(0, 0, 1)) {
            printSolution();
        } else {
            cout << "Solution does not exist for N=" << BOARD_SIZE << endl;
        }
    }

    void printSolution() {
        cout << "Knight's Tour for N=" << BOARD_SIZE << ":" << endl;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                cout << " " << setw(2) << board[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    KnightTour kt;
    kt.solve();
    return 0;
}
