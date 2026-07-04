#include <stack>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 394: Decode String

  Problem Description:
  Given an encoded string, return its decoded string.
  The encoding rule is: `k[encoded_string]`, where the `encoded_string` 
  inside the square brackets is being repeated exactly `k` times.

  Example 1:
  Input: s = "3[a]2[bc]"
  Output: "aaabcbc"

  Algorithm: Two Stacks
  1. Use two stacks: `countStack` for numbers and `stringStack` for 
     partial strings.
  2. Maintain a `currentString` and a `currentK`.
  3. Iterate through the string:
     - If digit: Update `currentK`.
     - If '[': Push `currentString` and `currentK` onto their 
       respective stacks. Reset `currentString` and `currentK`.
     - If ']': 
       - Pop `k` from `countStack`.
       - Pop `prevString` from `stringStack`.
       - Update `currentString = prevString + (repeat currentString k times)`.
     - If char: Append to `currentString`.
  4. Return `currentString`.

  Complexity Analysis:
  - Time Complexity: O(MaxK * N)
    Reason: We iterate through the string once, but string 
    concatenation can be expensive depending on K.
  - Space Complexity: O(N) for the stacks and result string.
*/

class Solution {
public:
    string decodeString(string s) {
        stack<int> countStack;
        stack<string> stringStack;
        string currentString = "";
        int k = 0;

        for (char c : s) {
            if (isdigit(c)) {
                k = k * 10 + (c - '0');
            } else if (c == '[') {
                countStack.push(k);
                stringStack.push(currentString);
                currentString = "";
                k = 0;
            } else if (c == ']') {
                string prevString = stringStack.top(); stringStack.pop();
                int repeatTimes = countStack.top(); countStack.pop();
                string repeated = "";
                for (int i = 0; i < repeatTimes; i++) repeated += currentString;
                currentString = prevString + repeated;
            } else {
                currentString += c;
            }
        }
        return currentString;
    }
};

void test(string s, string expected) {
    cout << "Testing: \"" << s << "\"" << endl;
    Solution sol;
    string result = sol.decodeString(s);
    if (result == expected) {
        cout << "  [PASS] Result: \"" << result << "\"" << endl;
    } else {
        cout << "  [FAIL] Result: \"" << result << "\" (Expected: \"" << expected << "\")" << endl;
    }
}

int main() {
    test("3[a]2[bc]", "aaabcbc");
    test("3[a2[c]]", "accaccacc");
    test("2[abc]3[cd]ef", "abcabccdcdcdef");
    return 0;
}
