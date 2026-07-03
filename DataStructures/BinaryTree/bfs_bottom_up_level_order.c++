#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

// g++ -std=c++2a bottom_up_level_order.c++ -g

/*
  LeetCode 107: Binary Tree Level Order Traversal II (Bottom-Up)

  Problem Description:
  Given the root of a binary tree, return the bottom-up level order 
  traversal of its nodes' values. (i.e., from left to right, level 
  by level from leaf to root).

  Algorithm: Breadth-First Search (BFS) + Result Reversal
  1. Perform a standard level-order traversal (BFS) using a queue.
  2. Store each level's nodes in a 2D vector.
  3. Reverse the 2D vector at the end.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: BFS visits each of the N nodes exactly once. Reversing the outer 
    vector (containing H levels) takes O(H) time, where H < N.
  - Space Complexity: O(N)
    Reason: We store all N nodes in the result vector. The queue also holds 
    up to O(W) nodes, where W is the maximum width.

  Alternative Approaches:
  - DFS: Use a recursive function passing the current depth. Use the depth 
    index to add nodes to the correct inner vector. Reverse at the end.
    - Time: O(N), Space: O(N + H).
  - Deque (Optimized Space): Instead of a vector and reversing, use a deque 
    and push each new level to the front (`push_front`). 
    - Note: In C++, `std::vector` + `std::reverse` is usually faster due to
      memory locality and contiguous storage compared to `std::deque`.

  Brute Force Approach:
  - 1. Calculate the height of the tree H.
  - 2. For each level i from H down to 1:
  -    Perform a DFS to find all nodes at depth i and add them to the result.
  - Time Complexity: O(H * N), which is O(N^2) in the worst case (skewed tree).
  - Space Complexity: O(N) to store the result.

  Comparison:
  - The BFS + Reverse approach is O(N) and is the most efficient way to 
    collect level nodes. The Brute Force approach is much slower because 
    it repeats the traversal for every single level.
*/

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
};

using namespace std;

void print_vec(const std::vector<int>& vec) {
  cout << "[ ";
  for (auto x: vec) {
    cout << ' ' << x;
  }
  cout << " ]" << endl;
}

void print_vec_vec (vector<vector<int>>& vec) {
  cout << "[ " << endl;
  for (auto x: vec) {
    print_vec(x);
    cout << ' ' << endl;
  }
  cout << " ]" << endl;
}

// Use BFS 
vector<vector<int>> levelOrderBottomBfs (TreeNode* root) {
  vector<vector<int>> answerQQ;                
  if (!root) return answerQQ;
  
  queue <TreeNode *> q;
  q.push(root); // put root in queue
  int level = 0;

  while (!q.empty()) {
    int sz = q.size();
    vector <int> levelVec;
    while (sz--) {
      TreeNode *n = q.front(); q.pop();
      if (n->left) 
        q.push(n->left);
      if (n->right)
        q.push(n->right);
      levelVec.push_back(n->val);
    }
    level++;
    answerQQ.push_back(levelVec);
  }
  reverse(answerQQ.begin(), answerQQ.end());
  return answerQQ;
}

int main () {
  TreeNode *root = new TreeNode;
  // [3,9,20,null,null,15,7]
  root->val = 3;
  
  root->left = new TreeNode;
  root->left->val = 9;
  
  
  root->right = new TreeNode;
  root->right->val = 20;
  
  root->right->left = new TreeNode;
  root->right->left->val = 15;
  
  root->right->right = new TreeNode;
  root->right->right->val = 7;
	
  vector<vector<int>> ans;
  ans = levelOrderBottomBfs(root);
  print_vec_vec(ans);
  
  return 0;
}
