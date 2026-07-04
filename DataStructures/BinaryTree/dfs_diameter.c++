/**
 * Problem: Diameter of Binary Tree
 * Return the length of the diameter of the tree. The diameter of a binary tree 
 * is the length of the longest path between any two nodes in a tree.
 * 
 * Strategy: Bottom-Up DFS (O(N))
 * - Use a helper function that returns the height of the current subtree.
 * - While calculating height, update the maximum diameter found so far.
 * - Diameter at node = height(left) + height(right).
 * 
 * Time Complexity: O(N) - Every node is visited once.
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

class Solution {
    int maxDiameter = 0;

    /**
     * Returns height of subtree while updating maxDiameter.
     */
    int calculateHeight(TreeNode* node) {
        if (!node) return 0;

        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);

        // Longest path through this node is leftHeight + rightHeight
        maxDiameter = max(maxDiameter, leftHeight + rightHeight);

        // Return height of current node
        return 1 + max(leftHeight, rightHeight);
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        maxDiameter = 0;
        calculateHeight(root);
        return maxDiameter;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    Solution sol;
    cout << "Diameter of the given binary tree: " << sol.diameterOfBinaryTree(root) << endl;

    return 0;
}
