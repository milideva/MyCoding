/**
 * Problem: Find Leaves of Binary Tree
 * Collect all leaf nodes, remove them, and repeat until the tree is empty.
 * 
 * Strategy: Bottom-Up Height Calculation
 * - Define "height" as the distance from the furthest leaf (leaf height = 0).
 * - Nodes with the same height belong to the same removal level.
 * - Use DFS to calculate height and group nodes by height in a 2D vector.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N) - To store the result.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    vector<vector<int>> result;

    /**
     * Calculates height from bottom and groups nodes.
     */
    int getLeafHeight(TreeNode* node) {
        if (!node) return -1;

        int h = 1 + max(getLeafHeight(node->left), getLeafHeight(node->right));

        if (h >= (int)result.size()) {
            result.push_back({});
        }
        result[h].push_back(node->val);

        return h;
    }

public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        result.clear();
        getLeafHeight(root);
        return result;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    Solution sol;
    vector<vector<int>> leaves = sol.findLeaves(root);

    cout << "Leaves level by level removal:" << endl;
    for (const auto& level : leaves) {
        cout << "[ ";
        for (int val : level) cout << val << " ";
        cout << "]" << endl;
    }

    return 0;
}
