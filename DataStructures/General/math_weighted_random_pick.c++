/**
 * Problem: Random Pick with Weight
 * You are given an array of positive integers w where w[i] describes the weight 
 * of the ith index. Implement pickIndex() which randomly returns an integer 
 * in the range [0, w.length - 1] proportional to its weight.
 * 
 * Strategy: Prefix Sums + Binary Search
 * 1. Create a prefix sum array `sums` where `sums[i]` is the total weight from index 0 to i.
 * 2. Generate a random number `r` in the range [1, total_sum].
 * 3. Use binary search (upper_bound) to find the first index `i` such that `sums[i] >= r`.
 * 
 * Time Complexity: 
 * - Constructor: O(N)
 * - pickIndex: O(log N)
 * Space Complexity: O(N) to store prefix sums.
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <ctime>

using namespace std;

class Solution {
    vector<int> prefixSums;
    int totalSum;

public:
    Solution(vector<int>& w) {
        int currentSum = 0;
        for (int weight : w) {
            currentSum += weight;
            prefixSums.push_back(currentSum);
        }
        totalSum = currentSum;
        srand(time(NULL));
    }

    int pickIndex() {
        int target = (rand() % totalSum) + 1;
        // Binary search for the first element >= target
        auto it = lower_bound(prefixSums.begin(), prefixSums.end(), target);
        return distance(prefixSums.begin(), it);
    }
};

int main() {
    vector<int> weights = {1, 3};
    Solution sol(weights);

    int counts[2] = {0};
    int iterations = 10000;

    for (int i = 0; i < iterations; i++) {
        counts[sol.pickIndex()]++;
    }

    printf("Results after %d iterations with weights {1, 3}:\n", iterations);
    printf("Index 0: %d (Expected ~25%%)\n", counts[0]);
    printf("Index 1: %d (Expected ~75%%)\n", counts[1]);

    return 0;
}
