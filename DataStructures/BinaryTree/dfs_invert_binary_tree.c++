/**
 * Problem: Invert Binary Tree
 * Given the root of a binary tree, invert the tree (mirror it).
 * 
 * Strategy: Recursive DFS
 * - Recursively invert left and right subtrees.
 * - Swap the left and right pointers of the current node.
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

class Solution {
public:
    /**
     * Inverts the tree in-place.
     */
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;

        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);

        root->left = right;
        root->right = left;

        return root;
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
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(9);

    cout << "Original Tree (In-order): ";
    printInOrder(root);
    cout << endl;

    Solution sol;
    sol.invertTree(root);

    cout << "Inverted Tree (In-order): ";
    printInOrder(root);
    cout << endl;

    return 0;
}
