/**
 * Problem: Binary Tree Vertical Order Traversal
 * Given the root of a binary tree, return the vertical order traversal 
 * of its nodes' values. (i.e., from top to bottom, column by column).
 * 
 * Strategy: BFS + Hash Map
 * 1. Use a queue to store pairs of (TreeNode*, column_index).
 * 2. Root is at column 0. Left child at col-1, right at col+1.
 * 3. Use a map<int, vector<int>> to group nodes by column index.
 * 4. BFS ensures nodes are processed top-to-bottom and left-to-right.
 * 
 * Time Complexity: O(N log W) - W is the width of the tree.
 * Space Complexity: O(N) - To store all nodes in the map.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * Performs vertical order traversal.
 */
vector<vector<int>> verticalOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    map<int, vector<int>> columnTable;
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
        auto [node, col] = q.front();
        q.pop();

        columnTable[col].push_back(node->val);

        if (node->left) q.push({node->left, col - 1});
        if (node->right) q.push({node->right, col + 1});
    }

    for (auto const& [col, values] : columnTable) {
        result.push_back(values);
    }

    return result;
}

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(0);
    root->right->left = new TreeNode(1);
    root->right->right = new TreeNode(7);
    root->left->right->right = new TreeNode(2);
    root->right->left->left = new TreeNode(5);

    vector<vector<int>> result = verticalOrder(root);

    cout << "Vertical order traversal:" << endl;
    for (const auto& col : result) {
        cout << "[ ";
        for (int val : col) cout << val << " ";
        cout << "] ";
    }
    cout << endl;

    return 0;
}
