/**
 * Problem: Count Leaf Nodes in a Binary Tree
 * Given a binary tree, return the count of all leaf nodes.
 * 
 * Strategy: Recursive DFS
 * - A node is a leaf if it has no children.
 * - Leaf count = leafCount(left) + leafCount(right).
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(H)
 */

#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * Counts leaf nodes in a binary tree.
 */
int countLeaves(TreeNode* node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return countLeaves(node->left) + countLeaves(node->right);
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    cout << "Leaf count: " << countLeaves(root) << " (Expected: 3)" << endl;

    return 0;
}
