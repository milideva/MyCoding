/**
 * Problem: Word Break
 * Given a string s and a dictionary wordDict, return true if s can be 
 * segmented into one or more dictionary words.
 * 
 * Strategy: BFS on string indices
 * - Treat each index in the string as a node.
 * - An edge exists from index i to j if s[i...j-1] is in wordDict.
 * - Start BFS from index 0.
 * - If index n (end of string) is reachable, return true.
 * - Use a visited array to avoid redundant work.
 * 
 * Time Complexity: O(N^3) due to substring creation and search.
 * Space Complexity: O(N)
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = s.length();
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int start = q.front();
            q.pop();

            if (start == n) return true;

            for (int end = start + 1; end <= n; end++) {
                string sub = s.substr(start, end - start);
                if (dict.count(sub)) {
                    if (end == n) return true;
                    if (!visited[end]) {
                        q.push(end);
                        visited[end] = true;
                    }
                }
            }
        }

        return false;
    }
};

int main() {
    Solution sol;
    vector<string> dict1 = {"leet", "code"};
    cout << "wordBreak(\"leetcode\"): " << (sol.wordBreak("leetcode", dict1) ? "True" : "False") << " (Expected: True)" << endl;

    vector<string> dict2 = {"cats", "dog", "sand", "and", "cat"};
    cout << "wordBreak(\"catsandog\"): " << (sol.wordBreak("catsandog", dict2) ? "True" : "False") << " (Expected: False)" << endl;

    return 0;
}
