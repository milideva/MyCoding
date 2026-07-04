#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

/*
  LeetCode 270: Closest Binary Search Tree Value

  Algorithm: Iterative Search
  1. Maintain a `closest` variable initialized to the root's value.
  2. While `root` is not null:
     - Update `closest` if the current node is closer to the target.
     - If target < current node, move to left child.
     - Else, move to right child.

  Complexity Analysis:
  - Time Complexity: O(H)
  - Space Complexity: O(1).
*/

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int closest = root->val;
        while (root) {
            if (abs(root->val - target) < abs(closest - target)) {
                closest = root->val;
            }
            root = target < root->val ? root->left : root->right;
        }
        return closest;
    }
};

int main() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    Solution sol;
    cout << "Closest to 3.71: " << sol.closestValue(root, 3.71) << " (Expected: 4)" << endl;
    return 0;
}
