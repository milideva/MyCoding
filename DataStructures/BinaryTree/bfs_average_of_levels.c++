/**
 * Problem: Average of Levels in Binary Tree
 * Given the root of a binary tree, return the average value of the nodes 
 * on each level in the form of an array.
 * 
 * Strategy: BFS (Level Order Traversal)
 * - Use a queue to traverse the tree level by level.
 * - For each level, calculate the sum of node values and the count of nodes.
 * 
 * Time Complexity: O(N) - Every node is visited once.
 * Space Complexity: O(W) - W is the maximum width of the tree (max nodes in a level).
 */

#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * Calculates the average of each level.
 */
vector<double> averageOfLevels(TreeNode* root) {
    vector<double> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        double levelSum = 0;
        for (int i = 0; i < levelSize; i++) {
            TreeNode* curr = q.front();
            q.pop();
            levelSum += curr->val;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        result.push_back(levelSum / levelSize);
    }
    return result;
}

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    vector<double> averages = averageOfLevels(root);

    cout << "Average of each level: [";
    for (size_t i = 0; i < averages.size(); i++) {
        cout << fixed << setprecision(2) << averages[i] << (i == averages.size() - 1 ? "" : ", ");
    }
    cout << "]" << endl;

    return 0;
}
