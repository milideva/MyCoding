#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/*
  Problem: BST Serialization and Deserialization

  Algorithm: Pre-order DFS
  For a general tree, we need two traversals or null markers to rebuild it. 
  For a BST, a single Pre-order or Post-order traversal is sufficient to 
  reconstruct the exact structure because the BST property implicitly 
  defines the parent-child boundaries. (Note: The implementation below 
  uses markers for simplicity).

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We visit each node once during serialization and once 
    during deserialization.
  - Space Complexity: O(N)
    Reason: Storage of the serialized string/file.

  Brute Force comparison:
  - Storing as a full 2D matrix (adjacency matrix) would take O(N^2) space. 
  - The Pre-order traversal is the most space-efficient standard approach.
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

// Helper function to create a BST
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

static void inorder (node *root)  { 
    if (root) { 
        inorder(root->left); 
        printf("%d \n", root->data); 
        inorder(root->right); 
    } 
}

#define MARKER -1
// pre-order with marker or post-order with marker is sufficient for a BST
// MARKERS for non-existing node when the tree is not full
void serialize (node *root, FILE *fp) {
    if (root == NULL) {
        fprintf(fp, "%d ", MARKER);
        return;
    }

    fprintf(fp, "%d ",root->data);
    serialize(root->left, fp);
    serialize(root->right, fp);
}

void deserialize (node **n, FILE *fp) {
    int data = MARKER;
    if (!n) return;
    int ret = fscanf(fp, "%d", &data);

    if (!ret || data == MARKER) {
        return;
    }
    *n = create_node(data);
    deserialize(&((*n)->left), fp);
    deserialize(&((*n)->right), fp);
}

void print_inorder (node *n) {
    printf("print_inorder: ");
    inorder(n);
}

void test_serdeser (node *root) {
    FILE *fp = fopen("tree.txt", "w"); 
    serialize(root, fp);
    fclose(fp); 

    node *read = NULL;
    fp = fopen("tree.txt", "r");
    deserialize(&read, fp);
    fclose(fp);

    printf("\nInorder Traversal of the tree constructed from file:\n"); 
    inorder(read, 0, 3); 
    printf("\n");
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
    int array[] = { -10, 5, 10, 56, 60, 100, 233, 300, 500, 600, 700, 800, 900, 1000, 2333 };
    int end = sizeof array/ sizeof array[0];
    node *root = create_BST_from_array(array, 0, 
                                       end-1);
    print_inorder(root);

    test_serdeser(root);
    return 0;
}
