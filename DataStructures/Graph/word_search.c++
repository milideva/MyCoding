/*
  LeetCode 79: Word Search

  Algorithm: DFS with Backtracking
  1. Iterate through each cell in the grid. If it matches the first letter 
     of the word, start a DFS.
  2. In DFS:
     - Mark the current cell as `visited`.
     - Recursively explore all 4 neighbors for the next character in the word.
     - If the word is found, return true.
     - Backtrack: Mark the current cell as `unvisited` before returning to 
       the caller.

  Complexity Analysis:
  - Time Complexity: O(N * 3^L)
    Reason: N is the number of cells in the grid. L is the length of the 
    word. For each starting cell, we explore 4 directions initially, 
    and then 3 directions (excluding the one we came from) for each 
    remaining character. 
  - Space Complexity: O(L)
    Reason: The maximum depth of the recursion stack is the length of 
    the word.

  Alternative Approaches:
  - BFS: Difficult to implement because each path requires its own 
    `visited` state to ensure we don't reuse cells within the same path.
  - Trie + DFS (LC 212 - Word Search II): If we were searching for multiple 
    words at once, a Trie would allow us to prune paths that don't match 
    any prefix.

  Brute Force comparison:
  - Generating all possible paths of length L in the grid and checking if 
    any match the word.
  - Time Complexity: O(N * 4^L).
  - Comparison: DFS with backtracking is the optimized way to perform 
    this exhaustive search, as it prunes the search tree as soon as 
    a character mismatch occurs.
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
    int r;
    int c;
    bool isSafe (int i, int j) {
        if (i < 0 or j < 0 or i >= r or j >= c )
            return false;
        return true;
    }
    int x[4] = { 0, 0, +1, -1};
    int y[4] = { +1, -1, 0, 0};

    bool dfs (vector<vector<char>>& board, int i, int j,
            vector<vector<bool>>& visited, string& word, int wi) {
        
        if (wi == word.size() - 1)
            return true;
        if (!isSafe(i, j)) 
            return false;
        visited[i][j] = true;
        for (int k = 0; k < 4; k++) {
            int ix = i + x[k];
            int jy = j + y[k];
            if (word[wi+1] != board[ix][jy] or visited[ix][jy])
                continue;

            // Typical mistake#1, return dfs unconditionally
            // should return true only if word is found
            // otherwise if dfs returns false, continue the loop to try other neighbors
            if (dfs(board, ix, jy, visited, word, wi+1)) 
                return true;
        }
        // Typical mistake#2, must backtrack here
        // The word was not found, mark it unvisited
        visited[i][j] = false;
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty())
            return false;
        
        int rows = board.size();
        int cols = board[0].size();
        r = rows; 
        c = cols;
        vector <vector <bool>> visited(r, vector<bool> (c, false));

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (word[0] != board[i][j] or visited[i][j])
                    continue;
                bool found = dfs(board, i, j, visited, word, 0);
                if (found) {
                    return true;
                }
            }
        }
        return false;
    }
};

void printBoard (vector <vector <char>> &board) {
    cout << endl << "Board: " << endl;
    for (auto v : board) {
        for (auto ch : v) {
            cout << ch << " ";
        }
        cout << endl;
    }
}
bool test (vector <vector <char>> &board, string word) {
    Solution sol;
    printBoard(board);
    cout << "word: " << word << endl;
    return sol.exist(board, word);
}

int main (void) {

    vector <vector <char>> board = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    string word = "ABCCED";
    bool output = test(board, word);
    cout << "found:" << output << endl;
    
    word = "SEE";
    output = test(board, word);
    cout << "found:" << output << endl;
    
    word = "ABCB";
    output = test(board, word);
    cout << "found:" << output << endl;
    
    board = {{'C','A','A'},{'A','A','A'},{'B','C','D'}};
    word = "AAB";
    output = test(board, word);
    cout << "found:" << output << endl;
    
    
    return 0;
}