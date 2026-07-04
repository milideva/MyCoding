#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
  LeetCode 179: Largest Number

  Problem Description:
  Given a list of non-negative integers `nums`, arrange them such 
  that they form the largest number and return it.
  Since the result may be very large, you need to return a string 
  instead of an integer.

  Example 1:
  Input: nums = [10, 2]
  Output: "210"

  Example 2:
  Input: nums = [3, 30, 34, 5, 9]
  Output: "9534330"

  Algorithm: Custom Sorting
  1. Convert all integers to strings.
  2. Define a custom comparator for two strings `A` and `B`:
     - If `A + B > B + A`, then `A` should come before `B`.
     - Otherwise, `B` should come before `A`.
  3. Sort the strings using this comparator.
  4. Concatenate the sorted strings.
  5. Handle edge case: If the largest number is "0" (e.g., input is 
     `[0, 0]`), return "0".

  Complexity Analysis:
  - Time Complexity: O(N log N * K)
    Reason: Sorting takes O(N log N) comparisons. Each comparison 
    involves string concatenation and comparison of length K, 
    where K is the average number of digits.
  - Space Complexity: O(N * K)
    Reason: To store the string representations of the numbers.

  Brute Force comparison:
  - Generate all possible permutations of the numbers and find the max.
  - Time Complexity: O(N!).
  - The custom sorting approach is much more efficient.
*/

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> strs;
        for (int x : nums) {
            strs.push_back(to_string(x));
        }

        sort(strs.begin(), strs.end(), [](const string& a, const string& b) {
            return a + b > b + a;
        });

        if (strs[0] == "0") return "0";

        string result = "";
        for (const string& s : strs) {
            result += s;
        }
        return result;
    }
};

void test(const string& label, vector<int> nums, string expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    string result = sol.largestNumber(nums);
    if (result == expected) {
        cout << "  [PASS] Result: " << result << endl;
    } else {
        cout << "  [FAIL] Result: " << result << " (Expected: " << expected << ")" << endl;
    }
}

int main() {
    test("Example 1", {10, 2}, "210");
    test("Example 2", {3, 30, 34, 5, 9}, "9534330");
    test("All Zeros", {0, 0}, "0");
    test("Single Number", {5}, "5");
    return 0;
}
