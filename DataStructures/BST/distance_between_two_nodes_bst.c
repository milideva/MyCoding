#include <stdio.h>
#include <stdlib.h>

/*
  Problem: Distance between two nodes in a BST

  Algorithm: LCA Property + Path Length
  1. Find the Lowest Common Ancestor (LCA) of the two nodes.
  2. In a BST, the LCA of n1 and n2 is the first node whose value is 
     between n1 and n2.
  3. Distance = distance(LCA to n1) + distance(LCA to n2).

  Complexity Analysis:
  - Time Complexity: O(H)
    Reason: Finding the LCA in a BST takes O(H). Finding the height from 
    LCA to each node also takes O(H). Total time is proportional to the 
    tree height.
  - Space Complexity: O(H)
    Reason: Recursive calls for LCA and height calculation.

  Comparison:
  - General Binary Tree: If it weren't a BST, finding LCA would take O(N). 
    The BST property allows us to skip entire subtrees, reducing time to O(H).
  - Brute Force: Use BFS/DFS to find both nodes and record their full paths 
    from the root, then find the first point of divergence. This is O(N) 
    time and space.
*/

struct node_ {
    int key;
    struct node_ *left;
    struct node_ *right;
};

typedef struct node_ node_t;

int height_from_node (node_t *root, node_t *me) {
    if (!root || !me || root == me) return 0;

    if (me->key < root->key) 
        return 1 + height_from_node(root->left, me);
    return 1 + height_from_node(root->right, me);
}
/*

         6
       /   \
     2      8
    / \    / \
   0   4  7   9
      / \
     3   5

*/

node_t *lowest_common_ancestor (node_t *root, node_t *n1, node_t *n2) {
    if (!root || !n1 || !n2) return NULL;
    if (n1->key < root->key && n2->key < root->key) 
        lowest_common_ancestor(root->left, n1, n2);
    if (n1->key > root->key && n2->key > root->key)
        lowest_common_ancestor(root->right, n1, n2);
   return root; // This is where one of the p or q is == root->val 
}

// input is sorted array
node_t *create_BST (int array[], int start, int end) {
    if (!array || start > end) return NULL;

    int mid = (start + end)/ 2;

    node_t *node = calloc(1, sizeof *node);
    if (!node) return NULL;

    node->key = array[mid];
    node->left = create_BST(array, start, mid-1);
    node->right = create_BST(array, mid+1, end);

    return node;
}

int distance (node_t *root, node_t *n1, node_t *n2) {
    if (!root || !n1 || !n2 || n1==n2) return 0;

    node_t *lca = lowest_common_ancestor(root, n1, n2);
    return height_from_node(lca, n1) + height_from_node(lca, n2);
}

node_t *find_node (node_t *root, int key) {
    if (!root) return NULL;
    if (root->key == key) return root;

    if (key < root->key) return find_node(root->left, key);
    return find_node(root->right, key);    
}

void pre_order (node_t *root) {
    if (!root) return;
    printf("%d ", root->key);
    pre_order(root->left);
    pre_order(root->right);
}

int main () {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};  
    int n = sizeof(arr) / sizeof(arr[0]);

    node_t *root = create_BST(arr, 0, n-1);
    printf("Preorder traversal of constructed BST:\n");
    pre_order(root);

    int key1 = 1;
    int key2 = 7;
    node_t *n1 = find_node(root, key1);
    node_t *n2 = find_node(root, key2);

    int d = distance(root, n1, n2);
    printf("\ndistance between %d and %d is %d \n", key1, key2, d);
    return 0;
}
