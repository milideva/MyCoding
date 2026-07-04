/**
 * Problem: Binary Tree Right Side View
 * Imagine yourself standing on the right side of a binary tree. 
 * Return the values of the nodes you can see ordered from top to bottom.
 * 
 * Strategy: BFS (Level Order Traversal)
 * - For each level, the last node in the queue is the one visible from the right side.
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

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        if (!root) return result;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                TreeNode* curr = q.front();
                q.pop();

                // If it's the last node of the level, add to result
                if (i == levelSize - 1) {
                    result.push_back(curr->val);
                }

                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
        }
        return result;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(4);

    Solution sol;
    vector<int> result = sol.rightSideView(root);

    cout << "Right side view: [ ";
    for (int val : result) cout << val << " ";
    cout << "]" << endl;

    return 0;
}
