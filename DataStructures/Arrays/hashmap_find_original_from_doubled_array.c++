#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

/*
  LeetCode 2007: Find Original Array From Doubled Array

  Problem Description:
  An integer array `original` is transformed into a doubled array 
  `changed` by appending twice the value of every element in `original`, 
  and then randomly shuffling the resulting array.
  Given an array `changed`, return `original` if `changed` is a 
  doubled array. If not, return an empty array.

  Example 1:
  Input: changed = [1,3,4,2,6,8]
  Output: [1,3,4]

  Algorithm: Frequency Map + Sorted Traversal
  1. If the length is odd, it cannot be a doubled array; return {}.
  2. Count frequencies of all numbers in a `map` (which keeps keys 
     sorted).
  3. Iterate through the sorted keys in the map.
  4. For each key `x`:
     - If `freq[x] > 0`:
       - We need at least `freq[x]` occurrences of `2*x`.
       - If `2*x` is not in the map or `freq[2*x] < freq[x]`, return {}.
       - Special case: If `x == 0`, `freq[0]` must be even.
       - Add `x` to the result `freq[x]` times.
       - Decrement `freq[2*x]` by `freq[x]`.
  5. If we successfully process all numbers, return the result.

  Complexity Analysis:
  - Time Complexity: O(N log N)
    Reason: Sorting (or map insertion) takes O(N log N).
  - Space Complexity: O(N)
    Reason: To store frequencies in the map.

  Brute Force comparison:
  - For each element, search for its double and remove both.
  - Time: O(N^2).
  - The map-based approach is significantly faster.
*/

class Solution {
public:
    vector<int> findOriginalArray(vector<int>& changed) {
        int n = changed.size();
        if (n % 2 != 0) return {};

        map<int, int> freq;
        for (int x : changed) freq[x]++;

        vector<int> result;
        for (auto const& [x, count] : freq) {
            if (freq[x] == 0) continue;

            if (x == 0) {
                if (count % 2 != 0) return {};
                for (int i = 0; i < count / 2; ++i) result.push_back(0);
                freq[0] = 0;
            } else {
                int target = 2 * x;
                if (freq[target] < count) return {};
                for (int i = 0; i < count; ++i) result.push_back(x);
                freq[target] -= count;
            }
        }
        return result;
    }
};

void test(const string& label, vector<int> changed) {
    cout << "Testing: " << label << endl;
    Solution sol;
    vector<int> result = sol.findOriginalArray(changed);
    if (!result.empty() || changed.empty()) {
        cout << "  Result: [ ";
        for (int x : result) cout << x << " ";
        cout << "]" << endl;
    } else {
        cout << "  Result: [] (Not a doubled array)" << endl;
    }
}

int main() {
    test("Example 1", {1, 3, 4, 2, 6, 8});
    test("Example 2", {6, 3, 0, 1});
    test("With Zeros", {0, 0, 0, 0});
    test("Single Element", {1});
    return 0;
}
