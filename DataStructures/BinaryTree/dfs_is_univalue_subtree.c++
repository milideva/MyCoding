/**
 * Problem: Count Univalue Subtrees
 * Given the root of a binary tree, return the number of univalue subtrees. 
 * A univalue subtree means all nodes of the subtree have the same value.
 * 
 * Strategy: Bottom-Up DFS
 * - A node is a univalue root if:
 *   1. Its children are roots of univalue subtrees.
 *   2. Its value matches the values of its non-null children.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(H) - Recursion stack.
 */

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    int count = 0;

    /**
     * Returns true if the subtree rooted at node is a univalue subtree.
     */
    bool isUnival(TreeNode* node) {
        if (!node) return true;

        bool left = isUnival(node->left);
        bool right = isUnival(node->right);

        // If either child subtree is NOT univalue, this one can't be either
        if (!left || !right) return false;

        // Check values against children
        if (node->left && node->val != node->left->val) return false;
        if (node->right && node->val != node->right->val) return false;

        // All checks passed
        count++;
        return true;
    }

public:
    int countUnivalSubtrees(TreeNode* root) {
        count = 0;
        isUnival(root);
        return count;
    }
};

int main() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(1);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(5);

    Solution sol;
    cout << "Number of univalue subtrees: " << sol.countUnivalSubtrees(root) << " (Expected: 4)" << endl;

    return 0;
}
