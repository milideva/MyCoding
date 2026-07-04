/**
 * Problem: Binary Tree Level Order Traversal
 * Given the root of a binary tree, return the level order traversal 
 * of its nodes' values. (i.e., from left to right, level by level).
 * 
 * Strategy: BFS (Level Order Traversal)
 * - Use a queue to process nodes level by level.
 * 
 * Time Complexity: O(N) - Every node is visited once.
 * Space Complexity: O(W) - W is the maximum width of the tree.
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * Performs level order traversal.
 */
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> currentLevel;
        for (int i = 0; i < levelSize; i++) {
            TreeNode* curr = q.front();
            q.pop();
            currentLevel.push_back(curr->val);
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        result.push_back(currentLevel);
    }
    return result;
}

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    vector<vector<int>> result = levelOrder(root);

    cout << "Level order traversal:" << endl;
    for (const auto& level : result) {
        cout << "[ ";
        for (int val : level) cout << val << " ";
        cout << "]" << endl;
    }

    return 0;
}
