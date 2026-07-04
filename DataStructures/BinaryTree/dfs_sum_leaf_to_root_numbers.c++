/**
 * Problem: Sum Root to Leaf Numbers
 * Each root-to-leaf path in the tree represents a number (e.g., 1->2->3 = 123).
 * Return the total sum of all root-to-leaf numbers.
 * 
 * Strategy: Recursive DFS
 * - Pass the current path value down to children.
 * - Current value = parentValue * 10 + node->val.
 * - If leaf reached, add current value to total sum.
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
    int totalSum = 0;

    void dfs(TreeNode* node, int currentSum) {
        if (!node) return;

        currentSum = currentSum * 10 + node->val;

        // If leaf node, add to total
        if (!node->left && !node->right) {
            totalSum += currentSum;
            return;
        }

        dfs(node->left, currentSum);
        dfs(node->right, currentSum);
    }

public:
    int sumNumbers(TreeNode* root) {
        totalSum = 0;
        dfs(root, 0);
        return totalSum;
    }
};

int main() {
    // Tree: [4, 9, 0, null, null, null, 1] -> Paths 49, 401. Sum = 450.
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(9);
    root->right = new TreeNode(0);
    root->right->right = new TreeNode(1);

    Solution sol;
    cout << "Sum root to leaf: " << sol.sumNumbers(root) << " (Expected: 450)" << endl;

    return 0;
}
