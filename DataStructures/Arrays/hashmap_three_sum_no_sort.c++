/**
 * @file hashmap_three_sum_no_sort.c++
 * @brief 3Sum (Three Sum) implementation in O(N^2) time WITHOUT sorting the original array.
 *
 * This file demonstrates how to solve the classic 3Sum problem (LeetCode 15)
 * when sorting the input array is strictly prohibited or when the input array 
 * is read-only and must not be mutated.
 *
 * ============================================================================
 * Key Concept: Hash Map / Hash Set Optimization
 * ============================================================================
 * - Instead of Sorting + Two Pointers (which mutates the original array and 
 *   requires O(N log N) sorting), we can use a hash-based approach.
 * - For each unique first element `nums[i]`, we solve a Two-Sum problem for the 
 *   remaining elements `nums[j]` (where `j > i`) to find pairs that sum to `-nums[i]`.
 * - We use a hash set `seen` to record visited elements in the inner loop, 
 *   and a set/hash table to deduplicate found triplets.
 *
 * ============================================================================
 * Complexity Analysis:
 * ============================================================================
 * Time Complexity:
 *   - Worst-Case: O(N^2)
 *     Outer loop runs N times. Inner loop runs up to N times, performing O(1) 
 *     average-time hash set lookups and insertions.
 *   - Average-Case: O(N^2)
 *   - Best-Case: O(N) (if array has fewer than 3 elements)
 *
 * Space Complexity:
 *   - Worst-Case: O(N)
 *     Auxiliary space used by the `dups` hash set, `seen` hash set, and the 
 *     `unique_triplets` set to store the deduplicated output.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * @brief Finds all unique triplets in the array that sum to 0 without sorting the input array.
     * 
     * Time Complexity:  O(N^2)
     * Space Complexity: O(N)
     */
    vector<vector<int>> threeSumNoSort(vector<int>& nums) {
        int n = nums.size();
        set<vector<int>> unique_triplets; // Use set to easily deduplicate found triplets
        unordered_set<int> dups;          // To skip duplicate first elements in the outer loop

        for (int i = 0; i < n; ++i) {
            // Only process nums[i] if we haven't used it as the first element of a triplet
            if (dups.insert(nums[i]).second) {
                unordered_set<int> seen;
                for (int j = i + 1; j < n; ++j) {
                    int needed = -nums[i] - nums[j];
                    if (seen.find(needed) != seen.end()) {
                        // Create and sort just the 3-element triplet to ensure consistent ordering
                        vector<int> triplet = {nums[i], nums[j], needed};
                        sort(triplet.begin(), triplet.end()); // Sorting 3 elements is O(1)
                        unique_triplets.insert(triplet);
                    }
                    seen.insert(nums[j]);
                }
            }
        }
        return vector<vector<int>>(unique_triplets.begin(), unique_triplets.end());
    }
};

void test(const string& label, vector<int> nums) {
    cout << "Testing: " << label << endl;
    cout << "  Original Array (Unsorted): [ ";
    for (int x : nums) cout << x << " ";
    cout << "]" << endl;

    Solution sol;
    vector<vector<int>> result = sol.threeSumNoSort(nums);

    cout << "  Unique Triplets: [ ";
    for (const auto& triplet : result) {
        cout << "[" << triplet[0] << "," << triplet[1] << "," << triplet[2] << "] ";
    }
    cout << "]" << endl;

    // Verify that the original array was NOT sorted or mutated
    cout << "  Array After Function (Verify Unsorted): [ ";
    for (int x : nums) cout << x << " ";
    cout << "]" << endl << endl;
}

int main() {
    cout << "=== 3Sum WITHOUT Sorting the Original Array ===" << endl << endl;

    test("Example 1 (Mixed)", {-1, 0, 1, 2, -1, -4});
    test("All Zeros", {0, 0, 0, 0});
    test("No Solution", {1, 2, 3, 4});
    test("Large Sparse Values", {10, -5, -5, 0, 5, -10});

    return 0;
}
