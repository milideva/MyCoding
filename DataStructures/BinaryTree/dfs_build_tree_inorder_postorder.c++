/**
 * Problem: Construct Binary Tree from Inorder and Postorder Traversal
 * Given two integer arrays inorder and postorder, construct and return 
 * the binary tree.
 * 
 * Strategy: Recursive DFS with Hash Map
 * 1. Postorder: LEFT -> RIGHT -> ROOT. The last element is the root.
 * 2. Inorder: LEFT -> ROOT -> RIGHT. Root splits left and right subtrees.
 * 3. Use a hash map to quickly find the root's index in the inorder array.
 * 4. Process postorder from end to start (ROOT -> RIGHT -> LEFT).
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
    int postIdx;

    TreeNode* build(int start, int end, const vector<int>& postorder) {
        if (start > end) return nullptr;

        int val = postorder[postIdx--];
        TreeNode* root = new TreeNode(val);
        int mid = inorderMap[val];

        // Build right subtree first because we are moving backwards in postorder
        root->right = build(mid + 1, end, postorder);
        root->left = build(start, mid - 1, postorder);

        return root;
    }

public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        inorderMap.clear();
        for (int i = 0; i < (int)inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        postIdx = postorder.size() - 1;
        return build(0, inorder.size() - 1, postorder);
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
    vector<int> postorder = {9, 15, 7, 20, 3};

    Solution sol;
    TreeNode* root = sol.buildTree(inorder, postorder);

    cout << "Reconstructed Tree (In-order): ";
    printInOrder(root);
    cout << endl;

    return 0;
}
