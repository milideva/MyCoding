/**
 * Problem: Vertical Order Traversal of a Binary Tree
 * Calculate the vertical order traversal of a binary tree with strict sorting:
 * 1. Sort by column index (left to right).
 * 2. If same column, sort by row index (top to bottom).
 * 3. If same column and row, sort by node value.
 * 
 * Strategy: DFS + Sorted Nested Map
 * - Use map<int, map<int, multiset<int>>> to store nodes at (col, row).
 * - multiset handles the value sorting for identical coordinates.
 * - map handles sorting by column and then by row.
 * 
 * Time Complexity: O(N log N)
 * Space Complexity: O(N)
 */

#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    // col -> row -> {values}
    map<int, map<int, multiset<int>>> nodes;

    void dfs(TreeNode* node, int row, int col) {
        if (!node) return;
        nodes[col][row].insert(node->val);
        dfs(node->left, row + 1, col - 1);
        dfs(node->right, row + 1, col + 1);
    }

public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        nodes.clear();
        dfs(root, 0, 0);

        vector<vector<int>> result;
        for (auto const& [col, rows] : nodes) {
            vector<int> currentColumn;
            for (auto const& [row, values] : rows) {
                for (int val : values) {
                    currentColumn.push_back(val);
                }
            }
            result.push_back(currentColumn);
        }
        return result;
    }
};

int main() {
    // Tree: [1,2,3,4,5,6,7]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    Solution sol;
    vector<vector<int>> result = sol.verticalTraversal(root);

    cout << "Vertical order traversal:" << endl;
    for (const auto& col : result) {
        cout << "[ ";
        for (int val : col) cout << val << " ";
        cout << "] ";
    }
    cout << endl;

    return 0;
}
