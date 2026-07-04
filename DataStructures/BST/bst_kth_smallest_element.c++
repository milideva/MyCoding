#include <iostream>
#include <vector>

using namespace std;

/*
  LeetCode 230: Kth Smallest Element in a BST

  Algorithm: Recursive In-order Traversal
  1. Perform in-order traversal (Left, Root, Right).
  2. Decrement `k` when visiting a node.
  3. When `k == 0`, we found the element.

  Complexity Analysis:
  - Time Complexity: O(H + K)
  - Space Complexity: O(H).
*/

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    int result = -1;
    void inorder(TreeNode* node, int& k) {
        if (!node || k <= 0) return;
        inorder(node->left, k);
        if (--k == 0) {
            result = node->val;
            return;
        }
        inorder(node->right, k);
    }

public:
    int kthSmallest(TreeNode* root, int k) {
        inorder(root, k);
        return result;
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->left->right = new TreeNode(2);

    Solution sol;
    cout << "1st Smallest: " << sol.kthSmallest(root, 1) << " (Expected: 1)" << endl;
    
    Solution sol2; // Reset state
    cout << "3rd Smallest: " << sol2.kthSmallest(root, 3) << " (Expected: 3)" << endl;

    return 0;
}
