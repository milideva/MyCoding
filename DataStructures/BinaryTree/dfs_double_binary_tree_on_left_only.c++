/**
 * Problem: Double Tree (Duplicate nodes on left)
 * For every node in the binary tree, create a duplicate node with 
 * the same value and insert it as the left child of the original node.
 * 
 * Strategy: Post-order Traversal (Bottom-Up)
 * - Traverse left and right subtrees first.
 * - Create a duplicate node and insert it between current and original left.
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

/**
 * Creates a duplicate node and inserts it on the left of each node.
 */
void doubleTree(TreeNode* node) {
    if (!node) return;

    // Recurse first to avoid infinite recursion
    doubleTree(node->left);
    doubleTree(node->right);

    // Insert duplicate
    TreeNode* oldLeft = node->left;
    node->left = new TreeNode(node->val);
    node->left->left = oldLeft;
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

    cout << "Original Tree (In-order): ";
    printInOrder(root);
    cout << endl;

    doubleTree(root);

    cout << "Doubled Tree (In-order): ";
    printInOrder(root);
    cout << endl;

    return 0;
}
