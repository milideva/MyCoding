/*
  LeetCode 269: Alien Dictionary

  Algorithm: Topological Sort (Kahn's BFS)
  1. Build a Directed Graph:
     - Compare adjacent words to find the first differing character.
     - An edge `u -> v` exists if `u` appears before `v` in the alien order.
     - Handle Edge Case: If word1 is a prefix of word2 but is longer 
       (e.g., "abc", "ab"), the order is invalid.
  2. Perform Topological Sort:
     - Use a queue for nodes with in-degree 0.
     - Detect cycles: If the result string size != number of unique characters, 
       a cycle exists (return "").

  Complexity Analysis:
  - Time Complexity: O(C)
    Reason: Where C is the total number of characters in all words combined. 
    Building the graph takes O(C) to compare adjacent words. The topological 
    sort takes O(V + E), where V is unique characters (max 26) and E is 
    edges (max V^2). Since V is constant, it's effectively O(C).
  - Space Complexity: O(1) or O(V + E)
    Reason: Adjacency list and in-degree map store up to 26 characters.

  Alternative Approaches:
  - DFS: Use recursion and a "visiting" state to detect cycles and post-order 
    traversal to determine order.
    - Comparison: Equally efficient. Kahn's BFS is often easier to debug 
      for cycle detection.

  Brute Force comparison:
  - Check every possible permutation of the alphabet to see if it satisfies 
    the given word order.
  - Time Complexity: O(26! * C).
  - Comparison: Impossible. Topological sort provides the correct linear 
    time solution.
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>

using namespace std;

/*

269. Alien Dictionary

There is a new alien language that uses the English alphabet. However,
the order among the letters is unknown to you.

You are given a list of strings words from the alien language's
dictionary, where the strings in words are sorted lexicographically by
the rules of this new language.

Return a string of the unique letters in the new alien language sorted
in lexicographically increasing order by the new language's rules. If
there is no solution, return "". If there are multiple solutions,
return any of them.

A string s is lexicographically smaller than a string t if at the
first letter where they differ, the letter in s comes before the
letter in t in the alien language. If the first min(s.length,
t.length) letters are the same, then s is smaller if and only if
s.length < t.length.

Example 1:

Input: words = ["wrt","wrf","er","ett","rftt"]
Output: "wertf"
Example 2:

Input: words = ["z","x"]
Output: "zx"
Example 3:

Input: words = ["z","x","z"]
Output: ""
Explanation: The order is invalid, so return "".


Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] consists of only lowercase English letters.
*/


/*

  https://en.wikipedia.org/wiki/Topological_sorting#Algorithms

  topo sort using BFS

  Kahn's algorithm:

  First, find a list of "start nodes" which have no incoming edges
  and insert them into a set S; at least one such node must exist in
  a non-empty acyclic graph. Then:


  L ← Empty list that will contain the sorted elements
  S ← Set of all nodes with no incoming edge

  while S is not empty do
    remove a node n from S
    add n to L
    for each node m with an edge e from n to m do
      remove edge e from the graph
      if m has no other incoming edges then
        insert m into S

  if graph has edges then
    return error   (graph has at least one cycle)
  else
    return L   (a topologically sorted order)


  An alternative algorithm for topological sorting is based on depth-first search.

  */

 /*
      a
     ↙ ↘
    b   c
   ↙ ↘ ↙ ↘
  d   e   f
       ↘
        g

  in-degree : number of Incoming edges. 
  indegree[a] = 0,  indegree[b] = 1,  indegree[c] = 1,  indegree[d] = 1,  indegree[e] = 2 ...

  A DAG (directed acyclic graph) must have at least one node with in-degree = 0. 
  If not, then it has a cycle and is not a DAG.
  (but having a node with in-degree 0, does not guarantee it's a DAG).

  We first build a graph. 
  for each edge u -> v
    record in-degree[v]++ ... as v has an incoming edge.
    graph[u].insert(v) ... insert v into the set of u which tracks all u's outgoing edges

  Now use classic BFS.
  We use a queue to start with the node with 0 incoming edges (in-degree is 0).
  Pop it off the queue, and add this to the result as we've no other dependency.
  then walk all its children/edges using the graph[u].set we built.
  decrement each child's incoming in-degree.
  if it's 0, then add it to the queue.
 */
class Solution {

  unordered_map <char, int> inDegree; // char->numCharsBefore
  unordered_map <char, unordered_set <char> > graph; // map of key, setOfChars that come after key char
  string result = "";

public:
  string alienOrder (vector <string> &words) {

    bool ret = buildGraph(words);

    if (ret == false)
      return result; // something went wrong in ordering

    bfsTopoSort();
    return result;
  }

private:
  bool buildGraph (vector <string> &words) {
    for (auto w : words) {
      for (auto c : w) {
        inDegree[c] = 0;
        graph[c] = unordered_set <char>();
      }
    }

    for (int i = 0; i < words.size() - 1; i++) {
      auto w1 = words[i];
      auto w2 = words[i + 1];
      if (w1.length() > w2.length() && w1.find(w2) == 0) {
        return false;
      }
      auto commonLen = min(w1.length(), w2.length());

      for (int j = 0; j < commonLen; j++) {
        auto parentCh = w1[j];
        auto childCh = w2[j];

        if (parentCh != childCh) {
          // First different character within commonLength
          // parentCh comes before childCh
          graph[parentCh].insert(childCh);
          // someone is before childCh
          inDegree[childCh]++;
          // The order of characters after this is meaningless.
          break;
        }
      }
    }

    return true;
  }

  void bfsTopoSort(void) {
    queue<char> q;
    for (auto [ch, count] : inDegree) {
      if (count == 0){
        q.push(ch);
      }
    }

    while (!q.empty()) {
      auto vertex = q.front();
      q.pop();
      result += vertex;
      // decrement the indegree for each child as we are removing the source vertex
      for (auto child : graph[vertex]) {
        inDegree[child]--;
        if (inDegree[child] == 0) {
          q.push(child);
        }
      }
    }

    if (result.size() != inDegree.size())
      result = "";
  }

};

int main() {

  class Solution sol;

  vector<string> words{"wrt", "wrf", "er", "ett", "rftt"};

  auto res = sol.alienOrder(words);

  cout << "Alien Dictionary : ";
  for (auto w : words) {
    cout << w << " ";
  }

  cout << endl << "Alien Order : " << res << endl;

  return 0;
}
