#include <stdio.h>
#include <stdlib.h>

/*
  Problem: Double Tree (Duplicate nodes on left)

  Problem Description:
  For every node in the binary tree, create a duplicate node with 
  the same value and insert it as the left child of the original node, 
  pushing the original left child down to be the left child of the 
  newly created node.

  Algorithm: Post-order Traversal (Bottom-Up)
  We traverse to the leaves first, then create the duplicate node and insert
  it between the current node and its original left child.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We visit each node in the binary tree exactly once to perform the
    duplication.
  - Space Complexity: O(H)
    Reason: Recursion stack space is proportional to the height of the tree (H).
    Note: The total memory usage increases as we double the number of nodes, 
    but the execution overhead is O(H).

  Why Post-order?
  - Using Post-order (Left, Right, Root) ensures we process the children 
    before modifying the current node's pointers. This prevents us from 
    accidentally traversing into the newly created duplicate nodes (which 
    would cause an infinite loop in a Pre-order approach).

  Comparison:
  - Pre-order: If not careful, you will visit the new node, duplicate it,
    visit that new node, etc. You'd need to manually skip the added node.
  - Level-order (BFS): Possible, but requires O(N) extra space for the queue.

  Brute Force comparison:
  - A brute force way to "double" the tree would be to serialize the whole 
    tree into an array, double every element in the array, and then 
    reconstruct a brand new tree. 
  - Time: O(N), but involves significant overhead for allocation and 
    traversal. The in-place post-order traversal is much more efficient.
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

/*

the tree... 
    2 
   / \ 
  1   3

 is changed to double tree on left ... 
       2 
      / \ 
     2   3 
    /   / 
   1   3 
  / 
 1

*/

/* Use Post order notation. 
   Excellent for things like changing nodes or freeing them.
   */
void doubleTree (struct node * node) {
    if (!node) return;
    doubleTree(node->left);
    doubleTree(node->right);
    struct node *left = node->left;
    struct node *double_node = newNode(node->data);
    node->left = double_node;
    double_node->left = left;

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

  doubleTree(root);
 
  printf("\n Inorder traversal of the mirror tree is \n");
  inOrder(root);

  getchar();
  return 0;
}
