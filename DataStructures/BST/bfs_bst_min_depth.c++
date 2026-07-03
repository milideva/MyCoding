/*
LeetCode 111: Minimum Depth of Binary Tree

Given a binary tree, find its minimum depth.
The minimum depth is the number of nodes along the shortest path from the 
root node down to the nearest leaf node.
Note: A leaf is a node with no children.

Example:
    3
   / \
  9  20
    /  \
   15   7
Input: root = [3,9,20,null,null,15,7]
Output: 2
*/

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        
        queue<TreeNode*> q;
        q.push(root);
        int depth = 1;
        
        while (!q.empty()) {
            int levelSize = q.size();
            
            // Process all nodes at the current depth
            for (int i = 0; i < levelSize; i++) {
                TreeNode* curr = q.front();
                q.pop();
                
                // BFS Advantage: The first leaf node we encounter is guaranteed 
                // to be at the minimum depth.
                if (!curr->left && !curr->right) {
                    return depth;
                }
                
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            depth++;
        }
        return depth;
    }
    
    void destroyTree(TreeNode* root) {
        if (!root) return;
        destroyTree(root->left);
        destroyTree(root->right);
        delete root;
    }
};

int main() {
    Solution sol;

    // Test Case 1: Example tree [3,9,20,null,null,15,7]
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);
    cout << "Test 1 (Standard): " << sol.minDepth(root1) << " (Expected: 2)" << endl;
    sol.destroyTree(root1);

    // Test Case 2: Skewed Tree (Right) [2,null,3,null,4,null,5,null,6]
    TreeNode* root2 = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->right->right = new TreeNode(4);
    root2->right->right->right = new TreeNode(5);
    root2->right->right->right->right = new TreeNode(6);
    cout << "Test 2 (Skewed Right): " << sol.minDepth(root2) << " (Expected: 5)" << endl;
    sol.destroyTree(root2);

    // Test Case 3: Empty Tree
    cout << "Test 3 (Empty): " << sol.minDepth(nullptr) << " (Expected: 0)" << endl;

    // Test Case 4: Single Node
    TreeNode* root4 = new TreeNode(1);
    cout << "Test 4 (Single Node): " << sol.minDepth(root4) << " (Expected: 1)" << endl;
    sol.destroyTree(root4);

    return 0;
}
