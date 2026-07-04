/**
 * Problem: Height of a Binary Tree
 * Find the height of a binary tree (number of nodes along the longest path 
 * from root to leaf).
 * 
 * Strategy: Recursive DFS
 * - Height = 1 + max(height of left subtree, height of right subtree).
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(H) - Recursion stack.
 */

#include <iostream>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * Calculates height of binary tree.
 */
int calculateHeight(TreeNode* node) {
    if (!node) return 0;
    return 1 + max(calculateHeight(node->left), calculateHeight(node->right));
}

int main() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    cout << "Height of the tree: " << calculateHeight(root) << " (Expected: 3)" << endl;

    return 0;
}
