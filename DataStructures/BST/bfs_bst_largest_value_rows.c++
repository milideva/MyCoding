/*
LeetCode 515: Find Largest Value in Each Tree Row

Given the root of a binary tree, return an array of the largest value in each row of the tree (0-indexed).

Example:
          1
         / \
        3   2
       / \   \
      5   3   9

Input: root = [1,3,2,5,3,null,9]
Output: [1,3,9]
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
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
    vector<int> largestValues(TreeNode* root) {
        if (!root) return {};
        
        vector<int> result;
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            int maxVal = numeric_limits<int>::min();
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* curr = q.front();
                q.pop();
                
                maxVal = max(maxVal, curr->val);
                
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            result.push_back(maxVal);
        }
        return result;
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

    // Constructing the example tree: [1,3,2,5,3,null,9]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(9);

    vector<int> res = sol.largestValues(root);
    
    cout << "Largest values per row: [";
    for (size_t i = 0; i < res.size(); i++) {
        cout << res[i] << (i == res.size() - 1 ? "" : ", ");
    }
    cout << "] (Expected: [1, 3, 9])" << endl;

    sol.destroyTree(root);
    return 0;
}
