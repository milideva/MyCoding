
#include <vector>
#include <list>
#include <iostream>
#include <unordered_set>

using namespace std;
 
/*
  LeetCode 236: Lowest Common Ancestor of a Binary Tree

  Problem Description:
  Given a binary tree, find the lowest common ancestor (LCA) of two 
  given nodes in the tree.

  Note: This implementation assumes that both nodes p and q are guaranteed 
  to exist in the tree (LeetCode 236). If p or q may be missing, this is 
  a follow-up question (LeetCode 1644) and is covered in:
  dfs_lca_no_parent_pointer_ii.c++

  According to the definition of LCA on Wikipedia: "The lowest common 
  ancestor is defined between two nodes p and q as the lowest node 
  in T that has both p and q as descendants (where we allow a node 
  to be a descendant of itself)."

  Algorithm: Recursive DFS (Top-Down with Short-circuiting)
  1. If root is null, p, or q, return root.
  2. Recursively search left and right subtrees.
  3. If both left and right search return non-null, current root is the LCA.
  4. If only one is non-null, return that non-null node.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: In the worst case (e.g., LCA is a leaf or nodes are far apart), 
    we may visit every node. 
  - Space Complexity: O(H)
    Reason: Recursion stack depth is proportional to tree height (H).

  Comparison:
  - Brute Force: For every node, check if p and q are in its subtrees.
    - Time: O(N^2).
  - With Parent Pointers: Use a hash set to find the intersection of
    paths to the root.
    - Time: O(H), Space: O(H).
  - Current Approach: Optimized O(N) DFS is the best possible when
    parent pointers are unavailable and you cannot pre-process the tree.

  Brute Force Approach:
  - For every node 'node' in the tree:
  -   1. Run a search to see if node 'p' is in the subtree rooted at 'node'.
  -   2. Run a search to see if node 'q' is in the subtree rooted at 'node'.
  -   3. The first node found (starting from the bottom) that satisfies both is the LCA.
  - Time Complexity: O(N^2).
  - Comparison: The optimized DFS reduces this to O(N) by visiting each node 
    once and returning the findings upwards.
*/

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;
  TreeNode(int x) : val(x), left(NULL), right(NULL), parent(nullptr) {}
};


class Solution {
public:
  // Note: This implementation assumes both p and q exist in the tree (LC 236).
  // If either p or q may be missing, this logic is INCORRECT and should use 
  // the robust version in dfs_lca_no_parent_pointer_ii.c++ (LC 1644).
  TreeNode* lowestCommonAncestor (TreeNode *root, TreeNode* p, TreeNode * q) {
    if (!root || !p || !q) return nullptr;
    if (root->val == p->val or root->val == q->val) 
      return root;
    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);
    if (left and right) return root;
    return left ? left : right;
  }
};

// Helper function to create a binary tree from a vector.
TreeNode* createTree(const std::vector<int>& values, int index = 0) {
    if (index >= values.size() || values[index] == -1) {
        return nullptr;
    }
    TreeNode* root = new TreeNode(values[index]);
    root->left = createTree(values, 2 * index + 1);
    root->right = createTree(values, 2 * index + 2);
    return root;
}

// Helper function to find a node by value.
TreeNode* findNode(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (root->val == val) return root;
    TreeNode* leftResult = findNode(root->left, val);
    if (leftResult) return leftResult;
    return findNode(root->right, val);
}

// Test case function.
void testLowestCommonAncestor(const std::vector<int>& treeValues, int pVal, int qVal, int expectedVal) {
    TreeNode* root = createTree(treeValues);
    TreeNode* p = findNode(root, pVal);
    TreeNode* q = findNode(root, qVal);
    Solution sol;
    TreeNode* lca = sol.lowestCommonAncestor(root, p, q);
    if (lca) {
        std::cout << "LCA of nodes " << pVal << " and " << qVal << " is: " << lca->val << std::endl;
        if (lca->val == expectedVal) {
            std::cout << "Test passed." << std::endl;
        } else {
            std::cout << "Test failed. Expected LCA: " << expectedVal << std::endl;
        }
    } else {
        std::cout << "LCA not found." << std::endl;
        if (expectedVal == -1) {
            std::cout << "Test passed." << std::endl;
        } else {
            std::cout << "Test failed. Expected LCA: " << expectedVal << std::endl;
        }
    }
}

int main() {
    // Example 1
    std::vector<int> tree1 = {3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4};
    testLowestCommonAncestor(tree1, 5, 1, 3);

    // Example 2
    testLowestCommonAncestor(tree1, 5, 4, 5);

    // Example 3
    std::vector<int> tree2 = {1, 2};
    testLowestCommonAncestor(tree2, 1, 2, 1);

    // Additional Test Case: Node not in tree
    testLowestCommonAncestor(tree1, 5, 10, -1);

    return 0;
}