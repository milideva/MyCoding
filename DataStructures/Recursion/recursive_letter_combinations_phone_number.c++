#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
  LeetCode 17: Letter Combinations of a Phone Number (Recursive)

  Problem Description:
  Given a string containing digits from 2-9 inclusive, return all 
  possible letter combinations.

  Algorithm: Divide and Conquer / Pure Recursion
  1. Base Cases:
     - If the input is empty, return an empty list.
     - If the input has only one digit, return its letters.
  2. Recursive Step:
     - Solve for the substring starting from the next character.
     - Combine each letter of the first digit with each combination 
       returned by the recursive call.
  3. This differs from backtracking as it explicitly builds the 
     entire result set from subproblems rather than modifying a 
     shared state.

  Complexity Analysis:
  - Time Complexity: O(3^N * 4^M)
    Reason: Total number of combinations.
  - Space Complexity: O(3^N * 4^M) for storing all results.
*/

class Solution {
    vector<string> mapping = {
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };

public:
    vector<string> combinations(string digits) {
        if (digits.empty()) return {};
        
        string first_letters = mapping[digits[0] - '0'];
        if (digits.length() == 1) {
            vector<string> res;
            for (char c : first_letters) res.push_back(string(1, c));
            return res;
        }

        vector<string> sub_combinations = combinations(digits.substr(1));
        vector<string> result;

        for (char c : first_letters) {
            for (const string& s : sub_combinations) {
                result.push_back(c + s);
            }
        }
        return result;
    }
};

void test(string digits) {
    cout << "Testing: \"" << digits << "\"" << endl;
    Solution sol;
    vector<string> result = sol.combinations(digits);
    cout << "  Result: [ ";
    for (const string& s : result) cout << "\"" << s << "\" ";
    cout << "]" << endl;
}

int main() {
    test("23");
    test("2");
    return 0;
}
