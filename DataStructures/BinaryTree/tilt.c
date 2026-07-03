/*
Given a binary tree, return the tilt of the whole tree.

The tilt of a tree node is defined as the absolute difference between the sum
of all left subtree node values and the sum of all right subtree node values.
Null node has tilt 0.

The tilt of the whole tree is defined as the sum of all nodes' tilt.

Example:
Input: 
         1
       /   \
      2     3
Output: 1
Explanation: 
Tilt of node 2 : 0
Tilt of node 3 : 0
Tilt of node 1 : |2-3| = 1
Tilt of binary tree : 0 + 0 + 1 = 1
*/

/*
  LeetCode 563: Binary Tree Tilt

  Problem: Return the sum of all nodes' tilt. Tilt of a node is the 
  absolute difference between the sum of its left and right subtrees.

  Algorithm: Post-order DFS
  We traverse bottom-up. Each recursive call returns the total sum of the 
  subtree rooted at that node, while simultaneously updating a global 
  `tilt` variable with the tilt calculated at that node.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We visit each node once and perform constant-time work 
    (subtraction and addition).
  - Space Complexity: O(H)
    Reason: Recursion stack depth.

  Comparison:
  - Brute Force: For every node, call a separate `sum()` function for left 
    and right subtrees. This would take O(N^2).
  - The current approach is optimal as it calculates both the tilt and 
    the subtree sum in a single pass.
*/

int findSum (struct TreeNode *root, int *tilt) {
    if (!root) return 0;
    int sumLeft = findSum(root->left, tilt);
    int sumRight = findSum(root->right, tilt);
    *tilt += (sumLeft > sumRight) ? sumLeft-sumRight : sumRight-sumLeft;
    return sumLeft + sumRight + root->val;
    
}

int findTilt (struct TreeNode* root){
    if (!root) return 0;
    int tilt = 0;
    
    findSum(root, &tilt);

    return tilt;
}



