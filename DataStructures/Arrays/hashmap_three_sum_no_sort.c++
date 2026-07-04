#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

/*
  Problem: 4-Sum Variation (x + y + z = w)

  Problem Description:
  Given an array `a`, find all unique sets of four elements `{x, y, z, w}` 
  such that `x + y + z = w`, where `x, y, z, w` are elements at 
  distinct indices `i, j, k, n` and `i < j < k < n`.
  Sorting the original array is NOT allowed for the index constraints.

  Algorithm: Hash Map / Two-Sum Optimization
  1. This problem can be rewritten as `x + y = w - z`.
  2. Use a hash map to store all possible sums of pairs `(x, y)` 
     encountered so far.
  3. Iterate through all pairs `(z, w)` where `index(z) < index(w)`:
     - Check if `w - z` exists in our hash map of previous pair sums.
     - If found, we have a valid quadruplet.
  4. To ensure `i < j < k < n`:
     - As we iterate with `k` from `0` to `n-1`:
       - First, check all pairs `(x, k)` where `index(x) < k` against 
         the current `w - z` targets.
       - Then, add all pairs `(x, k)` into the hash map to be used 
         for future `z, w` pairs.

  Complexity Analysis:
  - Time Complexity: O(N^2)
    Reason: We iterate through all pairs of elements.
  - Space Complexity: O(N^2)
    Reason: To store up to N^2 pair sums in the hash map.

  Brute Force comparison:
  - Check all combinations of four indices: O(N^4).
  - The hash map approach reduces it to quadratic time.
*/

class Solution {
public:
    vector<vector<int>> findQuadruplets(vector<int>& v) {
        int n = v.size();
        vector<vector<int>> result;
        // Map sum -> list of pairs (indices) that produce this sum
        unordered_map<int, vector<pair<int, int>>> pairSums;

        for (int j = 0; j < n; ++j) {
            // 1. Check for x + y + z = w  =>  x + y = w - z
            // Here j acts as 'k' (index of z) or 'n' (index of w)
            for (int i = 0; i < j; ++i) {
                // If we treat v[i] as z and v[j] as w
                int target = v[j] - v[i];
                if (pairSums.count(target)) {
                    for (auto const& p : pairSums[target]) {
                        // Ensure indices i < j < k < n
                        // p.first < p.second < i < j
                        if (p.second < i) {
                            result.push_back({v[p.first], v[p.second], v[i], v[j]});
                        }
                    }
                }
            }
            // 2. Add pairs (i, j) to map for future targets
            for (int i = 0; i < j; ++i) {
                pairSums[v[i] + v[j]].push_back({i, j});
            }
        }
        return result;
    }
};

void test(const string& label, vector<int> nums) {
    cout << "Testing: " << label << endl;
    Solution sol;
    vector<vector<int>> result = sol.findQuadruplets(nums);
    cout << "  Found " << result.size() << " quadruplets." << endl;
    for (const auto& q : result) {
        cout << "    [" << q[0] << "+" << q[1] << "+" << q[2] << " = " << q[3] << "]" << endl;
    }
}

int main() {
    vector<int> test_array = {1, 2, 3, 6, 5, 11}; 
    // Quadruplets: 1+2+3=6, 1+2+3=6 (no, distinct indices), 
    // 1+2+3=6 is one. 1+5+?
    // 1+2+3=6 (indices 0,1,2,3)
    // 1+5+? 1+2+3=6, 2+3+6=11 (indices 1,2,3,5)
    test("Simple case", test_array);
    return 0;
}
