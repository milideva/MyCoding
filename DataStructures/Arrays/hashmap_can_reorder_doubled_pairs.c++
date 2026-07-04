#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

/*
  LeetCode 954: Array of Doubled Pairs

  Problem Description:
  Given an integer array of even length `arr`, return true if it is 
  possible to reorder `arr` such that `arr[2 * i + 1] = 2 * arr[2 * i]` 
  for every `0 <= i < len(arr) / 2`.

  Example 1:
  Input: arr = [3,1,3,6]
  Output: false

  Example 2:
  Input: arr = [4,-2,2,-4]
  Output: true

  Algorithm: Frequency Map + Sorted Traversal
  1. Use a `std::map<int, int>` to store frequencies (sorted by key).
  2. For negative numbers: We must process them from largest to 
     smallest (e.g., -2 then -4) or use absolute values.
  3. Standardize: Iterate through keys sorted by their absolute values.
  4. For each key `x`:
     - If `freq[x] > 0`:
       - We need `freq[x]` occurrences of `2*x`.
       - If `freq[2*x] < freq[x]`, return false.
       - Decrement `freq[2*x]` by `freq[x]`.
  5. Return true if all pairs matched.

  Complexity Analysis:
  - Time Complexity: O(N log N)
    Reason: Sorting unique elements takes O(N log N).
  - Space Complexity: O(N)
    Reason: To store the frequency map.

  Brute Force comparison:
  - Try all permutations: O(N!).
  - Greedy with sorted frequency map is optimal.
*/

class Solution {
public:
    bool canReorderDoubled(vector<int>& arr) {
        map<int, int> freq;
        for (int x : arr) freq[x]++;

        vector<int> keys;
        for (auto const& [x, count] : freq) keys.push_back(x);

        // Sort keys by absolute value
        sort(keys.begin(), keys.end(), [](int a, int b) {
            return abs(a) < abs(b);
        });

        for (int x : keys) {
            if (freq[x] == 0) continue;
            
            int count = freq[x];
            int target = 2 * x;
            
            if (freq[target] < count) return false;
            freq[target] -= count;
            freq[x] = 0;
        }
        return true;
    }
};

void test(const string& label, vector<int> arr, bool expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    bool result = sol.canReorderDoubled(arr);
    cout << "  [" << (result == expected ? "PASS" : "FAIL") << "] Result: " << boolalpha << result << endl;
}

int main() {
    test("Example 1", {3, 1, 3, 6}, false);
    test("Example 2", {2, 1, 2, 6}, false);
    test("Example 3", {4, -2, 2, -4}, true);
    test("With Zeros", {0, 0}, true);
    test("Negatives", {-5, -2}, false);
    return 0;
}
