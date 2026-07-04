/**
 * Problem: Alien Dictionary
 * Given a sorted dictionary of words from an alien language, return the 
 * lexicographical order of characters in that language.
 * 
 * Strategy: Kahn's Algorithm (Topological Sort)
 * 1. Build a directed graph by comparing adjacent words to find the first 
 *    differing character (U -> V).
 * 2. Handle invalid case: If word1 is a prefix of word2 but is longer.
 * 3. Calculate in-degrees for all unique characters.
 * 4. Perform topological sort using a queue.
 * 5. If result length < number of unique chars, a cycle exists (return "").
 * 
 * Time Complexity: O(C) where C is total length of all words.
 * Space Complexity: O(1) as alphabet size is fixed (26).
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char, unordered_set<char>> adj;
        unordered_map<char, int> inDegree;

        // Initialize unique characters
        for (const string& w : words) {
            for (char c : w) {
                inDegree[c] = 0;
            }
        }

        // Build graph
        for (int i = 0; i < (int)words.size() - 1; i++) {
            string w1 = words[i];
            string w2 = words[i+1];
            
            // Check prefix case: "abc", "ab" is invalid
            if (w1.length() > w2.length() && w1.substr(0, w2.length()) == w2) return "";

            int len = min(w1.length(), w2.length());
            for (int j = 0; j < len; j++) {
                if (w1[j] != w2[j]) {
                    if (adj[w1[j]].find(w2[j]) == adj[w1[j]].end()) {
                        adj[w1[j]].insert(w2[j]);
                        inDegree[w2[j]]++;
                    }
                    break;
                }
            }
        }

        // Topological Sort
        queue<char> q;
        for (auto const& [c, degree] : inDegree) {
            if (degree == 0) q.push(c);
        }

        string result = "";
        while (!q.empty()) {
            char curr = q.front();
            q.pop();
            result += curr;

            for (char neighbor : adj[curr]) {
                if (--inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        return (result.length() == inDegree.size()) ? result : "";
    }
};

int main() {
    vector<string> words1 = {"wrt", "wrf", "er", "ett", "rftt"};
    Solution sol;
    cout << "Alien Order (Example 1): " << sol.alienOrder(words1) << " (Expected: wertf)" << endl;

    vector<string> words2 = {"z", "x", "z"};
    cout << "Alien Order (Example 2): " << sol.alienOrder(words2) << " (Expected: empty)" << endl;

    return 0;
}
