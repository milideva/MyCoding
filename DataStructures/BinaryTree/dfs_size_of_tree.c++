/**
 * Problem: Size of a Binary Tree
 * Given a binary tree, calculate the total number of nodes present in it.
 * 
 * Strategy: Recursive DFS
 * - Size = 1 + size(left) + size(right).
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
 * Calculates the total number of nodes in the binary tree.
 */
int calculateSize(TreeNode* node) {
    if (!node) return 0;
    return 1 + calculateSize(node->left) + calculateSize(node->right);
}

int main() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    cout << "Size of the tree: " << calculateSize(root) << " (Expected: 5)" << endl;

    return 0;
}
