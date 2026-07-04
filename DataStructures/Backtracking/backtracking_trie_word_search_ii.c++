#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

/*
  LeetCode 212: Word Search II

  Problem Description:
  Given an m x n board of characters and a list of strings `words`, 
  return all words on the board. Each word must be constructed from 
  letters of sequentially adjacent cells. The same letter cell may 
  not be used more than once in a word.

  Algorithm: Trie + Backtracking
  1. Build a Trie from the given list of `words`.
  2. For each cell `(r, c)` on the board:
     - If the character `board[r][c]` is a child of the Trie root:
       - Start a DFS/Backtracking from this cell.
  3. Backtracking:
     - Maintain the current Trie node.
     - If the current node contains a complete word, add it to 
       results and clear the word in the node (to avoid duplicates).
     - Mark the current cell as visited (e.g., using '#').
     - Explore all 4 neighbors.
     - Restore the cell (backtrack).
  4. Optimization: Remove leaf nodes from the Trie as words are found.

  Complexity Analysis:
  - Time Complexity: O(M * N * 4^L)
    Reason: M*N cells. L is the max length of a word. At each step, 
    we have 4 directions.
  - Space Complexity: O(Total characters in words) for the Trie.
*/

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    string word = "";
    
    ~TrieNode() {
        for (auto const& [ch, child] : children) delete child;
    }
};

class Solution {
    void backtrack(vector<vector<char>>& board, int r, int c, TrieNode* node, vector<string>& result) {
        char ch = board[r][c];
        if (!node->children.count(ch)) return;

        TrieNode* nextNode = node->children[ch];
        if (!nextNode->word.empty()) {
            result.push_back(nextNode->word);
            nextNode->word = ""; // Found it, don't find it again
        }

        board[r][c] = '#'; // Mark visited
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < board.size() && nc >= 0 && nc < board[0].size() && board[nr][nc] != '#') {
                backtrack(board, nr, nc, nextNode, result);
            }
        }

        board[r][c] = ch; // Restore
        
        // Pruning: if leaf node, remove it
        if (nextNode->children.empty()) {
            node->children.erase(ch);
        }
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode* root = new TrieNode();
        for (const string& w : words) {
            TrieNode* curr = root;
            for (char c : w) {
                if (!curr->children.count(c)) curr->children[c] = new TrieNode();
                curr = curr->children[c];
            }
            curr->word = w;
        }

        vector<string> result;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                backtrack(board, i, j, root, result);
            }
        }

        delete root;
        return result;
    }
};

void test(vector<vector<char>> board, vector<string> words) {
    cout << "Testing Word Search II" << endl;
    Solution sol;
    vector<string> result = sol.findWords(board, words);
    cout << "  Found: [ ";
    for (const string& s : result) cout << "\"" << s << "\" ";
    cout << "]" << endl;
}

int main() {
    test({{'o','a','a','n'},{'e','t','a','e'},{'i','h','k','r'},{'i','f','l','v'}}, 
         {"oath","pea","eat","rain"});
    test({{'a','b'},{'c','d'}}, {"abcb"});
    return 0;
}
