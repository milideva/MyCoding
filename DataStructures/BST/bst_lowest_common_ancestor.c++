#include <iostream>
#include <vector>

using namespace std;

/*
  LeetCode 235: Lowest Common Ancestor of a Binary Search Tree

  Algorithm: Iterative Search (Exploiting BST Property)
  1. Start from the root.
  2. If both `p` and `q` are smaller than root, move to left child.
  3. If both `p` and `q` are larger than root, move to right child.
  4. Otherwise, the current node is the split point (LCA).

  Complexity Analysis:
  - Time Complexity: O(H)
  - Space Complexity: O(1) iterative, O(H) recursive.
*/

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (root) {
            if (p->val < root->val && q->val < root->val) {
                root = root->left;
            } else if (p->val > root->val && q->val > root->val) {
                root = root->right;
            } else {
                return root;
            }
        }
        return nullptr;
    }
};

int main() {
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);

    Solution sol;
    TreeNode* lca = sol.lowestCommonAncestor(root, root->left, root->right);
    if (lca) cout << "LCA(2, 8): " << lca->val << " (Expected: 6)" << endl;

    lca = sol.lowestCommonAncestor(root, root->left, root->left->right);
    if (lca) cout << "LCA(2, 4): " << lca->val << " (Expected: 2)" << endl;

    return 0;
}
