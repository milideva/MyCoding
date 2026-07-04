/**
 * Problem: Word Search
 * Given an m x n grid of characters and a string word, return true if word 
 * exists in the grid. Construct word from sequentially adjacent cells.
 * 
 * Strategy: DFS + Backtracking
 * - Iterate through each cell. If it matches word[0], start a DFS.
 * - In DFS, mark current cell as visited (e.g., by changing to '#').
 * - Recursively explore 4-directional neighbors for the next character.
 * - If found, return true.
 * - Backtrack by restoring the original character.
 * 
 * Time Complexity: O(N * 3^L) where N is number of cells, L is word length.
 * Space Complexity: O(L)
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
    bool dfs(vector<vector<char>>& board, int r, int c, int index, const string& word) {
        if (index == (int)word.length()) return true;
        
        int m = board.size();
        int n = board[0].size();

        if (r < 0 || r >= m || c < 0 || c >= n || board[r][c] != word[index]) {
            return false;
        }

        char temp = board[r][c];
        board[r][c] = '#'; // Mark as visited

        bool found = dfs(board, r + 1, c, index + 1, word) ||
                     dfs(board, r - 1, c, index + 1, word) ||
                     dfs(board, r, c + 1, index + 1, word) ||
                     dfs(board, r, c - 1, index + 1, word);

        board[r][c] = temp; // Backtrack
        return found;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty()) return false;
        int m = board.size();
        int n = board[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(board, i, j, 0, word)) return true;
            }
        }
        return false;
    }
};

int main() {
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    Solution sol;
    cout << "Word \"ABCCED\" exists: " << (sol.exist(board, "ABCCED") ? "True" : "False") << " (Expected: True)" << endl;
    cout << "Word \"SEE\" exists: " << (sol.exist(board, "SEE") ? "True" : "False") << " (Expected: True)" << endl;
    cout << "Word \"ABCB\" exists: " << (sol.exist(board, "ABCB") ? "True" : "False") << " (Expected: False)" << endl;

    return 0;
}
