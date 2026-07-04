/**
 * Problem: Construct Binary Tree from Inorder and Preorder Traversal
 * Given two integer arrays preorder and inorder, construct and return 
 * the binary tree.
 * 
 * Strategy: Recursive DFS with Hash Map
 * 1. Preorder: ROOT -> LEFT -> RIGHT. The first element is the root.
 * 2. Inorder: LEFT -> ROOT -> RIGHT. Root splits left and right subtrees.
 * 3. Use a hash map to quickly find the root's index in the inorder array.
 * 4. Process preorder from start to end (ROOT -> LEFT -> RIGHT).
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N) - For hash map and recursion stack.
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    unordered_map<int, int> inorderMap;
    int preIdx;

    TreeNode* build(int start, int end, const vector<int>& preorder) {
        if (start > end) return nullptr;

        int val = preorder[preIdx++];
        TreeNode* root = new TreeNode(val);
        int mid = inorderMap[val];

        // Build left subtree first because we are moving forward in preorder
        root->left = build(start, mid - 1, preorder);
        root->right = build(mid + 1, end, preorder);

        return root;
    }

public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& preorder) {
        inorderMap.clear();
        for (int i = 0; i < (int)inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        preIdx = 0;
        return build(0, inorder.size() - 1, preorder);
    }
};

/**
 * Utility to print in-order traversal.
 */
void printInOrder(TreeNode* root) {
    if (!root) return;
    printInOrder(root->left);
    cout << root->val << " ";
    printInOrder(root->right);
}

int main() {
    vector<int> inorder = {9, 3, 15, 20, 7};
    vector<int> preorder = {3, 9, 20, 15, 7};

    Solution sol;
    TreeNode* root = sol.buildTree(inorder, preorder);

    cout << "Reconstructed Tree (In-order): ";
    printInOrder(root);
    cout << endl;

    return 0;
}
