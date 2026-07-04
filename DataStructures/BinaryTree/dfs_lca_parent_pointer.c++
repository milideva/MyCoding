/**
 * Problem: Lowest Common Ancestor of a Binary Tree III (with Parent Pointers)
 * Given two nodes p and q of a binary tree where each node has a parent pointer, 
 * find their lowest common ancestor.
 * 
 * Strategy: Path Intersection (O(1) space variant)
 * 1. Find the depths of p and q by traversing up to the root.
 * 2. Advance the deeper node until it reaches the same depth as the shallower node.
 * 3. Advance both nodes together until they meet. The meeting point is the LCA.
 * 
 * Time Complexity: O(H)
 * Space Complexity: O(1)
 */

#include <iostream>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right, *parent;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
};

class Solution {
    /**
     * Calculates the depth of a node from the root.
     */
    int getDepth(TreeNode* node) {
        int depth = 0;
        while (node) {
            depth++;
            node = node->parent;
        }
        return depth;
    }

public:
    /**
     * Finds the LCA of p and q using parent pointers.
     */
    TreeNode* lowestCommonAncestor(TreeNode* p, TreeNode* q) {
        int d1 = getDepth(p);
        int d2 = getDepth(q);

        // Advance the deeper node to the same level
        while (d1 > d2) {
            p = p->parent;
            d1--;
        }
        while (d2 > d1) {
            q = q->parent;
            d2--;
        }

        // Advance both nodes until they meet
        while (p != q) {
            p = p->parent;
            q = q->parent;
        }

        return p;
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->parent = root;
    root->right->parent = root;

    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->left->left->parent = root->left;
    root->left->right->parent = root->left;

    Solution sol;
    TreeNode* p = root->left; // 5
    TreeNode* q = root->left->right; // 2
    TreeNode* res = sol.lowestCommonAncestor(p, q);
    cout << "LCA of 5 and 2: " << (res ? to_string(res->val) : "null") << " (Expected: 5)" << endl;

    return 0;
}
