/**
 * Problem: Find Duplicate Subtrees
 * Given the root of a binary tree, return all duplicate subtrees.
 * 
 * Strategy: DFS + Serialization + Hash Map
 * 1. For each node, serialize its subtree (LeftChild, RootVal, RightChild).
 * 2. Store the serialization string in a hash map and count its frequency.
 * 3. If frequency becomes 2, add the root node of this subtree to the result.
 * 
 * Time Complexity: O(N^2) in worst case due to string concatenation.
 * Space Complexity: O(N^2) to store all serialization strings.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    unordered_map<string, int> counts;
    vector<TreeNode*> result;

    /**
     * Serializes a subtree into a unique string.
     */
    string serialize(TreeNode* node) {
        if (!node) return "#";

        string s = "(" + serialize(node->left) + to_string(node->val) + serialize(node->right) + ")";
        
        counts[s]++;
        if (counts[s] == 2) {
            result.push_back(node);
        }
        return s;
    }

public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        counts.clear();
        result.clear();
        serialize(root);
        return result;
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
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->right->left = new TreeNode(2);
    root->right->right = new TreeNode(4);
    root->right->left->left = new TreeNode(4);

    Solution sol;
    vector<TreeNode*> duplicates = sol.findDuplicateSubtrees(root);

    cout << "Duplicate subtrees (In-order):" << endl;
    for (TreeNode* n : duplicates) {
        printInOrder(n);
        cout << endl;
    }

    return 0;
}
