/**
 * Problem: Common Binary Tree Traversals
 * Implement Pre-order, In-order, Post-order (Recursive) and Level-order (Iterative).
 * 
 * Strategy: DFS (Recursion) and BFS (Queue)
 * 
 * Time Complexity: O(N) for all traversals.
 * Space Complexity: O(H) for DFS (recursion stack), O(W) for BFS (queue).
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
 * Pre-order: Root -> Left -> Right
 */
void preOrder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    preOrder(root->left);
    preOrder(root->right);
}

/**
 * In-order: Left -> Root -> Right
 */
void inOrder(TreeNode* root) {
    if (!root) return;
    inOrder(root->left);
    cout << root->val << " ";
    inOrder(root->right);
}

/**
 * Post-order: Left -> Right -> Root
 */
void postOrder(TreeNode* root) {
    if (!root) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->val << " ";
}

/**
 * Level-order: Top -> Bottom, Left -> Right
 */
void levelOrder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        cout << curr->val << " ";
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    cout << "Pre-order:  "; preOrder(root); cout << endl;
    cout << "In-order:   "; inOrder(root);  cout << endl;
    cout << "Post-order: "; postOrder(root); cout << endl;
    cout << "Level-order: "; levelOrder(root); cout << endl;

    return 0;
}
