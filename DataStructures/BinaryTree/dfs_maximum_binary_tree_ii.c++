/**
 * Problem: Maximum Binary Tree II
 * Suppose B is a copy of A with value val appended to it. Return Construct(B).
 * 
 * Strategy: Recursive DFS
 * - Since val was added to the END of the array, it must be on the right-most path.
 * - If val > root->val, it becomes the new root, and the old tree becomes its left child.
 * - Otherwise, recursively insert val into the root's right subtree.
 * 
 * Time Complexity: O(H) - We only traverse the right spine.
 * Space Complexity: O(H) - Recursion stack.
 */

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
};

class Solution {
public:
    /**
     * Inserts val into the maximum binary tree.
     */
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        if (!root || val > root->val) {
            return new TreeNode(val, root, nullptr);
        }
        root->right = insertIntoMaxTree(root->right, val);
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
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(2);

    cout << "Original Tree (In-order): ";
    printInOrder(root);
    cout << endl;

    Solution sol;
    root = sol.insertIntoMaxTree(root, 5);

    cout << "Tree after inserting 5 (In-order): ";
    printInOrder(root);
    cout << endl;

    return 0;
}
