#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 11: Container With Most Water

  Problem Description:
  You are given an integer array `height` of length `n`. There are `n` 
  vertical lines drawn such that the two endpoints of the `i`-th line 
  are `(i, 0)` and `(i, height[i])`.

  Find two lines that together with the x-axis form a container, 
  such that the container contains the most water.

  Return the maximum amount of water a container can store.

  Note: You may not slant the container.

  Algorithm: Two Pointers (Greedy)
  1. Initialize two pointers, `l = 0` and `r = n - 1`.
  2. Calculate `currentArea = min(height[l], height[r]) * (r - l)`.
  3. Update `maxArea` if `currentArea` is larger.
  4. Move the pointer that points to the SHORTER line:
     - If `height[l] < height[r]`, increment `l`.
     - Otherwise, decrement `r`.
  5. The logic is that the area is limited by the shorter line. 
     Moving the taller line would only decrease the width without 
     the possibility of increasing the height limit.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the array exactly once with two pointers 
    meeting in the middle.
  - Space Complexity: O(1) auxiliary space.

  Brute Force comparison:
  - Check all possible pairs of lines.
  - Time Complexity: O(N^2).
  - The two-pointer greedy approach reduces this to linear time.
*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int max_water = 0;
        int l = 0, r = n - 1;

        while (l < r) {
            int current_water = min(height[l], height[r]) * (r - l);
            max_water = max(max_water, current_water);
            
            // Greedy move: move the pointer pointing to the shorter wall
            if (height[l] < height[r]) {
                l++;
            } else {
                r--;
            }
        }
        return max_water;
    }
};

void test(const string& label, vector<int> height, int expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    int result = sol.maxArea(height);
    cout << "  Result: " << result << " (Expected: " << expected << ")" << endl;
}

int main() {
    test("Example 1", {1, 8, 6, 2, 5, 4, 8, 3, 7}, 49);
    test("Example 2", {1, 1}, 1);
    test("Skewed heights", {10, 1, 1, 1, 10}, 40);
    return 0;
}
