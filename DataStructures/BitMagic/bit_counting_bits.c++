#include <vector>
#include <iostream>
#include <string>

using namespace std;

/*
  LeetCode 338: Counting Bits

  Problem Description:
  Given an integer n, return an array ans of length n + 1 such that for each i 
  (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.

  Do not solve it with built-in functions (i.e., like __builtin_popcount in C++).

  Example 1:
  Input: n = 2
  Output: [0,1,1]
  Explanation:
  0 --> 0
  1 --> 1
  2 --> 10

  Example 2:
  Input: n = 5
  Output: [0,1,1,2,1,2]
  Explanation:
  0 --> 0
  1 --> 1
  2 --> 10
  3 --> 11
  4 --> 100
  5 --> 101

  Constraints:
  0 <= n <= 10^5

  Key Insight:
  For any integer i:
  - i >> 1 (Shift Right): Removes the least significant bit (LSB).
  - i & 1 (Bitwise AND): Checks if the LSB is 1 (odd) or 0 (even).
  Thus, the total number of set bits in i is simply the set bits in (i >> 1) 
  plus 1 if i is odd (or 0 if even):
      bits[i] = bits[i >> 1] + (i & 1)

  Complexity Analysis:
  - Time Complexity:
    - Best Case: O(N) where N = n.
    - Average Case: O(N).
    - Worst Case: O(N).
    Reason: We loop from 0 to n exactly once, executing O(1) constant-time 
    operations at each step.
  - Space Complexity:
    - Auxiliary Space: O(1) as we only use a few primitive variables.
    - Output Space: O(N) to store the resulting vector of size n + 1.
*/

class Solution {
public:
    vector<int> countBits(int n) {
        vector <int> res(n + 1, 0);

        for (unsigned int i = 0; i <= n; i++) {
            int idx = i >> 1;
            if (i % 2) {
                res[i] = res[idx] + 1;
            } else {
                res[i] = res[idx];
            }
        }
        return res;
    }
};

// =========================================================================
// TESTING HARNESS
// =========================================================================

void printVector(const vector<int>& vec) {
    cout << "[ ";
    for (int x : vec) {
        cout << x << " ";
    }
    cout << "]";
}

void runTest(const string& label, int n, const vector<int>& expected) {
    cout << "Testing: " << label << " (n = " << n << ")" << endl;
    Solution sol;
    vector<int> result = sol.countBits(n);

    cout << "  Result:   "; printVector(result); cout << endl;
    cout << "  Expected: "; printVector(expected); cout << " ";

    if (result == expected) {
        cout << "[PASS]" << endl;
    } else {
        cout << "[FAIL]" << endl;
    }
    cout << endl;
}

int main() {
    cout << "=========================================================" << endl;
    cout << "               RUNNING COUNTING BITS TESTS               " << endl;
    cout << "=========================================================" << endl;

    runTest("Example 1", 2, {0, 1, 1});
    runTest("Example 2", 5, {0, 1, 1, 2, 1, 2});
    runTest("Edge Case - Zero", 0, {0});
    runTest("Small Input - One", 1, {0, 1});

    cout << "=========================================================" << endl;
    return 0;
}
