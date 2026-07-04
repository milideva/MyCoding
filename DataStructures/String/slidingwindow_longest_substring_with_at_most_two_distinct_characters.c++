#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

/*
  LeetCode 159: Longest Substring with At Most Two Distinct Characters

  Problem Description:
  Given a string `s`, return the length of the longest substring that 
  contains at most two distinct characters.

  Algorithm: Sliding Window (Special case of k=2)
  1. Use two pointers `l` and `r` to define a window.
  2. Maintain a frequency map of characters.
  3. Iterate with `r` from 0 to n-1:
     - Add `s[r]` to the map.
     - While the map size > 2:
       - Decrement frequency of `s[l]`.
       - If frequency becomes 0, remove `s[l]` from the map.
       - Increment `l`.
     - Update `maxLen = max(maxLen, r - l + 1)`.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(1) (Hash map stores at most 3 characters).
*/

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        unordered_map<char, int> freq;
        int l = 0, maxLen = 0;

        for (int r = 0; r < s.length(); ++r) {
            freq[s[r]]++;
            while (freq.size() > 2) {
                if (--freq[s[l]] == 0) {
                    freq.erase(s[l]);
                }
                l++;
            }
            maxLen = max(maxLen, r - l + 1);
        }
        return maxLen;
    }
};

void test(const string& label, string s, int expected) {
    cout << "Testing: " << label << " (\"" << s << "\")" << endl;
    Solution sol;
    int result = sol.lengthOfLongestSubstringTwoDistinct(s);
    if (result == expected) {
        cout << "  [PASS] Length: " << result << endl;
    } else {
        cout << "  [FAIL] Result: " << result << " (Expected: " << expected << ")" << endl;
    }
}

int main() {
    test("Example 1", "eceba", 3);
    test("Example 2", "ccaabbb", 5);
    return 0;
}
