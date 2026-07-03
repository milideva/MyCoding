/*
  LeetCode 998: Maximum Binary Tree II

  Problem: Insert a value into an existing Maximum Binary Tree. This value 
  was conceptually added to the end of the original array.

  Algorithm: Recursive DFS (Right-skewed Traversal)
  Since the value was appended to the array, it can only be:
  1. The new root (if it's greater than the current root).
  2. A node in the right subtree (since it appears after the root in the array).
  3. The right child of some node.

  Complexity Analysis:
  - Time Complexity: O(H) or O(N)
    Reason: We only traverse down the right spine of the tree. In the 
    worst case (skewed right), we visit O(N) nodes. On average (balanced), 
    it is O(log N).
  - Space Complexity: O(H)
    Reason: Recursion stack depth.

  Comparison:
  - Constructing the whole tree again (LC 654): O(N^2).
  - The current approach is optimal because it leverages the property that
    the new value was added to the *end* of the array, restricting its
    possible positions to the right-most path.

  Brute Force comparison:
  - A brute-force solution would involve converting the existing tree back 
    into an array, appending the new value, and calling the O(N^2) construction 
    function again. 
  - Time: O(N^2), Space: O(N).
  - The optimized insertion is O(H), requiring no extra array storage.
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/*

998. Maximum Binary Tree II

A maximum tree is a tree where every node has a value greater than any other value in its subtree.

Insert a value in a maximum binary tree

You are given an integer array nums with no duplicates. 
A maximum binary tree can be built recursively from nums using the following algorithm:

Create a root node whose value is the maximum value in nums.
Recursively build the left subtree on the subarray prefix to the left of the maximum value.
Recursively build the right subtree on the subarray suffix to the right of the maximum value.
Return the maximum binary tree built from nums.

Input: nums = [3,2,1,6,0,5]
Output: [6,3,5,null,2,0,null,null,1]
Explanation: The recursive calls are as follow:
- The largest value in [3,2,1,6,0,5] is 6. Left prefix is [3,2,1] and right suffix is [0,5].
    - The largest value in [3,2,1] is 3. Left prefix is [] and right suffix is [2,1].
        - Empty array, so no child.
        - The largest value in [2,1] is 2. Left prefix is [] and right suffix is [1].
            - Empty array, so no child.
            - Only one element, so child is a node with value 1.
    - The largest value in [0,5] is 5. Left prefix is [0] and right suffix is [].
        - Only one element, so child is a node with value 0.
        - Empty array, so no child.
    
*/
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution {
    
    TreeNode* recurseMaximumBinaryTree (vector<int>& nums, int start, int end) {
        if (start > end) 
            return nullptr;
        int max = nums[start];
        int max_index = start;
        for (int i = start; i <= end; i++) {
            if (nums[i] > max) {
                max_index= i;
                max = nums[i];
            }
        }
        TreeNode *root = new TreeNode(max);
        root->left = recurseMaximumBinaryTree(nums, start, max_index - 1);
        root->right = recurseMaximumBinaryTree(nums, max_index + 1, end);
        return root;
    }

public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return recurseMaximumBinaryTree(nums, 0, nums.size() - 1);
    }
    
    TreeNode* insertIntoMaxTree (TreeNode* root, int val) {
        if (!root)
            return new TreeNode(val);
        if (val > root->val)
            return new TreeNode(val, root, nullptr);

        root->right = insertIntoMaxTree(root->right, val);
        return root;
    }
};

void inOrderPrint (TreeNode *root) {
    if (!root) return;
    inOrderPrint(root->left);
    cout << root->val << " " << endl;
    inOrderPrint(root->right);
}

void test(void) {
    class Solution sol;
    vector <int> nums{3,2,1,6,0,5};
    TreeNode *root = sol.constructMaximumBinaryTree(nums);
    inOrderPrint(root);
    root = sol.insertIntoMaxTree(root, 7);
    inOrderPrint(root);
    root = sol.insertIntoMaxTree(root, 4);
}

int main () {
    test(); 
    return 0;
}