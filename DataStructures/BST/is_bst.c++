#include <iostream>
#include <limits>
#include <vector>
#include <algorithm> // For std::max and std::min

// Definition for a binary tree node, using C++ conventions.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    // Constructor for easy node creation.
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/*
  LeetCode 98: Validate Binary Search Tree

  Problem Description:
  Given the root of a binary tree, determine if it is a valid binary 
  search tree (BST).

  A valid BST is defined as follows:
  - The left subtree of a node contains only nodes with keys less than 
    the node's key.
  - The right subtree of a node contains only nodes with keys greater 
    than the node's key.
  - Both the left and right subtrees must also be binary search trees.

  Algorithm:
private:
    // Helper to find the maximum value in a subtree.
    int findMax(TreeNode* node) {
        if (!node) return std::numeric_limits<int>::min();
        return std::max({node->val, findMax(node->left), findMax(node->right)});
    }

    // Helper to find the minimum value in a subtree.
    int findMin(TreeNode* node) {
        if (!node) return std::numeric_limits<int>::max();
        return std::min({node->val, findMin(node->left), findMin(node->right)});
    }

public:
    bool isBST_bruteforce(TreeNode* root) {
        if (!root) {
            return true;
        }

        // Check if max value in left subtree is less than the current node's value.
        if (root->left && findMax(root->left) >= root->val) {
            return false;
        }

        // Check if min value in right subtree is greater than the current node's value.
        if (root->right && findMin(root->right) <= root->val) {
            return false;
        }

        // Recursively check if left and right subtrees are also BSTs.
        return isBST_bruteforce(root->left) && isBST_bruteforce(root->right);
    }

    //=========================================================================
    // Method 2: Min-Max Range Check (Efficient)
    // Pass down min and max constraints to children.
    // Time Complexity: O(N) as we visit each node once.
    // Space Complexity: O(H) for recursion stack, where H is tree height.
    //=========================================================================
private:
    // Helper function using long long to correctly handle nodes with INT_MIN/INT_MAX values.
    bool isValidBSTHelper(TreeNode* node, long long minVal, long long maxVal) {
        if (!node) {
            return true;
        }
        if (node->val <= minVal || node->val >= maxVal) {
            return false;
        }
        // The new max for the left subtree is the current node's value.
        // The new min for the right subtree is the current node's value.
        return isValidBSTHelper(node->left, minVal, node->val) &&
               isValidBSTHelper(node->right, node->val, maxVal);
    }

public:
    bool isBST_range(TreeNode* root) {
        return isValidBSTHelper(root, std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max());
    }

    //=========================================================================
    // Method 3: In-order Traversal (Efficient)
    // In-order traversal of a BST yields a sorted sequence. We just need
    // to check if the current node is greater than the previous one.
    // This implementation avoids using a global variable by passing the
    // 'prev' pointer by reference.
    // Time Complexity: O(N)
    // Space Complexity: O(H)
    //=========================================================================
private:
    bool inOrderIsBST(TreeNode* node, TreeNode*& prev) {
        if (!node) {
            return true;
        }

        // 1. Traverse the left subtree.
        if (!inOrderIsBST(node->left, prev)) {
            return false;
        }

        // 2. Visit the current node. Check if it's greater than the previous.
        if (prev != nullptr && node->val <= prev->val) {
            std::cout << "In-order fails here: node " << node->val << " <= prev " << prev->val << std::endl;
            return false;
        }
        prev = node; // Update previous node to be the current one.

        // 3. Traverse the right subtree.
        return inOrderIsBST(node->right, prev);
    }

public:
    bool isBST_inorder(TreeNode* root) {
        TreeNode* prev = nullptr;
        return inOrderIsBST(root, prev);
    }

    // Recursively delete the tree to prevent memory leaks.
    void destroyTree(TreeNode* node) {
        if (!node) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
};

// Main function to test the solutions.
int main() {
    Solution sol;

    // Test Case 1: Should fail due to an invalid node (140).
    TreeNode* root1 = new TreeNode(100);
    root1->left = new TreeNode(50);
    root1->right = new TreeNode(150);
    root1->left->left = new TreeNode(30);
    root1->left->right = new TreeNode(60);
    root1->right->left = new TreeNode(111);
    root1->right->right = new TreeNode(170);
    root1->left->left->left = new TreeNode(10);
    root1->left->left->right = new TreeNode(140); // Invalid: > ancestors 50 and 100
    root1->left->right->left = new TreeNode(55);
    root1->left->right->right = new TreeNode(75);

    std::cout << "--- Test Case 1 (should fail) ---" << std::endl;
    std::cout << "isBST_bruteforce(): " << (sol.isBST_bruteforce(root1) ? "true" : "false") << std::endl;
    std::cout << "isBST_range():      " << (sol.isBST_range(root1) ? "true" : "false") << std::endl;
    std::cout << "isBST_inorder():    " << (sol.isBST_inorder(root1) ? "true" : "false") << std::endl;
    std::cout << std::endl;

    // Test Case 2: Should pass after fixing the tree.
    root1->left->left->right->val = 40; // Fix the invalid node.
    std::cout << "--- Test Case 2 (should pass) ---" << std::endl;
    std::cout << "isBST_bruteforce(): " << (sol.isBST_bruteforce(root1) ? "true" : "false") << std::endl;
    std::cout << "isBST_range():      " << (sol.isBST_range(root1) ? "true" : "false") << std::endl;
    std::cout << "isBST_inorder():    " << (sol.isBST_inorder(root1) ? "true" : "false") << std::endl;
    std::cout << std::endl;

    // Test Case 3: Should fail after introducing a new error.
    root1->left->right->left->val = 45; // Invalid: < parent (50)
    std::cout << "--- Test Case 3 (should fail) ---" << std::endl;
    std::cout << "isBST_bruteforce(): " << (sol.isBST_bruteforce(root1) ? "true" : "false") << std::endl;
    std::cout << "isBST_range():      " << (sol.isBST_range(root1) ? "true" : "false") << std::endl;
    std::cout << "isBST_inorder():    " << (sol.isBST_inorder(root1) ? "true" : "false") << std::endl;
    std::cout << std::endl;

    // Test Case 4: Empty Tree
    std::cout << "--- Test Case 4 (Empty Tree) ---" << std::endl;
    std::cout << "isBST_range(nullptr): " << (sol.isBST_range(nullptr) ? "true" : "false") << std::endl;
    std::cout << std::endl;

    // Test Case 5: Single Node
    TreeNode* root_single = new TreeNode(100);
    std::cout << "--- Test Case 5 (Single Node) ---" << std::endl;
    std::cout << "isBST_range():      " << (sol.isBST_range(root_single) ? "true" : "false") << std::endl;
    sol.destroyTree(root_single);
    std::cout << std::endl;

    // Test Case 6: Duplicate Values (should fail strictly increasing check)
    TreeNode* root_dup = new TreeNode(100);
    root_dup->left = new TreeNode(100); 
    std::cout << "--- Test Case 6 (Duplicates - should fail) ---" << std::endl;
    std::cout << "isBST_range():      " << (sol.isBST_range(root_dup) ? "true" : "false") << std::endl;
    sol.destroyTree(root_dup);
    std::cout << std::endl;

    // Test Case 7: INT_MAX Boundary (Verifies long long range logic)
    TreeNode* root_limit = new TreeNode(std::numeric_limits<int>::max());
    root_limit->left = new TreeNode(100);
    std::cout << "--- Test Case 7 (INT_MAX Boundary) ---" << std::endl;
    std::cout << "isBST_range():      " << (sol.isBST_range(root_limit) ? "true" : "false") << std::endl;
    sol.destroyTree(root_limit);
    std::cout << std::endl;

    // Memory for the tree is explicitly deleted.
    sol.destroyTree(root1);

    return 0;
}
