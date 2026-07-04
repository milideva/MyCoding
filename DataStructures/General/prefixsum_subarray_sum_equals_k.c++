/**
 * Problem: Subarray Sum Equals K
 * Given an array of integers and an integer k, find the total number of 
 * continuous subarrays whose sum equals to k.
 * 
 * Strategy: Prefix Sum + Hash Map
 * 1. Maintain a running sum (prefix sum).
 * 2. At each element, if (prefixSum - k) has been seen before, it means there is 
 *    a subarray ending here that sums to k.
 * 3. Use a hash map to store the frequency of each prefix sum encountered.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N) for the hash map.
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/**
 * Finds the number of subarrays that sum up to k.
 */
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixSumCounts;
    prefixSumCounts[0] = 1; // Base case: prefix sum of 0 seen once

    int count = 0;
    int currentSum = 0;

    for (int num : nums) {
        currentSum += num;
        if (prefixSumCounts.find(currentSum - k) != prefixSumCounts.end()) {
            count += prefixSumCounts[currentSum - k];
        }
        prefixSumCounts[currentSum]++;
    }

    return count;
}

int main() {
    vector<int> nums1 = {1, 1, 1};
    int k1 = 2;
    cout << "Subarrays of {1, 1, 1} summing to 2: " << subarraySum(nums1, k1) << " (Expected: 2)" << endl;

    vector<int> nums2 = {1, 2, 3};
    int k2 = 3;
    cout << "Subarrays of {1, 2, 3} summing to 3: " << subarraySum(nums2, k2) << " (Expected: 2)" << endl;

    return 0;
}
