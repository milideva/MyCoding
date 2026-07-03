/*
  LeetCode 139: Word Break

  Algorithm: Breadth-First Search (BFS) on String Indices
  1. Treat the string as a graph where each index is a node. 
  2. An edge exists between index `i` and `j` if the substring `s[i...j-1]` 
     is a valid word in the dictionary.
  3. Starting from index 0, perform BFS to see if the end of the string 
     (index `s.length()`) is reachable.
  4. Use a `visited` array to avoid re-processing the same starting index.

  Complexity Analysis:
  - Time Complexity: O(N^3)
    Reason: There are N nodes in the graph (string indices). For each 
    node, we iterate up to N times to find all possible next words. 
    Inside the loop, `s.substr()` takes O(N) time. Total: O(N * N * N).
  - Space Complexity: O(N)
    Reason: To store the `visited` array and the BFS queue.

  Alternative Approaches:
  - Dynamic Programming (Optimal): `dp[i]` is true if `s[0...i-1]` can be 
    segmented. 
    - Time: O(N^2 * L) where L is max word length.
    - Comparison: DP is generally more memory efficient than BFS for 
      this problem and avoids the overhead of a queue.
  - DFS with Memoization: 
    - Logic: Recursive search with a `memo` map to store results of 
      subproblems.
    - Time: O(N^2).

  Brute Force Approach:
  - Try every possible split point in the string recursively without 
    memoization.
  - Time Complexity: O(2^N).
  - Comparison: BFS/DP reduces this to polynomial time by identifying 
    overlapping subproblems (same starting indices).
*/

#include <vector>
#include <unordered_set>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        
        unordered_set <string> dictSet (wordDict.begin(), wordDict.end());

        vector<bool> visited (s.length(), false);
        
        queue <int> q;
        q.push(0);
        
        while (!q.empty()) {
            int i = q.front(); q.pop();
            if (visited[i])
                continue;
            
            for (int j = i + 1; j <= s.length(); j++) {
                string sub = s.substr(i, j - i);
                if (dictSet.count(sub) != 0) {
                    q.push(j);
                    if (j == s.length()) {
                        return true;
                    }
                }
            }
            visited[i] = true;
        }
        
        return false;
    }
};


int main (void) {

  Solution sol;

  vector <string> vec = { "leet", "code" };

  bool ret = sol.wordBreak("leetcode", vec);
  cout << "leetcode wordBreak ret:" << ret << '\n';

  vector <string> vec2 = { "apple","pen" };
  ret = sol.wordBreak("applepenapple", vec2);
  cout << "applepenapple wordBreak ret:" << ret << '\n';

  vector <string> vec3 = {"cats","dog","sand","and","cat"};
  ret = sol.wordBreak("catsandog", vec3);
  cout << "catsandog  wordBreak ret:" << ret << '\n';

  return 0;
}
