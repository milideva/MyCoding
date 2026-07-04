/**
 * Problem: Lowest Common Ancestor of a Binary Tree
 * Given a binary tree, find the lowest common ancestor (LCA) of two given 
 * nodes in the tree. p and q are guaranteed to exist.
 * 
 * Strategy: Recursive DFS
 * - If root is null, p, or q, return root.
 * - Recursively search in left and right subtrees.
 * - If both subtrees return non-null, root is the LCA.
 * - Otherwise, return the non-null result from either subtree.
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

class Solution {
public:
    /**
     * Finds the LCA of p and q. Assumes p and q exist.
     */
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) return root;

        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if (left && right) return root;
        return left ? left : right;
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);

    Solution sol;
    TreeNode* p = root->left; // 5
    TreeNode* q = root->right; // 1
    TreeNode* res = sol.lowestCommonAncestor(root, p, q);
    cout << "LCA of 5 and 1: " << res->val << " (Expected: 3)" << endl;

    q = root->left->right; // 2
    res = sol.lowestCommonAncestor(root, p, q);
    cout << "LCA of 5 and 2: " << res->val << " (Expected: 5)" << endl;

    return 0;
}
