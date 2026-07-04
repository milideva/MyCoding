#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
  LeetCode 93: Restore IP Addresses

  Problem Description:
  A valid IP address consists of exactly four integers separated by 
  single dots. Each integer is between 0 and 255 (inclusive) and 
  cannot have leading zeros.
  Given a string `s` containing only digits, return all possible 
  valid IP addresses that can be formed by inserting dots.

  Example 1:
  Input: s = "25525511135"
  Output: ["255.255.11.135","255.255.111.35"]

  Algorithm: Backtracking (DFS)
  1. Recursive function `dfs(start_index, current_path)`.
  2. Base Case: If `current_path` has 4 segments and we used all 
     characters in `s`, add the joined path to result.
  3. Recursive Step:
     - Try taking 1, 2, or 3 digits starting from `start_index`.
     - Constraints:
       - Segment must not exceed `s.length()`.
       - Segment must not have leading zero (unless it's just "0").
       - Segment value must be <= 255.
     - Add segment, recurse, then backtrack.

  Complexity Analysis:
  - Time Complexity: O(3^4)
    Reason: We have at most 4 segments, each with 3 choices of length. 
    The search space is small and constant relative to input size 
    (input length is at most 12).
  - Space Complexity: O(1) beyond result storage, as recursion depth is 4.
*/

class Solution {
    void dfs(const string& s, int start, vector<string>& path, vector<string>& ans) {
        if (path.size() == 4) {
            if (start == s.length()) {
                ans.push_back(path[0] + "." + path[1] + "." + path[2] + "." + path[3]);
            }
            return;
        }

        for (int len = 1; len <= 3; ++len) {
            if (start + len > s.length()) break;
            
            string part = s.substr(start, len);
            
            // Check for leading zero
            if (len > 1 && part[0] == '0') break;
            
            // Check for value range
            if (len == 3 && stoi(part) > 255) break;

            path.push_back(part);
            dfs(s, start + len, path, ans);
            path.pop_back(); // Backtrack
        }
    }

public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        vector<string> path;
        if (s.length() < 4 || s.length() > 12) return result;
        dfs(s, 0, path, result);
        return result;
    }
};

void test(string s) {
    cout << "Testing: \"" << s << "\"" << endl;
    Solution sol;
    vector<string> result = sol.restoreIpAddresses(s);
    cout << "  Result: [ ";
    for (const string& ip : result) cout << "\"" << ip << "\" ";
    cout << "]" << endl;
}

int main() {
    test("25525511135");
    test("0000");
    test("101023");
    return 0;
}
