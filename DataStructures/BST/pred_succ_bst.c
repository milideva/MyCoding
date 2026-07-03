#include <stdio.h>
#include <stdlib.h>

/*
  Problem: Predecessor and Successor in a BST

  Algorithm: Recursive BST Search
  1. If root is NULL, return.
  2. If key is found:
     - Predecessor is the max in left subtree.
     - Successor is the min in right subtree.
  3. If key is smaller than root:
     - Update successor to current root (potential successor).
     - Recurse left.
  4. If key is larger than root:
     - Update predecessor to current root (potential predecessor).
     - Recurse right.

  Complexity Analysis:
  - Time Complexity: O(H)
    Reason: We follow a single path from root to leaf to locate the key 
    and its neighbors. H is tree height.
  - Space Complexity: O(H)
    Reason: Recursion stack depth.

  Brute Force comparison:
  - Perform a full in-order traversal (O(N)), store values in an array, 
    and find the elements before and after the key. 
  - The O(H) BST search is much more efficient as it skips irrelevant 
    subtrees.
*/

struct node_ {
    int key;
    struct node_ *left;
    struct node_ *right;
};

typedef struct node_ node_t;

/*
   In-order predecessor and successor for a given key in BST.
   Pseudo code
   0. start from root, succ = pred = NULL
   1. terminate
        if (node == null) return

   2.   if (key == root->key) {
            succ is the min elem on right or one of the parents
            pred is max elem on left or one of the parents
            return;
        }
   3. if (key < root->key) succ = root;  recurse on root->left now
      if (key > root->key) pred = root;  recurse on root->right now
*/

void
BST_succ_pred (node_t *root, node_t **pred, node_t **succ, int key) {
    if (!root) 
        return;

    if (root->key == key) {
        if (root->right) {
            //succ is the min elem in right subtree
            *succ = root->right;
            while ((*succ)->left) {
                *succ = (*succ)->left;
            }
        }
        if (root->left) {
            // pred is max elem on left
            *pred = root->left;
            while ((*pred)->right) {
                *pred = (*pred)->right;
            }
        }
        return;
    }

    if (key < root->key) {
        *succ = root;
        BST_succ_pred(root->left, pred, succ, key);
    } else {
        *pred = root;
        BST_succ_pred(root->right, pred, succ, key);
    }

    return;
}

node_t *create_node (int key) {
    node_t *node = calloc(1, sizeof *node);
    if (node) node->key = key;
    printf("created node:%d\n", key);
    return node;
}

node_t *insert_node (node_t *root, int key) {
    if (root == NULL) {
        return create_node(key);
    }

    if (key < root->key) 
        root->left = insert_node(root->left, key);
    else 
        root->right = insert_node(root->right, key);

    return root;
}

static node_t *min_value_node (node_t* node)  { 
    node_t* current = node; 
  
    while (current && current->left != NULL) 
        current = current->left; 
  
    return current; 
} 

node_t* delete_node (node_t* root, int key)  { 

    if (root == NULL) return root; 
  
    // If the key to be deleted is smaller than the root's key, 
    // then it lies in left subtree 
    if (key < root->key)  {
        root->left = delete_node(root->left, key); 
        return root;
    }
    // If the key to be deleted is greater than the root's key, 
    // then it lies in right subtree 
    if (key > root->key) {
        root->right = delete_node(root->right, key); 
        return root;
    }

    // Found the node to be deleted

    // node with only one child or no child 
    if (root->left == NULL) { 
      node_t *temp = root->right; 
      free(root); 
      return temp; 
    } 
    if (root->right == NULL) { 
      node_t *temp = root->left; 
      free(root); 
      return temp; 
    }

    // node with two children.
    // Get the in-order successor (smallest in the right subtree)
    node_t *temp = min_value_node(root->right);
    // in-order predecessor (biggest in left subtree) will also do.

    // Copy the in-order successor's content to this node
    root->key = temp->key;

    // Delete the in-order successor
    root->right = delete_node(root->right, temp->key); 
    
    return root; 
} 

/* 
                    100
           50               150
       30    60         111   170
     10 40  55  75
*/


void test2 (void) {
    node_t *root = NULL;
    int key;

    key = 100;
    root = insert_node(root, key);
    printf("insert node: key %d , root %d \n", key, root->key);

    key = 500;
    node_t *node = insert_node(root, key);
    printf("insert node: key %d, root %d \n", key, node->key);

    key = 150;
    node = insert_node(root, key);
    printf("insert node: key %d, root %d \n", key, node->key);

    key = 300;
    node = insert_node(root, key);
    printf("insert node: key %d, root %d \n", key, node->key);

    key = 60;
    node = insert_node(root, key);
    printf("insert node: key %d, root %d \n", key, node->key);

}   

void test1 (void) {
    node_t *node = create_node(100);
    node->left = create_node(50);
    node->right = create_node(150);

    node->left->left = create_node(30);
    node->left->right = create_node(60);

    node->right->left = create_node(111);
    node->right->right = create_node(170);

    node->left->left->left =  create_node(10);
    node->left->left->right = create_node(40);

    node->left->right->left =  create_node(55);
    node->left->right->right = create_node(75);
    node_t *pred, *succ;
    int key = 75;
    pred = succ = NULL;

    BST_succ_pred(node, &pred, &succ, key);
    printf("pred of %d is %d\n", key, pred ? pred->key : 0);
    printf("succ of %d is %d\n\n", key, succ ? succ->key : 0);

    key = 40;
    pred = succ = NULL;
    BST_succ_pred(node, &pred, &succ, key);
    printf("pred of %d is %d\n", key, pred ? pred->key : 0);
    printf("succ of %d is %d\n\n", key, succ ? succ->key : 0);

    key = 170;
    pred = succ = NULL;
    BST_succ_pred(node, &pred, &succ, key);
    printf("pred of %d is %d\n", key, pred ? pred->key : 0);
    printf("succ of %d is %d\n\n", key, succ ? succ->key : 0);

    key = 100;
    pred = succ = NULL;
    BST_succ_pred(node, &pred, &succ, key);
    printf("pred of %d is %d\n", key, pred ? pred->key : 0);
    printf("succ of %d is %d\n\n", key, succ ? succ->key : 0);

}


int main () {
    test1();
    test2();
    return 0;
}
