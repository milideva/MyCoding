/**
 * Problem: Sum of Root To Leaf Binary Numbers
 * Each root-to-leaf path represents a binary number starting with the 
 * most significant bit. Return the sum of these numbers.
 * 
 * Strategy: Recursive DFS
 * - Pass current binary value down to children.
 * - Current value = (parentValue << 1) | node->val.
 * - If leaf reached, add current value to total sum.
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
    int totalSum = 0;

    void dfs(TreeNode* node, int currentSum) {
        if (!node) return;

        currentSum = (currentSum << 1) | node->val;

        // If leaf node, add to total
        if (!node->left && !node->right) {
            totalSum += currentSum;
            return;
        }

        dfs(node->left, currentSum);
        dfs(node->right, currentSum);
    }

public:
    int sumRootToLeaf(TreeNode* root) {
        totalSum = 0;
        dfs(root, 0);
        return totalSum;
    }
};

int main() {
    // Tree: [1,0,1,0,1,0,1] -> Binary paths 100, 101, 110, 111.
    // Values: 4, 5, 6, 7. Sum = 22.
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(0);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(1);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(1);

    Solution sol;
    cout << "Sum root to leaf binary: " << sol.sumRootToLeaf(root) << " (Expected: 22)" << endl;

    return 0;
}
