#include <stdio.h>
#include <stdlib.h>

/*
  Problem: Size of a Binary Tree (Total number of nodes)

  Algorithm: Recursive DFS
  The size of a tree is 1 (for the root) + size(left) + size(right).

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We must visit every node exactly once to count it.
  - Space Complexity: O(H)
    Reason: Recursion stack depth is proportional to the tree height (H).

  Alternative Approaches:
  - Iterative BFS (Level Order): Use a queue and a counter.
    - Time: O(N), Space: O(W).
  
  Comparison:
  - Recursive DFS is the most concise solution. BFS is only necessary
    for extremely large trees where stack overflow is a risk.

  Brute Force comparison:
  - You could traverse the tree and push every node's value into a list/vector, 
    and then return the size of that list. 
  - Time: O(N), Space: O(N).
  - The direct counter in DFS/BFS is better as it only requires O(H) or O(W) 
    extra space.
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

int size (struct node *node) {
    if (!node) return 0;
    return 1 + size(node->left) +  size(node->right);
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
  
  printf("Size of the tree is : %d \n", size(root));

  getchar();
  return 0;
}
