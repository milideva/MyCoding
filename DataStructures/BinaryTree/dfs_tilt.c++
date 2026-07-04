/**
 * Problem: Binary Tree Tilt
 * Return the sum of every tree node's tilt. The tilt of a node is the absolute 
 * difference between the sum of all left subtree values and the sum of all 
 * right subtree values.
 * 
 * Strategy: Post-order DFS
 * - Each recursive call returns the total sum of the subtree rooted at that node.
 * - While calculating subtree sums, update a global tilt sum.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(H)
 */

#include <iostream>
#include <cmath>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    int totalTilt = 0;

    /**
     * Calculates the sum of values in a subtree and updates totalTilt.
     */
    int calculateSubtreeSum(TreeNode* node) {
        if (!node) return 0;

        int leftSum = calculateSubtreeSum(node->left);
        int rightSum = calculateSubtreeSum(node->right);

        totalTilt += abs(leftSum - rightSum);

        return node->val + leftSum + rightSum;
    }

public:
    int findTilt(TreeNode* root) {
        totalTilt = 0;
        calculateSubtreeSum(root);
        return totalTilt;
    }
};

int main() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(9);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(7);

    Solution sol;
    cout << "Total Tilt: " << sol.findTilt(root) << " (Expected: 15)" << endl;

    return 0;
}
