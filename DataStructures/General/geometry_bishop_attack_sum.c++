/**
 * Problem: Bishop Attack Sum (X-Sum)
 * Given an NxM chessboard with non-negative integers in each cell, find the 
 * position to place a bishop such that the sum of all cells attacked by it 
 * is maximal. A bishop attacks all cells in its four diagonal directions.
 * 
 * Strategy: Diagonal Prefix Sums
 * There are two types of diagonals:
 * 1. Main diagonals: r - c is constant.
 * 2. Anti-diagonals: r + c is constant.
 * We can pre-calculate the sum for each diagonal to reduce complexity.
 * 
 * Time Complexity: O(N * M) - Pre-calculating diagonal sums and then scanning the board.
 * Space Complexity: O(N + M) - To store diagonal sums.
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

/**
 * Finds the maximum sum of cells attacked by a bishop.
 */
int getMaxBishopAttackSum(const vector<vector<int>>& board) {
    if (board.empty() || board[0].empty()) return 0;
    int N = board.size();
    int M = board[0].size();

    // Maps to store the sum of each diagonal
    // Main diagonals: r - c (key can be negative, so we add an offset or use a map)
    map<int, int> mainDiagSum;
    // Anti-diagonals: r + c
    map<int, int> antiDiagSum;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            mainDiagSum[i - j] += board[i][j];
            antiDiagSum[i + j] += board[i][j];
        }
    }

    int maxSum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // The sum for a bishop at (i, j) is sum(mainDiag) + sum(antiDiag) - board[i][j]
            // as board[i][j] is counted in both.
            int currentSum = mainDiagSum[i - j] + antiDiagSum[i + j] - board[i][j];
            if (currentSum > maxSum) {
                maxSum = currentSum;
            }
        }
    }

    return maxSum;
}

void test(const vector<vector<int>>& board, int expected) {
    int result = getMaxBishopAttackSum(board);
    cout << "Max Bishop Sum: " << result << " (Expected: " << expected << ") -> " 
         << (result == expected ? "PASS" : "FAIL") << endl;
}

int main() {
    vector<vector<int>> board1 = {
        {1, 2, 2, 1},
        {2, 4, 2, 4},
        {2, 2, 3, 1},
        {2, 4, 2, 4}
    };
    test(board1, 20);

    vector<vector<int>> board2 = {{1}, {0}};
    test(board2, 1);

    vector<vector<int>> board3 = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    test(board3, 5);

    return 0;
}
