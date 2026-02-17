/*

62. Unique Paths

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the
diagram below).

The robot can only move either down or right at any point in time. The robot is
trying to reach the bottom-right corner of the grid (marked 'Finish' in the
diagram below).

How many possible unique paths are there?
Example 1:

Input: m = 3, n = 7
Output: 28

Example 2:

Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down

Example 3:

Input: m = 7, n = 3
Output: 28

Example 4:

Input: m = 3, n = 3
Output: 6
*/

#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;

/*

https://www.reddit.com/r/cs2b/comments/1ab9k2h/tabulation_vs_memoization/

*/
class Solution {
  unordered_map <string, int> ij2val;

public:
  // Step 1
  // A simple recursive code
  int uniquePathsRecursive (int i, int j) {
    // base case
    if (i == 1 || j == 1) return 1;
    if (i == 0 || j == 0) return 0;
    return uniquePathsRecursive(i-1, j) + uniquePathsRecursive(i, j-1);
    // Time : 2^n + 2 ^m 
  }
  
  // Step 2 
  // It's easy to add memoization now
  // A top down approach, often with recursion
  int uniquePathsRecursiveMemoized (int i, int j) {
    string ij = to_string(i) + ":" + to_string(j);
    if (ij2val.find(ij) != ij2val.end()) {
      return ij2val[ij];
    }
    // base case
    if (i == 1 || j == 1) return 1;
    if (i == 0 || j == 0) return 0;

    int ret = uniquePathsRecursiveMemoized(i-1, j) + uniquePathsRecursiveMemoized(i, j-1);

    ij2val[ij] = ret;
    return ret;
  }

/*

  The problem with memoization is that if we are required to solve all problems (meaning more inputs) 
  and if we are not only looking for an optimal solution, then due to the recursive nature of memoization, 
  too many recursive calls could fill up the stack space. 

  This is where we would use tabulation instead since we don't need any overhead for the recursion and 
  can instead use a preallocated table/array.

  Use recursive approach for small set of subproblems (stack can overflow with large data set).
  Use iterative approach for large set of subproblems.

*/
  // Step 3 
  // Now it's easy to convert it to a dp array without recursion
  // A bottom up approach, often with iterative
  int uniquePathsIterativeTabulation (int m, int n) {
    int gridSum[m][n];
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        // base case : Pascal's triangle
        if (i == 0 || j == 0) {
          gridSum[i][j] = 1;
          continue;
        } 
        gridSum[i][j] = gridSum[i-1][j] + gridSum[i][j-1];  
      }
    }
    return gridSum[m-1][n-1];
  }

};

int main () {
  class Solution sol;
  int count;
  count = sol.uniquePathsRecursive(7, 3);
  cout << "#Unique paths recursive: " << count << endl;

  count = sol.uniquePathsRecursiveMemoized(7, 3);
  cout << "#Unique paths recursive memoized: " << count << endl;

  count = sol.uniquePathsIterativeTabulation(7, 3);
  cout << "#Unique paths DP: " << count << endl;

  return 0;
}
