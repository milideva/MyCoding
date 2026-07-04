/**
 * Problem: Maximum Binary Tree
 * Build a maximum binary tree from an array nums where:
 * 1. Root is the maximum value in nums.
 * 2. Left subtree is built from prefix to the left of max.
 * 3. Right subtree is built from suffix to the right of max.
 * 
 * Strategy: Recursive DFS (O(N^2) worst case, O(N log N) average)
 * - Find max element in current range.
 * - Create root.
 * - Recurse for left and right ranges.
 * 
 * Time Complexity: O(N^2) - Can be improved to O(N) using a monotonic stack.
 * Space Complexity: O(N) - Recursion stack.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    /**
     * Recursive helper to build maximum binary tree.
     */
    TreeNode* build(const vector<int>& nums, int start, int end) {
        if (start > end) return nullptr;

        // Find index of maximum element in range [start, end]
        int maxIdx = start;
        for (int i = start + 1; i <= end; i++) {
            if (nums[i] > nums[maxIdx]) {
                maxIdx = i;
            }
        }

        TreeNode* root = new TreeNode(nums[maxIdx]);
        root->left = build(nums, start, maxIdx - 1);
        root->right = build(nums, maxIdx + 1, end);

        return root;
    }

public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return build(nums, 0, nums.size() - 1);
    }
};

/**
 * Utility to print in-order traversal.
 */
void printInOrder(TreeNode* root) {
    if (!root) return;
    printInOrder(root->left);
    cout << root->val << " ";
    printInOrder(root->right);
}

int main() {
    vector<int> nums = {3, 2, 1, 6, 0, 5};
    Solution sol;
    TreeNode* root = sol.constructMaximumBinaryTree(nums);

    cout << "Maximum Binary Tree (In-order): ";
    printInOrder(root);
    cout << endl;

    return 0;
}
