#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

/*
  LeetCode 340: Longest Substring with At Most K Distinct Characters

  Problem Description:
  Given a string `s` and an integer `k`, return the length of the 
  longest substring that contains at most `k` distinct characters.

  Algorithm: Sliding Window
  1. Use two pointers `l` and `r` to define a window.
  2. Maintain a frequency map of characters in the current window.
  3. Iterate with `r` from 0 to n-1:
     - Add `s[r]` to the frequency map.
     - While the map size > `k`:
       - Decrement frequency of `s[l]`.
       - If frequency becomes 0, remove `s[l]` from the map.
       - Increment `l`.
     - Update `maxLen = max(maxLen, r - l + 1)`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Each character is visited at most twice.
  - Space Complexity: O(K)
    Reason: The hash map stores at most K+1 characters.
*/

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if (k == 0) return 0;
        unordered_map<char, int> freq;
        int l = 0, maxLen = 0;

        for (int r = 0; r < s.length(); ++r) {
            freq[s[r]]++;
            while (freq.size() > k) {
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

void test(const string& label, string s, int k, int expected) {
    cout << "Testing: " << label << " (k=" << k << ")" << endl;
    Solution sol;
    int result = sol.lengthOfLongestSubstringKDistinct(s, k);
    if (result == expected) {
        cout << "  [PASS] Length: " << result << endl;
    } else {
        cout << "  [FAIL] Result: " << result << " (Expected: " << expected << ")" << endl;
    }
}

int main() {
    test("Example 1", "eceba", 2, 3);
    test("Example 2", "aa", 1, 2);
    test("K larger than length", "abc", 10, 3);
    return 0;
}
