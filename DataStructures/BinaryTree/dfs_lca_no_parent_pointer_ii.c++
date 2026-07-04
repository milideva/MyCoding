/**
 * Problem: Lowest Common Ancestor of a Binary Tree II (p or q might not exist)
 * Given the root of a binary tree, return the LCA of two nodes p and q. 
 * If either node does not exist, return null.
 * 
 * Strategy: Post-order DFS
 * - Traverse the entire tree to find p and q.
 * - Unlike the standard LCA (where p and q are guaranteed to exist), we 
 *   cannot return early when we find one node.
 * - We must maintain flags to track if both nodes were actually found.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(H)
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
    bool foundP = false;
    bool foundQ = false;

    TreeNode* findLCA(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;

        TreeNode* left = findLCA(root->left, p, q);
        TreeNode* right = findLCA(root->right, p, q);

        if (root == p) {
            foundP = true;
            return root;
        }
        if (root == q) {
            foundQ = true;
            return root;
        }

        if (left && right) return root;
        return left ? left : right;
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        foundP = false;
        foundQ = false;
        TreeNode* lca = findLCA(root, p, q);
        return (foundP && foundQ) ? lca : nullptr;
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
    TreeNode* q = root->left->right; // 2
    TreeNode* res = sol.lowestCommonAncestor(root, p, q);
    cout << "LCA of 5 and 2: " << (res ? to_string(res->val) : "null") << " (Expected: 5)" << endl;

    TreeNode* nonExistent = new TreeNode(10);
    res = sol.lowestCommonAncestor(root, p, nonExistent);
    cout << "LCA of 5 and 10: " << (res ? to_string(res->val) : "null") << " (Expected: null)" << endl;

    return 0;
}
