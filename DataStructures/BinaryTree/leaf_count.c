#include <stdio.h>
#include <stdlib.h>

/*
  Problem: Count Leaf Nodes in a Binary Tree

  Algorithm: Recursive DFS
  A node is a leaf if both its left and right children are NULL.
  Total leaves = leafcount(left) + leafcount(right).

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We must visit every node in the tree to determine if it is a leaf.
  - Space Complexity: O(H)
    Reason: Recursion stack depth depends on the height of the tree (H).

  Alternative Approaches:
  - Iterative BFS: Use a queue. If a dequeued node has no children, 
    increment the counter.
    - Time: O(N)
    - Space: O(W) where W is the max width.
  
  Comparison:
  - DFS is simpler to implement. BFS is useful for extremely deep trees
    to avoid stack overflow.

  Brute Force comparison:
  - You could traverse every path from the root to every possible termination 
    point and count the ones that end at a node with no children.
  - This is redundant and would take O(N) anyway. The O(N) DFS/BFS is 
    the standard.
*/

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct node* newNode (int data) {
    struct node* node = calloc(1, sizeof(*node));
    if (node) node->data = data;
    return node;
}

int leafcount (struct node * node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return (leafcount(node->left) + leafcount(node->right));
}
 
int main() {
 
  /* Constructed binary tree is
            1
          /   \
        2      3
      /  \
    4     5
  */
  struct node *root = newNode(1);
  root->left        = newNode(2);
  root->right       = newNode(3);
  root->left->left  = newNode(4);
  root->left->right = newNode(5);
 
  printf("Leafcount of the given binary tree is %d\n", leafcount(root));
 
  getchar();
  return 0;
}
