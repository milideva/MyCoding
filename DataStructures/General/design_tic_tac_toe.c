/**
 * Problem: Tic-Tac-Toe Design
 * Design a Tic-Tac-Toe game that is played between two players on a 3x3 grid.
 * 
 * Strategy: Array-based state tracking
 * Time Complexity: 
 * - move: O(1) if we track row/column/diagonal sums, O(N) if we scan.
 *   This implementation uses simple scanning for a 3x3 board.
 * Space Complexity: O(N^2) for the board.
 */

#include <stdio.h>
#include <stdbool.h>

#define SIZE 3

typedef enum { EMPTY = 0, PLAYER_X = 1, PLAYER_O = 2 } Player;

typedef struct {
    Player board[SIZE][SIZE];
    Player currentPlayer;
} TicTacToe;

/**
 * Initializes the game.
 */
void initGame(TicTacToe *game) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            game->board[i][j] = EMPTY;
        }
    }
    game->currentPlayer = PLAYER_X;
}

/**
 * Prints the board.
 */
void printBoard(TicTacToe *game) {
    printf("\n  0 1 2\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < SIZE; j++) {
            char c = '.';
            if (game->board[i][j] == PLAYER_X) c = 'X';
            if (game->board[i][j] == PLAYER_O) c = 'O';
            printf("%c ", c);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Checks if the current move resulted in a win.
 */
bool checkWin(TicTacToe *game, int row, int col) {
    Player p = game->board[row][col];

    // Check row
    if (game->board[row][0] == p && game->board[row][1] == p && game->board[row][2] == p) return true;

    // Check col
    if (game->board[0][col] == p && game->board[1][col] == p && game->board[2][col] == p) return true;

    // Check diagonals
    if (row == col) {
        if (game->board[0][0] == p && game->board[1][1] == p && game->board[2][2] == p) return true;
    }
    if (row + col == SIZE - 1) {
        if (game->board[0][2] == p && game->board[1][1] == p && game->board[2][0] == p) return true;
    }

    return false;
}

/**
 * Makes a move. Returns true if win, false otherwise.
 */
bool makeMove(TicTacToe *game, int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || game->board[row][col] != EMPTY) {
        printf("Invalid move! Try again.\n");
        return false;
    }

    game->board[row][col] = game->currentPlayer;
    if (checkWin(game, row, col)) {
        printBoard(game);
        printf("Player %c wins!\n", (game->currentPlayer == PLAYER_X ? 'X' : 'O'));
        return true;
    }

    // Switch player
    game->currentPlayer = (game->currentPlayer == PLAYER_X ? PLAYER_O : PLAYER_X);
    return false;
}

int main() {
    TicTacToe game;
    initGame(&game);

    printf("Starting Tic-Tac-Toe...\n");
    
    // Simulate a game
    makeMove(&game, 0, 0); // X
    makeMove(&game, 1, 1); // O
    makeMove(&game, 0, 1); // X
    makeMove(&game, 1, 0); // O
    makeMove(&game, 0, 2); // X wins

    return 0;
}
