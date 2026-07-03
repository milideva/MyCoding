#include <stdio.h>
#include <stdlib.h>

/*
  Problem: Height of a Binary Tree

  Problem Description:
  Given a binary tree, find its height. The height of a binary tree 
  is the number of nodes along the longest path from the root node 
  down to the farthest leaf node.

  Algorithm: Recursive Depth-First Search (DFS)
  The height of a tree is defined as 1 + max(height of left subtree, height 
  of right subtree).

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We must visit every node in the tree exactly once to determine 
    the overall height.
  - Space Complexity: O(H)
    Reason: The space used by the recursion stack is equal to the height 
    of the tree (H). 
    - Balanced Tree: O(log N)
    - Skewed Tree: O(N)

  Alternative Approaches:
  - Iterative BFS (Level Order): Use a queue to count the number of levels. 
    After processing all nodes of a level, increment the height.
    - Time: O(N)
    - Space: O(W) where W is the maximum width (can be O(N)).
    - Comparison: The recursive DFS is more concise and uses less space
      on average (stack vs queue).

  Brute Force comparison:
  - For height, there isn't really a "brute force" that is worse than O(N) 
    unless you perform redundant traversals (e.g., for each node, counting 
    all paths to leaves).
  - The O(N) DFS is the most direct and efficient method.
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

static void process_node (struct node *node) {
    printf("%d ", node->data);
}

void inOrder (struct node *node) {
    if (!node) return;
    inOrder(node->left);
    process_node(node);
    inOrder(node->right);
}

/* Height is the longest path from root to a leaf */
int height (struct node *node) {
    if (!node) return 0;
    int lHeight = height(node->left);
    int rHeight = height(node->right);
    int maxHeight = lHeight > rHeight ? lHeight : rHeight;
    return 1 + maxHeight;
}
 
int main() {
 
  /* Constructed binary tree is
            4
          /   \
        2      5
      /  \
    1     3
  */
  struct node *root = newNode(4);
  root->left        = newNode(2);
  root->right       = newNode(5);
  root->left->left  = newNode(1);
  root->left->right = newNode(3);
  
  printf("tree inOrder : ");
  inOrder(root);

  printf("\nHeight of the tree is : %d \n", height(root));

  getchar();
  return 0;
}
