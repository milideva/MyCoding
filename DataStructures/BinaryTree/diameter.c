#include <stdio.h>
#include <stdlib.h>

/*
  LeetCode 543: Diameter of Binary Tree

  Problem Description:
  Given the root of a binary tree, return the length of the diameter 
  of the tree. The diameter of a binary tree is the length of the 
  longest path between any two nodes in a tree. This path may or 
  may not pass through the root.

  The length of a path between two nodes is represented by the 
  number of edges between them.

  Current Approach: Recursive Top-Down
  - Logic: Diameter at a node is max(left_height + right_height, 
                                     left_diameter, 
                                     right_diameter).

  Complexity Analysis (Current Implementation):
  - Time Complexity: O(N^2) (Worst Case - Skewed Tree)
    Reason: For every node, we call `height()`, which is an O(N) operation.
    In a skewed tree, we do N calls * O(N) per call = O(N^2).
  - Space Complexity: O(H)
    Reason: Recursion stack depth is the height of the tree.

  Optimized Approach (Bottom-Up):
  - Logic: Compute height and diameter in a single traversal. Each recursive
    call returns the height, while updating a global/reference variable for
    the maximum diameter found so far.
  - Time Complexity: O(N) - visits each node once.
  - Space Complexity: O(H) - recursion stack.

  Brute Force comparison:
  - The O(N^2) approach is essentially a brute force method because it 
    redundantly calculates the height of subtrees for every single node in 
    the tree. By merging the height calculation into the diameter check 
    (Bottom-Up), we remove the O(N) overhead from each node visit.

  Comparison:
  - The current implementation is simple to understand but inefficient for
    large/skewed trees. The O(N) approach is industry standard for this problem.
*/

struct node {
    int data;
    struct node* left;
    struct node* right;
};

static int max (int a, int b) {
  return (a >= b)? a: b;
}  

// This is height counting up from the leaf
int height (struct node* node) {
   if (node == NULL)
       return 0;

   return 1 + max(height(node->left), height(node->right));
}
 
struct node* newNode (int data) {
    struct node* node = calloc(1, sizeof(*node));
    if (node) node->data = data;
    return node;
}

/* Function to get diameter of a binary tree. 
 * It's longest path between two leaves.
 * In some cases, it's possible that diameter does not go through ROOT.
 * Especially if the tree is one sided. Imagine only one node on right.
 * and arbitrarily complex structure on left.
*/
int diameter (struct node * tree)
{
   /* base case where tree is empty */
   if (tree == 0)
     return 0;
 
  /* get the height of left and right sub-trees */
  int lheight = height(tree->left);
  int rheight = height(tree->right);
 
  printf("height L:%d R:%d total:%d\n", 
         lheight, rheight, lheight + rheight +1);
  
  /* get the diameter of left and right sub-trees */
  int ldiameter = diameter(tree->left);
  int rdiameter = diameter(tree->right);
 
  printf("diameter L:%d R:%d\n", ldiameter, rdiameter);
  
  /* Return max of following three
   1) Diameter of left subtree
   2) Diameter of right subtree
   3) Height of left subtree + height of right subtree + 1 */
  return max(lheight + rheight, max(ldiameter, rdiameter));
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
 
  printf("Diameter of the given binary tree is %d\n", diameter(root));
 
  getchar();
  return 0;
}
