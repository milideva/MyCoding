#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
  LeetCode 17: Letter Combinations of a Phone Number

  Problem Description:
  Given a string containing digits from 2-9 inclusive, return all 
  possible letter combinations that the number could represent.

  Mapping: 2:"abc", 3:"def", 4:"ghi", 5:"jkl", 6:"mno", 7:"pqrs", 
           8:"tuv", 9:"wxyz".

  Algorithm: Backtracking (DFS)
  1. Define a mapping from digits to strings.
  2. Use a recursive function `backtrack(index, current_string)`.
  3. Base Case: If `index == digits.size()`, add `current_string` 
     to result.
  4. Recursive Step:
     - Get the letters corresponding to `digits[index]`.
     - For each letter:
       - Append to `current_string`.
       - Recurse to `index + 1`.
       - Backtrack: Remove the letter.

  Complexity Analysis:
  - Time Complexity: O(3^N * 4^M)
    Reason: N is the number of digits mapping to 3 letters, M is 
    the number of digits mapping to 4 letters. Total combinations.
  - Space Complexity: O(N + M) for the recursion stack.
*/

class Solution {
    vector<string> mapping = {
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };

    void backtrack(string digits, int index, string& curr, vector<string>& result) {
        if (index == digits.size()) {
            result.push_back(curr);
            return;
        }

        string letters = mapping[digits[index] - '0'];
        for (char c : letters) {
            curr.push_back(c);
            backtrack(digits, index + 1, curr, result);
            curr.pop_back(); // Backtrack
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        vector<string> result;
        string curr = "";
        backtrack(digits, 0, curr, result);
        return result;
    }
};

void test(string digits) {
    cout << "Testing: \"" << digits << "\"" << endl;
    Solution sol;
    vector<string> result = sol.letterCombinations(digits);
    cout << "  Result: [ ";
    for (const string& s : result) cout << "\"" << s << "\" ";
    cout << "]" << endl;
}

int main() {
    test("23");
    test("");
    test("2");
    return 0;
}
