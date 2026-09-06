/**
 * Problem: Check if two nodes are cousins
 * Two nodes of a binary tree are cousins if they have the same depth 
 * but different parents.
 * 
 * Strategy: BFS (Level Order Traversal)
 * - Process nodes level by level.
 * - For each level, check if both target nodes exist.
 * - Also check if they share the same parent.
 * 
 * Complexity Analysis:
 * - Time Complexity:
 *   - Best Case: O(N) where N is the number of nodes in the tree.
 *   - Average Case: O(N).
 *   - Worst Case: O(N).
 *   Reason: In the worst case we must traverse all nodes in the tree level-by-level.
 * - Space Complexity:
 *   - Worst Case: O(W) queue space, where W is the maximum width of the tree 
 *     at any level (which can be up to N/2 for a full binary tree).
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
 * Checks if two nodes with values x and y are cousins.
 */
bool isCousins(TreeNode* root, int x, int y) {
    if (!root) return false;

    queue <pair <TreeNode*, TreeNode*> > q; // {node, parent}
    q.push({root, nullptr});

    while (!q.empty()) {
        int levelSize = q.size();
        TreeNode *parentX = nullptr, *parentY = nullptr;

        for (int i = 0; i < levelSize; i++) {
            auto [node, parent] = q.front();
            q.pop();

            if (node->val == x) parentX = parent;
            if (node->val == y) parentY = parent;

            if (node->left) q.push({node->left, node});
            if (node->right) q.push({node->right, node});
        }

        // If both nodes found at this level
        if (parentX && parentY) {
            return parentX != parentY; // Cousins if parents are different
        }
        // If only one node found at this level, they can't be cousins
        if (parentX || parentY) return false;
    }

    return false;
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    int x = 4, y = 5;
    cout << "Nodes " << x << " and " << y << " are cousins: " 
         << (isCousins(root, x, y) ? "Yes" : "No") << endl;

    x = 2; y = 3;
    cout << "Nodes " << x << " and " << y << " are cousins: " 
         << (isCousins(root, x, y) ? "Yes" : "No") << endl;

    return 0;
}
