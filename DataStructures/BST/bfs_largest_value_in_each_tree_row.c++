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

    void printVector(const vector<int>& v) {
        cout << "[";
        for (size_t i = 0; i < v.size(); i++) {
            cout << v[i] << (i == v.size() - 1 ? "" : ", ");
        }
        cout << "]";
    }
};

int main() {
    Solution sol;

    // Test Case 1: Example tree [1,3,2,5,3,null,9]
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(3);
    root1->right = new TreeNode(2);
    root1->left->left = new TreeNode(5);
    root1->left->right = new TreeNode(3);
    root1->right->right = new TreeNode(9);
    cout << "Test 1: "; sol.printVector(sol.largestValues(root1)); cout << " (Expected: [1, 3, 9])" << endl;
    sol.destroyTree(root1);

    // Test Case 2: Negative values
    TreeNode* root2 = new TreeNode(-1);
    root2->left = new TreeNode(-3);
    root2->right = new TreeNode(-2);
    cout << "Test 2: "; sol.printVector(sol.largestValues(root2)); cout << " (Expected: [-1, -2])" << endl;
    sol.destroyTree(root2);

    // Test Case 3: Single Node
    TreeNode* root3 = new TreeNode(100);
    cout << "Test 3: "; sol.printVector(sol.largestValues(root3)); cout << " (Expected: [100])" << endl;
    sol.destroyTree(root3);

    return 0;
}
