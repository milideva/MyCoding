#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* 
  LeetCode 108: Convert Sorted Array to Binary Search Tree

  Algorithm: Recursive Midpoint Split
  To ensure the BST is height-balanced, the root must be the middle element 
  of the sorted array. We recursively apply this logic to the left and 
  right halves of the array.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We visit every element in the array exactly once to create its 
    corresponding node.
  - Space Complexity: O(log N)
    Reason: Since we always split at the midpoint, the tree is guaranteed 
    to be balanced, so the recursion stack depth is O(log N).

  Comparison:
  - Brute Force: Insert elements one by one from the array into a BST. 
    - If the array is sorted, this results in a skewed tree (linked list) 
      taking O(N^2) total time.
    - If you randomize the array first, it takes O(N log N).
  - Current Approach: O(N) is the optimal theoretical lower bound because 
    every node must be created.
*/

/* create a BST with min height, from a sorted array */


/*
  The left subtree of a node contains only nodes with keys less than the
  node's key.  The right subtree of a node contains only nodes with keys
  greater than the node's key.  The left and right subtree each must also be a
  binary search tree.  Each node can have up to two successor nodes.  There
  must be no duplicate nodes.  A unique path exists from the root to every
  other node.
*/
struct node_ {
    int data;
    struct node_ *left;
    struct node_ *right;
};

typedef struct node_ node;

node *create_node (int data) {
    node *node = calloc(1, sizeof *node);
    if (node) node->data = data;
    return node;
}

node *create_BST_from_array (int array[], int start, int end) {
    if (!array) return NULL;
    if (end < start) return NULL;

    int mid = (start+end)/2;
    node *n = create_node(array[mid]);
    if (!n) return n;

    n->left = create_BST_from_array(array, start, mid-1);
    n->right = create_BST_from_array(array, mid+1, end);
    
    printf("node:%d left:%d right:%d\n", n->data, 
           n->left ? n->left->data : 0, 
           n->right ? n->right->data : 0);
    return n;
}

void inorder (node *root)  { 
    if (root) { 
        inorder(root->left); 
        printf("%d ", root->data); 
        inorder(root->right); 
    } 
}

void print_inorder (node *n) {
    printf("print_inorder: ");
    inorder(n);
}


/*
(gdb) p *root
$1 = {data = 56, left = 0x601030, right = 0x601090}
(gdb) p *root->left
$2 = {data = -5, left = 0x601050, right = 0x601070}
(gdb) p *root->left->left
$3 = {data = -10, left = 0x0, right = 0x0}
(gdb) p *root->left->right
$4 = {data = 10, left = 0x0, right = 0x0}
(gdb) p *root->right
$5 = {data = 233, left = 0x6010b0, right = 0x6010d0}
(gdb) p *root->right->left
$6 = {data = 60, left = 0x0, right = 0x0}
(gdb) p *root->right->right
$7 = {data = 1000, left = 0x0, right = 0x6010f0}
(gdb) 
*/

int main (void) {
    int array[] = { 10, 5, 1, 56, 60, 233, 1000, 2333 };
    int end = sizeof array/ sizeof array[0];
    node *root = create_BST_from_array(array, 0, 
                                       end-1);
    print_inorder(root);

    return 0;
}
