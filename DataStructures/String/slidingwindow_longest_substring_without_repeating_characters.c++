#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
  LeetCode 3: Longest Substring Without Repeating Characters

  Problem Description:
  Given a string `s`, find the length of the longest substring 
  without repeating characters.

  Example 1:
  Input: s = "abcabcbb"
  Output: 3
  Explanation: The answer is "abc", with the length of 3.

  Algorithm: Sliding Window (Optimized)
  1. Use a hash map (or frequency array for ASCII) to store the 
     last seen index of each character.
  2. Maintain two pointers: `l` (left) and `r` (right).
  3. Iterate with `r` from 0 to n-1:
     - If `s[r]` was seen before and its last index is within 
       the current window (`lastSeen[s[r]] >= l`):
       - Move `l` to `lastSeen[s[r]] + 1` to exclude the repeating 
         character.
     - Update `maxLen = max(maxLen, r - l + 1)`.
     - Update `lastSeen[s[r]] = r`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Each character is visited at most twice (once by `r` 
    and once by `l`). With the index map optimization, each 
    character is visited only once by `r`.
  - Space Complexity: O(min(M, N)) or O(128)
    Reason: To store the last seen indices of characters.
*/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> lastSeen(128, -1);
        int maxLen = 0;
        int l = 0;

        for (int r = 0; r < s.length(); ++r) {
            if (lastSeen[s[r]] >= l) {
                l = lastSeen[s[r]] + 1;
            }
            lastSeen[s[r]] = r;
            maxLen = max(maxLen, r - l + 1);
        }
        return maxLen;
    }
};

void test(const string& label, string s, int expected) {
    cout << "Testing: " << label << " (\"" << s << "\")" << endl;
    Solution sol;
    int result = sol.lengthOfLongestSubstring(s);
    if (result == expected) {
        cout << "  [PASS] Length: " << result << endl;
    } else {
        cout << "  [FAIL] Result: " << result << " (Expected: " << expected << ")" << endl;
    }
}

int main() {
    test("Example 1", "abcabcbb", 3);
    test("All Same", "bbbbb", 1);
    test("Example 3", "pwwkew", 3);
    test("Empty String", "", 0);
    test("Tricky Case", "tmmzuxt", 5);
    return 0;
}
