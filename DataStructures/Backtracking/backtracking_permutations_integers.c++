#include <iostream>
#include <vector>
#include <algorithm> // For std::swap

using namespace std;

/*
  LeetCode 46: Permutations

  Problem Description:
  Given an array `nums` of distinct integers, return all the 
  possible permutations. You can return the answer in any order.

  Algorithm: Backtracking (Swap-based)
  1. Use a recursive function `backtrack(index)`.
  2. Base Case: If `index == n`, we have a complete permutation.
     We append a copy of `nums` to our `result` list.
  3. Recursive Step:
     - For each `i` from `index` to `n-1`:
       - Swap `nums[index]` and `nums[i]`.
       - Recurse for `index + 1`.
       - Backtrack: Swap `nums[index]` and `nums[i]` back to 
         restore the original state.

  Complexity Analysis:
  - Time Complexity: O(N * N!)
    Reasoning for the O(N * N!) Bound:
    - It is a common misconception to assume the time complexity is O(N!) just because 
      there are N! permutations.
    - There are exactly N! leaf nodes in our recursion tree (representing all possible permutations).
    - At each leaf node, we perform O(N) work to copy the permutation of size N into our 
      results container (result.push_back(nums)).
    - The work done at the leaf nodes is: Leaf Work = O(N * N!).
    - The total number of nodes in the recursion tree is roughly e * N! ≈ 2.718 * N!. 
      At each internal node, we perform O(1) operations (swapping and looping). 
      The work done during the recursion itself is: Internal Node Work = O(N!).
    - Total Time Complexity = Leaf Work + Internal Node Work = O(N * N!) + O(N!) = O(N * N!).

  - Space Complexity: O(N)
    Reasoning: The recursion tree has a maximum height of N, meaning the recursive call stack 
    requires O(N) auxiliary space.

  Engineering Optimizations:
  1. Pre-allocating Capacity (std::vector::reserve):
     By pre-calculating the factorial of N (which is N!), we can reserve the exact number 
     of slots required in our result container. This completely eliminates expensive 
     dynamic array re-allocations and elements copying during push_back operations.
*/

class Solution {
private:
    int factorial(int n) {
        int f = 1;
        for (int i = 2; i <= n; ++i) f *= i;
        return f;
    }

    void backtrack(vector<int>& nums, int index, vector<vector<int>>& result) {
        int n = nums.size();
        if (index == n) {
            result.push_back(nums); // Store the current permutation (takes O(N) copy work)
            return;
        }

        for (int i = index; i < n; i++) {
            swap(nums[index], nums[i]);         // Choose: Swap elements
            backtrack(nums, index + 1, result);  // Explore
            swap(nums[index], nums[i]);         // Un-choose: Swap back (Backtrack)
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        result.reserve(factorial(nums.size())); // Optimize: reserve N! capacity to avoid re-allocations
        backtrack(nums, 0, result);
        return result;
    }
};

void test(const string& label, vector<int> nums) {
    cout << "Testing " << label << ":" << endl;
    Solution sol;
    vector<vector<int>> result = sol.permute(nums);
    
    for (const auto& perm : result) {
        cout << "  [ ";
        for (int x : perm) {
            cout << x << " ";
        }
        cout << "]" << endl;
    }
    cout << endl;
}

int main() {
    test("Example 1", {1, 2, 3});
    test("Example 2", {0, 1});

    return 0;
}
