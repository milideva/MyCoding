/**
 * Problem: Mirror a Binary Tree
 * Convert a binary tree into its mirror image.
 * 
 * Strategy: Post-order DFS
 * - Recursively mirror left and right subtrees.
 * - Swap left and right pointers of the current node.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(H)
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
 * Mirrors the binary tree in-place.
 */
void mirrorTree(TreeNode* node) {
    if (!node) return;

    mirrorTree(node->left);
    mirrorTree(node->right);

    // Swap children
    TreeNode* temp = node->left;
    node->left = node->right;
    node->right = temp;
}

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
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    cout << "Original Tree (In-order): ";
    printInOrder(root);
    cout << endl;

    mirrorTree(root);

    cout << "Mirrored Tree (In-order): ";
    printInOrder(root);
    cout << endl;

    return 0;
}
