#include <stdio.h>
#include <stdlib.h>

/*
  Problem: Mirror (Invert) a Binary Tree

  Problem Description:
  Given a binary tree, convert it into its mirror image. In a mirror 
  image, the left and right children of all non-leaf nodes are 
  interchanged.

  Algorithm: Post-order DFS
  We recursively traverse to the bottom of the tree. At each node, we swap 
  the left and right pointers.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We visit every node in the tree exactly once to perform the swap.
  - Space Complexity: O(H)
    Reason: Recursion stack space is proportional to the tree height (H).

  Alternative Approaches:
  - BFS (Level Order): Use a queue. For each node, swap children and 
    enqueue. 
    - Time: O(N), Space: O(W).
  - Iterative DFS: Use a stack.
  
  Comparison:
  - The recursive approach is the most readable and standard way to mirror
    a tree. BFS is preferred if stack depth is a concern.

  Brute Force comparison:
  - Creating a brand new tree where you manually assign children in 
    reverse order is the brute force way. 
  - Time: O(N), Space: O(N) for the new nodes.
  - The in-place swap approach is superior as it uses O(1) extra space 
    beyond the recursion stack.
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

void inOrder (struct node *node) {
    if (!node) return;
    inOrder(node->left);
    printf("%d ", node->data);
    inOrder(node->right);
}

/* Use Post order notation. 
   Excellent for things like changing nodes or freeing them.
   */
void mirror (struct node * node) {
    if (!node) return;
    mirror(node->left);
    mirror(node->right);
    // now swap left and right
    struct node *temp = node->left;
    node->left = node->right;
    node->right =  temp;
    return;
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
 

  printf("\n Inorder traversal of the constructed tree is \n");
  inOrder(root);

  mirror(root);
 
  printf("\n Inorder traversal of the mirror tree is \n");
  inOrder(root);

  getchar();
  return 0;
}
