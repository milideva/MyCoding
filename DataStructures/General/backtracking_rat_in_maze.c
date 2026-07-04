/**
 * Problem: Rat in a Maze
 * A rat starts from source (0,0) and has to reach destination (N-1, N-1).
 * The rat can move only in two directions: forward (right) and down.
 * In the maze matrix, 0 means the block is a dead end and 1 means the block 
 * can be used in the path.
 * 
 * Strategy: Backtracking
 * Time Complexity: O(2^(N^2)) - In the worst case, we explore two directions for each cell.
 * Space Complexity: O(N^2) - For the solution matrix and the recursion stack.
 */

#include <stdio.h>
#include <stdbool.h>

// Maze size
#define N 4

/**
 * A utility function to print the maze or solution matrix.
 */
static void printMatrix(int matrix[N][N], const char* message) {
    printf("%s:\n", message);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf(" %d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * A utility function to check if x,y is a valid index for N*N maze.
 */
static bool isSafe(int maze[N][N], int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1);
}

/**
 * A recursive utility function to solve the Maze problem using backtracking.
 */
static bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N]) {
    // If (x, y) is the destination, return true
    if (x == N - 1 && y == N - 1) {
        sol[x][y] = 1;
        return true;
    }

    // Check if maze[x][y] is valid
    if (isSafe(maze, x, y)) {
        // Mark x, y as part of solution path
        sol[x][y] = 1;

        // Move forward in x direction (down)
        if (solveMazeUtil(maze, x + 1, y, sol)) {
            return true;
        }

        // If moving in x direction doesn't give a solution, move in y direction (right)
        if (solveMazeUtil(maze, x, y + 1, sol)) {
            return true;
        }

        // If none of the above movements work, then BACKTRACK: unmark x, y
        sol[x][y] = 0;
        return false;
    }

    return false;
}

/**
 * This function solves the Maze problem using Backtracking.
 * It returns false if no path is possible, otherwise it returns true 
 * and prints the path.
 */
static bool solveMaze(int maze[N][N]) {
    int sol[N][N] = {0};

    if (solveMazeUtil(maze, 0, 0, sol) == false) {
        printf("Solution doesn't exist\n");
        return false;
    }

    printMatrix(sol, "Path to destination (1s mark the path)");
    return true;
}

int main() {
    int maze[N][N] = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };

    printMatrix(maze, "Original Maze (1 = open, 0 = wall)");
    solveMaze(maze);

    return 0;
}
