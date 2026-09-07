#include <iostream>
#include <limits>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

/*
  LeetCode 98: Validate Binary Search Tree

  Problem Description:
  Given the root of a binary tree, determine if it is a valid BST.

  Algorithm 1: Min-Max Range Check
  - A node is valid if its value is between `min` and `max` constraints.
  - Left child: `(min, node->val)`
  - Right child: `(node->val, max)`
  - Use `long long` to handle `INT_MIN` and `INT_MAX`.

  Algorithm 2: In-order Traversal
  - An in-order traversal of a BST must be strictly increasing.
  - Track `prev` node and ensure `curr->val > prev->val`.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(H).
*/

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // Running time O(N), where N is the number of nodes in the tree.
    // Space complexity O(H), where H is the height of the tree.
    bool isValidBST(TreeNode* root, long long minVal = LLONG_MIN, long long maxVal = LLONG_MAX) {
        if (!root) return true;
        // Note that we use strict inequalities (<= and >=) to ensure that duplicates are not allowed in the BST.
        if (root->val <= minVal || root->val >= maxVal) return false;
        return isValidBST(root->left, minVal, root->val) &&
               isValidBST(root->right, root->val, maxVal);
    }

    void destroy(TreeNode* root) {
        if (!root) return;
        destroy(root->left);
        destroy(root->right);
        delete root;
    }
};

void test(TreeNode* root, bool expected) {
    Solution sol;
    bool result = sol.isValidBST(root);
    cout << "Valid BST: " << boolalpha << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);
    test(root, true);

    TreeNode* root2 = new TreeNode(5);
    root2->left = new TreeNode(1);
    root2->right = new TreeNode(4);
    root2->right->left = new TreeNode(3);
    root2->right->right = new TreeNode(6);
    test(root2, false);

    Solution sol;
    sol.destroy(root);
    sol.destroy(root2);
    return 0;
}
