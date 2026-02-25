#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <cfloat>
#include <iomanip>

using namespace std;

/*

235. Lowest Common Ancestor of a Binary Search Tree

Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.

*/

#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


/*

         6
       /   \
     2      8
    / \    / \
   0   4  7   9
      / \
     3   5

*/

class Solution {
private:
    // Helper function to check if a node exists in the BST.
    // Time complexity: O(H), where H is the height of the tree.
    bool exists(TreeNode* root, TreeNode* node) {
        if (!root || !node) return false;
        TreeNode* current = root;
        while (current) {
            if (current->val == node->val) {
                return true;
            }
            current = node->val < current->val ? current->left : current->right;
        }
        return false;
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || !p || !q) return nullptr;

        // A robust solution must first verify both nodes exist in the tree.
        // If either is missing, an LCA is not defined.
        if (!exists(root, p) || !exists(root, q)) {
            return nullptr;
        }

        // The original logic is correct if both nodes exist.
        if (root->val > p->val && root->val > q->val) return lowestCommonAncestor(root->left, p, q);
        if (root->val < p->val && root->val < q->val) return lowestCommonAncestor(root->right, p, q);
        return root; // This is the split point, so it's the LCA.
    }
};

// Helper function to insert nodes into the BST.
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) {
        root->left = insertIntoBST(root->left, val);
    } else {
        root->right = insertIntoBST(root->right, val);
    }
    return root;
}

// Helper function to create a BST from a vector.
TreeNode* createBST(const std::vector<int>& values) {
    TreeNode* root = nullptr;
    for (int val : values) {
        if (val != -1) {
            root = insertIntoBST(root, val);
        }
    }
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
    TreeNode* root = createBST(treeValues);
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
    std::vector<int> tree1 = {6,2,8,0,4,7,9,-1,-1,3,5};
    testLowestCommonAncestor(tree1, 2, 8, 6);

    // Example 2
    testLowestCommonAncestor(tree1, 2, 4, 2);

    // Example 3
    std::vector<int> tree2 = {2, 1};
    testLowestCommonAncestor(tree2, 2, 1, 2);

    return 0;
}