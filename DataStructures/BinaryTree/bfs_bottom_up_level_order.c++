/**
 * Problem: Binary Tree Level Order Traversal II (Bottom-Up)
 * Given the root of a binary tree, return the bottom-up level order traversal 
 * of its nodes' values. (i.e., from left to right, level by level from leaf to root).
 * 
 * Strategy: BFS (Level Order Traversal) + Vector Reversal
 * 1. Perform a standard level-order traversal using a queue.
 * 2. Store each level's values in a vector.
 * 3. Reverse the order of levels at the end.
 * 
 * Time Complexity: O(N) - Every node is visited once.
 * Space Complexity: O(N) - To store the result and the queue.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * Performs bottom-up level order traversal.
 */
vector<vector<int>> levelOrderBottom(TreeNode* root) {
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

    reverse(result.begin(), result.end());
    return result;
}

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    vector<vector<int>> result = levelOrderBottom(root);

    cout << "Bottom-up level order traversal:" << endl;
    for (const auto& level : result) {
        cout << "[ ";
        for (int val : level) cout << val << " ";
        cout << "]" << endl;
    }

    return 0;
}
