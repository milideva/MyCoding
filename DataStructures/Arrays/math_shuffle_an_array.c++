#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

/*
  LeetCode 384: Shuffle an Array

  Problem Description:
  Given an integer array `nums`, design an algorithm to randomly 
  shuffle the array. All permutations of the array should be equally 
  likely.

  Implement the Solution class:
  - `Solution(int[] nums)` Initializes the object with the array `nums`.
  - `int[] reset()` Resets the array to its original configuration.
  - `int[] shuffle()` Returns a random shuffling of the array.

  Algorithm: Fisher-Yates Shuffle
  1. Iterate through the array from left to right (index `i`).
  2. For each `i`, pick a random index `j` in the range `[i, n-1]`.
  3. Swap `nums[i]` and `nums[j]`.
  4. This ensures that every element has an equal probability of 
     occupying any position.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We perform a single pass through the array.
  - Space Complexity: O(N)
    Reason: To store the original configuration for `reset()`.

  Brute Force comparison:
  - Generate all N! permutations and pick one: O(N!). 
  - Fisher-Yates provides the same randomness in linear time.
*/

class Solution {
    vector<int> original;
    vector<int> current;
    mt19937 rng;

public:
    Solution(vector<int>& nums) : original(nums), current(nums), rng(random_device{}()) {}
    
    vector<int> reset() {
        current = original;
        return current;
    }
    
    vector<int> shuffle() {
        int n = current.size();
        for (int i = 0; i < n; ++i) {
            // Pick random index in [i, n-1]
            uniform_int_distribution<int> dist(i, n - 1);
            int j = dist(rng);
            swap(current[i], current[j]);
        }
        return current;
    }
};

void printVec(const vector<int>& vec) {
    cout << "[ ";
    for (int x : vec) cout << x << " ";
    cout << "]" << endl;
}

int main() {
    cout << "Testing: Shuffle an Array" << endl;
    vector<int> nums = {1, 2, 3, 4, 5};
    Solution sol(nums);

    cout << "  Original: "; printVec(nums);
    cout << "  Shuffled 1: "; printVec(sol.shuffle());
    cout << "  Shuffled 2: "; printVec(sol.shuffle());
    cout << "  Reset: "; printVec(sol.reset());

    return 0;
}
