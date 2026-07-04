#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

/*
  LeetCode 767: Reorganize String

  Problem Description:
  Given a string `s`, rearrange the characters of `s` so that any 
  two adjacent characters are not the same. If not possible, 
  return an empty string.

  Algorithm: Greedy with Max-Heap
  1. Count frequencies of each character.
  2. If any character frequency > `(n + 1) / 2`, it's impossible.
  3. Use a Max-Heap to store `(frequency, character)` pairs.
  4. Build the result string by picking the two most frequent 
     characters at a time:
     - Pop the top character `c1`.
     - Append it to result.
     - If the heap is not empty:
       - Pop the next top character `c2`.
       - Append it to result.
       - Decrement counts of `c1` and `c2`.
       - Re-insert into heap if counts > 0.
     - If heap is empty and `c1` still has count > 0:
       - This should not happen if the `(n+1)/2` check passed.
  5. Alternatively, process one character at a time but keep track 
     of the "previous" character and its remaining count, re-inserting 
     it after the next character is picked.

  Complexity Analysis:
  - Time Complexity: O(N log A) where A is alphabet size (26).
    Reason: We iterate through the string, and each heap operation 
    takes O(log 26).
  - Space Complexity: O(A).
*/

class Solution {
public:
    string reorganizeString(string s) {
        int n = s.length();
        unordered_map<char, int> freq;
        for (char c : s) freq[c]++;

        priority_queue<pair<int, char>> pq;
        for (auto const& [ch, count] : freq) {
            if (count > (n + 1) / 2) return "";
            pq.push({count, ch});
        }

        string result = "";
        while (pq.size() >= 2) {
            auto [f1, c1] = pq.top(); pq.pop();
            auto [f2, c2] = pq.top(); pq.pop();

            result += c1;
            result += c2;

            if (--f1 > 0) pq.push({f1, c1});
            if (--f2 > 0) pq.push({f2, c2});
        }

        if (!pq.empty()) {
            result += pq.top().second;
        }

        return result;
    }
};

void test(string s) {
    Solution sol;
    string result = sol.reorganizeString(s);
    cout << "Input: \"" << s << "\" -> Output: \"" << (result.empty() ? "(empty)" : result) << "\"" << endl;
}

int main() {
    test("aab");
    test("aaab");
    test("vvvlo");
    test("bfrbs");
    return 0;
}
