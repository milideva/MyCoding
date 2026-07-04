#include <iostream>
#include <vector>

using namespace std;

/*
  LeetCode 238: Product of Array Except Self

  Problem Description:
  Given an integer array `nums`, return an array `answer` such that 
  `answer[i]` is equal to the product of all the elements of `nums` 
  except `nums[i]`.

  You must write an algorithm that runs in O(N) time and without 
  using the division operation.

  Algorithm: Prefix and Suffix Products (Space Optimized)
  1. Initialize the result array `ans` with 1s.
  2. Perform a forward pass:
     - Each `ans[i]` stores the product of all elements to its left.
     - `ans[i] = ans[i-1] * nums[i-1]`.
  3. Perform a backward pass:
     - Maintain a `rightProduct` variable (initially 1).
     - Multiply `ans[i]` with `rightProduct`.
     - Update `rightProduct *= nums[i]`.
  4. The result array now contains the product of prefix and suffix 
     for each element.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Two passes through the array.
  - Space Complexity: O(1) auxiliary space.
    Reason: Ignoring the result array, we only use a single variable 
    for the backward pass.

  Brute Force comparison:
  - For each element, iterate through the rest of the array to 
    calculate the product.
  - Time: O(N^2).
  - The division approach would be O(N) but is forbidden (and fails 
    on zero).
*/

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 1);

        // Forward pass: prefix products
        for (int i = 1; i < n; ++i) {
            ans[i] = ans[i - 1] * nums[i - 1];
        }

        // Backward pass: multiply with suffix products
        int rightProduct = 1;
        for (int i = n - 1; i >= 0; --i) {
            ans[i] *= rightProduct;
            rightProduct *= nums[i];
        }

        return ans;
    }
};

void test(const string& label, vector<int> nums, vector<int> expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    vector<int> result = sol.productExceptSelf(nums);
    bool pass = (result == expected);
    cout << "  [" << (pass ? "PASS" : "FAIL") << "] Result: ";
    for (int x : result) cout << x << " ";
    cout << endl;
}

int main() {
    test("Example 1", {1, 2, 3, 4}, {24, 12, 8, 6});
    test("Example 2", {-1, 1, 0, -3, 3}, {0, 0, 9, 0, 0});
    test("All ones", {1, 1, 1}, {1, 1, 1});
    return 0;
}
