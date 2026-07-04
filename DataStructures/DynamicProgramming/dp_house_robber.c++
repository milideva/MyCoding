#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
  LeetCode 198: House Robber I (Linear)
  LeetCode 213: House Robber II (Circular)
  LeetCode 337: House Robber III (Binary Tree)

  Algorithm (Linear):
  1. Let `dp[i]` be the maximum money robbed from first `i` houses.
  2. Recursive Step: `dp[i] = max(dp[i-1], dp[i-2] + nums[i])`.
  3. Space can be optimized to O(1) by only keeping the last two values.

  Algorithm (Circular):
  1. The first and last houses cannot be robbed together.
  2. Solve for `nums[0...n-2]` and `nums[1...n-1]`.
  3. The result is the maximum of the two.

  Algorithm (Binary Tree):
  1. Each node returns a pair: `{robThisNode, skipThisNode}`.
  2. `skipThisNode = max(l_rob, l_skip) + max(r_rob, r_skip)`.
  3. `robThisNode = node->val + l_skip + r_skip`.
  
  Complexity Analysis:
  - Time Complexity: O(N) for all cases.
  - Space Complexity: O(1) for Linear/Circular, O(H) for Tree recursion stack.
*/

class Solution {
    int robLinear(const vector<int>& nums, int start, int end) {
        if (start > end) return 0;
        int prev2 = 0, prev1 = 0;
        for (int i = start; i <= end; i++) {
            int curr = max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }

public:
    int rob(vector<int>& nums) {
        return robLinear(nums, 0, nums.size() - 1);
    }

    int robII(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        return max(robLinear(nums, 0, n - 2), robLinear(nums, 1, n - 1));
    }
};

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class TreeSolution {
    pair<int, int> dfs(TreeNode* node) {
        if (!node) return {0, 0};
        auto left = dfs(node->left);
        auto right = dfs(node->right);
        
        // if we rob this node, we must NOT rob its children
        int rob = node->val + left.second + right.second;
        // if we don't rob this node, we can rob or skip its children (pick max)
        int skip = max(left.first, left.second) + max(right.first, right.second);
        
        return {rob, skip};
    }

public:
    int robIII(TreeNode* root) {
        auto res = dfs(root);
        return max(res.first, res.second);
    }
};

void test() {
    Solution sol;
    vector<int> h1 = {1, 2, 3, 1};
    cout << "Rob I:  " << sol.rob(h1) << " (Expected: 4)" << endl;
    
    vector<int> h2 = {2, 3, 2};
    cout << "Rob II: " << sol.robII(h2) << " (Expected: 3)" << endl;

    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(1);
    TreeSolution tSol;
    cout << "Rob III: " << tSol.robIII(root) << " (Expected: 7)" << endl;
}

int main() {
    test();
    return 0;
}
