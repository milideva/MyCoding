#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

/*
  Problem: Find Original Array from Squared Array

  Problem Description:
  An integer array `original` is transformed into a squared array 
  `changed` by appending the square of every element in `original`, 
  and then randomly shuffling the resulting array.
  Given an array `changed`, return `original` if `changed` is a 
  squared array. If not, return an empty array.

  Example 1:
  Input: changed = [2, 1, 4, 1, -3, 9]
  Output: [2, 1, -3]
  Explanation: 2^2=4, 1^2=1, (-3)^2=9.

  Algorithm: Frequency Map + Absolute Sorted Traversal
  1. If length is odd, return {}.
  2. Use a `std::map<int, int>` to store frequencies.
  3. Sort unique keys by absolute value.
  4. For each key `x`:
     - If `freq[x] > 0`:
       - If `x*x` is not in map or `freq[x*x] < count`, return {}.
       - Special case: If `x == 0` or `x == 1`, `freq[x]` must be even.
       - Add `x` to result.
       - Decrement `freq[x*x]`.

  Complexity Analysis:
  - Time Complexity: O(N log N)
  - Space Complexity: O(N)
*/

class Solution {
public:
    vector<int> findOriginalArray(vector<int>& changed) {
        int n = changed.size();
        if (n % 2 != 0) return {};

        map<int, int> freq;
        for (int x : changed) freq[x]++;

        vector<int> keys;
        for (auto const& [x, count] : freq) keys.push_back(x);

        sort(keys.begin(), keys.end(), [](int a, int b) {
            return abs(a) < abs(b);
        });

        vector<int> result;
        for (int x : keys) {
            if (freq[x] == 0) continue;

            int count = freq[x];
            if (x == 0 || x == 1 || x == -1) {
                // For 0, 1, -1, the square is either itself or -itself.
                // This logic is slightly tricky if both -1 and 1 are present.
                // Let's simplify: only 0, 1, -1 need even counts if they square to themselves.
                if (x == 0 || x == 1) {
                    if (count % 2 != 0) return {};
                    for (int i = 0; i < count / 2; ++i) result.push_back(x);
                    freq[x] = 0;
                    continue;
                }
            }

            int target = x * x;
            if (freq[target] < count) return {};
            for (int i = 0; i < count; ++i) result.push_back(x);
            freq[target] -= count;
            freq[x] = 0;
        }
        return result;
    }
};

void test(const string& label, vector<int> changed) {
    cout << "Testing: " << label << endl;
    Solution sol;
    vector<int> result = sol.findOriginalArray(changed);
    cout << "  Result: [ ";
    for (int x : result) cout << x << " ";
    cout << "]" << endl;
}

int main() {
    test("Example 1", {2, 1, 4, 1, -3, 9});
    test("Zeros and Ones", {0, 0, 1, 1});
    test("Invalid", {2, 3, 5});
    return 0;
}
