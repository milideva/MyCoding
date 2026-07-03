/*
  LeetCode 563: Binary Tree Tilt

  Problem Description:
  Given the root of a binary tree, return the sum of every tree node's 
  tilt.

  The tilt of a tree node is the absolute difference between the sum 
  of all left subtree node values and the sum of all right subtree 
  node values. If a node does not have a left child, then the sum 
  of the left subtree node values is 0. The rule is similar if the 
  node does not have a right child.

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



