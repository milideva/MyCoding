#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 242: Valid Anagram

  Problem Description:
  Given two strings `s` and `t`, return true if `t` is an anagram 
  of `s`, and false otherwise.

  Algorithm 1: Frequency Array
  1. If lengths differ, return false.
  2. Use a frequency array of size 26 for lowercase English letters.
  3. Increment counts for each character in `s`.
  4. Decrement counts for each character in `t`.
  5. If all counts in the array are zero, return true.

  Algorithm 2: Sorting
  1. Sort both strings.
  2. If `sorted_s == sorted_t`, return true.

  Complexity Analysis (Algorithm 1):
  - Time Complexity: O(N)
    Reason: We traverse each string once.
  - Space Complexity: O(1)
    Reason: The frequency array size is constant (26).

  Complexity Analysis (Algorithm 2):
  - Time Complexity: O(N log N)
    Reason: Due to sorting.
  - Space Complexity: O(1) or O(N) depending on sort implementation.
*/

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
        
        int count[26] = {0};
        for (int i = 0; i < s.length(); i++) {
            count[s[i] - 'a']++;
            count[t[i] - 'a']--;
        }
        
        for (int i = 0; i < 26; i++) {
            if (count[i] != 0) return false;
        }
        return true;
    }
};

void test(string s, string t, bool expected) {
    cout << "Testing: s=\"" << s << "\", t=\"" << t << "\"" << endl;
    Solution sol;
    bool result = sol.isAnagram(s, t);
    cout << "  [" << (result == expected ? "PASS" : "FAIL") << "] Result: " << boolalpha << result << endl;
}

int main() {
    test("anagram", "nagaram", true);
    test("rat", "car", false);
    test("listen", "silent", true);
    return 0;
}
