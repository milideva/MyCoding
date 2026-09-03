#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/*
  LeetCode 1448: Count Good Nodes in Binary Tree

  Problem Description:
  Given a binary tree root, a node X in the tree is named good if in the path 
  from root to X there are no nodes with a value greater than X.
  Return the number of good nodes in the binary tree.

  Example 1:
  Input: root = [3,1,4,3,null,1,5]
  Output: 4
  Explanation: Nodes in blue are good.
  - Root Node (3) is always a good node.
  - Node 4 -> (3,4) is the maximum value in the path starting from the root.
  - Node 5 -> (3,4,5) is the maximum value in the path.
  - Node 3 -> (3,1,3) is the maximum value in the path.

  Example 2:
  Input: root = [3,3,null,4,2]
  Output: 3
  Explanation: Node 2 -> (3, 3, 2) is not good, because "3" is higher than it.

  Example 3:
  Input: root = [1]
  Output: 1

  Constraints:
  - The number of nodes in the binary tree is in the range [1, 10^5].
  - Each node's value is between [-10^4, 10^4].

  Strategy: Pre-Order DFS Traversal
  - We traverse the tree from root to leaf, passing down the maximum value 
    seen so far (`maxVal`) along the current path.
  - At each node:
    - If the node's value is greater than or equal to `maxVal`, it is a "good node".
      We increment our count and update `maxVal` to the node's value.
    - We then recursively call the helper on the left and right subtrees 
      with the updated `maxVal`.
  - Note: Although the recursive helper function is named `inOrder`, the logic 
    is functionally a **Pre-order** traversal (Root -> Left -> Right) because 
    we evaluate and update the parent node's maximum value *before* visiting 
    its children.

  Complexity Analysis:
  - Time Complexity:
    - Best Case: O(N) where N is the number of nodes in the tree.
    - Average Case: O(N).
    - Worst Case: O(N).
    Reason: We must visit every node in the binary tree exactly once.
  - Space Complexity:
    - Worst Case: O(H) recursion stack space, where H is the height of the tree 
      (O(log N) for balanced trees, O(N) for skewed trees).
*/

class Solution {
    int good = 0;

    void inOrder (TreeNode *node, int maxVal) {
        if (!node) return;
        if (node->val >= maxVal) {
            good++;
            maxVal = node->val;
        }
        inOrder(node->left, maxVal);
        inOrder(node->right, maxVal);
    }

public:
    int goodNodes(TreeNode* root) {
        good = 0; // Reset state variable to ensure reentrancy across multiple test runs in main()
        if (!root) return 0;
        inOrder(root, root->val);
        return good;
    }
};

// =========================================================================
// TESTING HARNESS
// =========================================================================

void runTest(const string& label, TreeNode* root, int expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    int result = sol.goodNodes(root);
    cout << "  Good Nodes Count: " << result << " (Expected: " << expected << ") ";
    if (result == expected) {
        cout << "[PASS]" << endl;
    } else {
        cout << "[FAIL]" << endl;
    }
    cout << endl;
}

int main() {
    cout << "=========================================================" << endl;
    cout << "               RUNNING GOOD NODES TESTS                  " << endl;
    cout << "=========================================================" << endl;

    /*
     * Test 1: Example 1
     *          3
     *         / \
     *        1   4
     *       /   / \
     *      3   1   5
     */
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(1);
    root1->right = new TreeNode(4);
    root1->left->left = new TreeNode(3);
    root1->right->left = new TreeNode(1);
    root1->right->right = new TreeNode(5);
    runTest("Example 1", root1, 4);

    /*
     * Test 2: Example 2
     *          3
     *         /
     *        3
     *       / \
     *      4   2
     */
    TreeNode* root2 = new TreeNode(3);
    root2->left = new TreeNode(3);
    root2->left->left = new TreeNode(4);
    root2->left->right = new TreeNode(2);
    runTest("Example 2", root2, 3);

    /*
     * Test 3: Example 3 (Single Node)
     *          1
     */
    TreeNode* root3 = new TreeNode(1);
    runTest("Example 3 (Single Node)", root3, 1);

    // Clean up memory
    delete root1->left->left;
    delete root1->right->left;
    delete root1->right->right;
    delete root1->left;
    delete root1->right;
    delete root1;

    delete root2->left->left;
    delete root2->left->right;
    delete root2->left;
    delete root2;

    delete root3;

    cout << "=========================================================" << endl;
    return 0;
}
