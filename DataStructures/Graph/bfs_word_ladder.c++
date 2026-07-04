/**
 * Problem: Word Ladder
 * Find the length of the shortest transformation sequence from beginWord to 
 * endWord using wordList. Each adjacent pair must differ by exactly one letter.
 * 
 * Strategy: BFS (Shortest Path in Unweighted Graph)
 * - Use a hash set for wordList for O(1) lookups.
 * - Start BFS from beginWord.
 * - For each word, try changing each character to all letters 'a'-'z'.
 * - If mutated word is in the set, add it to queue and remove from set (mark visited).
 * 
 * Time Complexity: O(N * L^2) where N is num words and L is word length.
 * Space Complexity: O(N * L)
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (dict.find(endWord) == dict.end()) return 0;

        queue<string> q;
        q.push(beginWord);
        int length = 1;

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                string curr = q.front();
                q.pop();

                if (curr == endWord) return length;

                for (int j = 0; j < (int)curr.length(); j++) {
                    char original = curr[j];
                    for (char c = 'a'; c <= 'z'; c++) {
                        curr[j] = c;
                        if (curr == endWord) return length + 1;
                        if (dict.count(curr)) {
                            q.push(curr);
                            dict.erase(curr);
                        }
                    }
                    curr[j] = original; // Restore
                }
            }
            length++;
        }

        return 0;
    }
};

int main() {
    string begin = "hit", end = "cog";
    vector<string> list = {"hot", "dot", "dog", "lot", "log", "cog"};

    Solution sol;
    cout << "Word Ladder length: " << sol.ladderLength(begin, end, list) << " (Expected: 5)" << endl;

    return 0;
}
