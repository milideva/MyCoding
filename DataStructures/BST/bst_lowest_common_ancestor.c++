#include <iostream>
#include <vector>

using namespace std;

/*
  LeetCode 235: Lowest Common Ancestor of a Binary Search Tree

  =============================================================================
  METHOD 1: Iterative Search (Ideal for BST)
  =============================================================================
  Complexity Analysis:
  - Time Complexity: 
    - Best Case: O(1) if the root itself is the split point (LCA).
    - Average Case: O(H) where H is the height of the BST.
    - Worst Case: O(H) (or O(N) for a skewed tree) where H is the height, when the LCA is deep in the tree.
  - Space Complexity: O(1) auxiliary space.

  Why Iterative is Ideal for a BST:
  - O(1) Space Complexity: Since you only reassign the root pointer in a while loop,
    it runs in constant auxiliary space O(1).
  - No Call Stack Overhead: A recursive version adds stack frames for each call,
    taking O(H) space. On a skewed tree, recursion risks stack overflow,
    whereas iteration avoids this completely.
  - BST Property Dependency: Keep in mind this O(1) iterative trick only works because BST
    properties allow you to decide which direction to traverse without needing to backtrack.
    For a general Binary Tree (where values are unsorted), you would need recursion or a
    parent pointer/stack to traverse both branches.

  =============================================================================
  METHOD 2: Recursive Search (Alternative)
  =============================================================================
  Complexity Analysis:
  - Time Complexity:
    - Best Case: O(1) if the root is the split point.
    - Average Case: O(H) where H is the height of the tree.
    - Worst Case: O(H) (or O(N) for a skewed tree) where H is the height of the tree.
  - Space Complexity: O(H) auxiliary space due to the function call stack.
*/

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // Method 1: Iterative (Ideal for BST)
    TreeNode* lowestCommonAncestorIterative(TreeNode* root, TreeNode* p, TreeNode* q) {
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

    // Method 2: Recursive (Alternative)
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;

        if (p->val < root->val && q->val < root->val) {
            return lowestCommonAncestor(root->left, p, q);
        } 
        if (p->val > root->val && q->val > root->val) {
            return lowestCommonAncestor(root->right, p, q);
        }

        return root; // Found the split point
    }
};

void run_test(const string& name, TreeNode* actual, int expected_val) {
    int actual_val = actual ? actual->val : -1;
    bool passed = (actual && actual->val == expected_val);
    cout << name << ": Expected: " << expected_val 
         << " Got: " << (actual ? to_string(actual_val) : "nullptr") 
         << " " << (passed ? "PASS" : "FAIL") << endl;
}

int main() {
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);

    Solution sol;
    
    // Testing Recursive Implementation
    cout << "--- Testing Recursive Implementation ---" << endl;
    TreeNode* lca1 = sol.lowestCommonAncestor(root, root->left, root->right);
    run_test("LCA(2, 8)", lca1, 6);

    TreeNode* lca2 = sol.lowestCommonAncestor(root, root->left, root->left->right);
    run_test("LCA(2, 4)", lca2, 2);

    // Testing Iterative Implementation
    cout << "\n--- Testing Iterative Implementation ---" << endl;
    TreeNode* lca3 = sol.lowestCommonAncestorIterative(root, root->left, root->right);
    run_test("LCA(2, 8)", lca3, 6);

    TreeNode* lca4 = sol.lowestCommonAncestorIterative(root, root->left, root->left->right);
    run_test("LCA(2, 4)", lca4, 2);

    return 0;
}
