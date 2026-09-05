#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

/*
  Height vs. Depth in a Binary Tree

  1. Height of a Node: (Bottom-Up / Post-Order)
     - Definition: The number of nodes on the longest path from that node to a leaf.
     - Convention: A leaf node has a height of 1. A null node has a height of 0.
     - Process: Bottom-Up. A parent node cannot determine its height until it 
       receives the heights of both its left and right subtrees.
     - Formula: height = 1 + max(leftHeight, rightHeight)

  2. Depth of a Node: (Top-Down / Pre-Order)
     - Definition: The number of edges (or nodes) from the root to that node.
     - Convention: The root node has a depth of 0.
     - Process: Top-Down. We compute and assign the depth to the current node 
       first, and then pass `currentDepth + 1` down to its left and right subtrees.

  Complexity Analysis:
  - Time Complexity:
    - Best Case: O(N) where N is the number of nodes in the tree.
    - Average Case: O(N).
    - Worst Case: O(N).
    Reason: We visit each node exactly once for height, and exactly once for depth.
  - Space Complexity:
    - Worst Case: O(H) recursion stack space, where H is the height of the tree 
      (O(log N) for balanced trees, O(N) for skewed trees).
*/

struct TreeNode {
    int val;
    int height;
    int depth;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), height(0), depth(0), left(nullptr), right(nullptr) {}
};

// Bottom-Up: Computes height after receiving results from children
int computeAndStoreHeight(TreeNode* node) {
    if (!node) return 0;

    // 1. Recurse down to subtrees
    int leftHeight = computeAndStoreHeight(node->left);
    int rightHeight = computeAndStoreHeight(node->right);

    // 2. Compute and store height for current node
    node->height = 1 + max(leftHeight, rightHeight);

    // 3. Return stored height to parent
    return node->height;
}

// Top-Down: Computes depth before visiting children
void computeAndStoreDepth(TreeNode* node, int currentDepth = 0) {
    if (!node) return;

    // 1. Process current node
    node->depth = currentDepth;

    // 2. Pass depth down to left and right subtrees
    computeAndStoreDepth(node->left, currentDepth + 1);
    computeAndStoreDepth(node->right, currentDepth + 1);
}

// =========================================================================
// TESTING HARNESS
// =========================================================================

void printNodeMetrics(TreeNode* node, const string& name) {
    if (!node) return;
    cout << "Node " << name << " (Val: " << node->val << ") -> Height: " 
         << node->height << ", Depth: " << node->depth << endl;
    printNodeMetrics(node->left, name + "->left");
    printNodeMetrics(node->right, name + "->right");
}

int main() {
    cout << "=========================================================" << endl;
    cout << "             RUNNING HEIGHT & DEPTH TESTS                " << endl;
    cout << "=========================================================" << endl;

    /*
     * Build the following Binary Tree:
     *          4
     *         / \
     *        2   5
     *       / \
     *      1   3
     */
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    // Compute metrics
    computeAndStoreHeight(root);
    computeAndStoreDepth(root, 0);

    // Print and Verify Metrics
    printNodeMetrics(root, "root");

    // Clean up memory
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;

    cout << "=========================================================" << endl;
    return 0;
}
