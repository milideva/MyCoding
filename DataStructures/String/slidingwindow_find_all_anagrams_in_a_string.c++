#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 438: Find All Anagrams in a String

  Problem Description:
  Given two strings `s` and `p`, return an array of all the start 
  indices of `p`'s anagrams in `s`. You may return the answer in any 
  order.

  Example 1:
  Input: s = "cbaebabacd", p = "abc"
  Output: [0, 6]

  Algorithm: Sliding Window with Frequency Arrays
  1. Use two frequency arrays of size 26 for `s` and `p`.
  2. Populate the frequency array for `p`.
  3. Initially, populate the frequency array for the first `p.length()` 
     characters of `s`.
  4. If the two arrays are equal, the first window is an anagram (index 0).
  5. Slide the window one character at a time:
     - Add the new character to the window frequency array.
     - Remove the leftmost character from the window frequency array.
     - Compare frequency arrays. If equal, add start index to result.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We slide the window across `s` once. Each comparison of 
    frequency arrays takes O(26) = O(1).
  - Space Complexity: O(1) beyond result storage, as frequency arrays 
    are fixed size.
*/

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int sl = s.length(), pl = p.length();
        if (sl < pl) return {};

        vector<int> pFreq(26, 0);
        vector<int> sFreq(26, 0);
        vector<int> result;

        for (int i = 0; i < pl; i++) {
            pFreq[p[i] - 'a']++;
            sFreq[s[i] - 'a']++;
        }

        if (sFreq == pFreq) result.push_back(0);

        for (int i = pl; i < sl; i++) {
            sFreq[s[i] - 'a']++;
            sFreq[s[i - pl] - 'a']--;
            if (sFreq == pFreq) {
                result.push_back(i - pl + 1);
            }
        }

        return result;
    }
};

void test(string s, string p) {
    cout << "Testing: s=\"" << s << "\", p=\"" << p << "\"" << endl;
    Solution sol;
    vector<int> result = sol.findAnagrams(s, p);
    cout << "  Result: [ ";
    for (int i : result) cout << i << " ";
    cout << "]" << endl;
}

int main() {
    test("cbaebabacd", "abc");
    test("abab", "ab");
    return 0;
}
