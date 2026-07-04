#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
  LeetCode 266: Palindrome Permutation

  Problem Description:
  Given a string, determine if a permutation of the string could 
  form a palindrome.

  Example 1: "code" -> False
  Example 2: "aab" -> True ("aba")
  Example 3: "carerac" -> True ("racecar")

  Algorithm: Odd Frequency Count
  1. For a string to be a palindrome, at most one character can 
     have an odd frequency.
  2. Use a frequency array (or bitset) to track counts of each character.
  3. Count how many characters have odd frequencies.
  4. If `oddCount <= 1`, return true.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Single pass through the string.
  - Space Complexity: O(1)
    Reason: Frequency array size is constant (e.g., 128 for ASCII).
*/

class Solution {
public:
    bool canPermutePalindrome(string s) {
        int count[128] = {0};
        int oddCount = 0;
        
        for (char c : s) {
            count[(int)c]++;
            if (count[(int)c] % 2 != 0) {
                oddCount++;
            } else {
                oddCount--;
            }
        }
        return oddCount <= 1;
    }
};

void test(string s, bool expected) {
    cout << "Testing: \"" << s << "\"" << endl;
    Solution sol;
    bool result = sol.canPermutePalindrome(s);
    cout << "  [" << (result == expected ? "PASS" : "FAIL") << "] Result: " << boolalpha << result << endl;
}

int main() {
    test("code", false);
    test("aab", true);
    test("carerac", true);
    test("Aa", false); // Case sensitive by default
    return 0;
}
