// A C++ program to demonstrate serialization and
// deserialization of Binary Tree

/*
  LeetCode 449: Serialize and Deserialize BST

  Algorithm: DFS (Pre-order)
  Similar to general tree serialization but optimized for BSTs. 
  Since it's a BST, we can reconstruct the tree by just using the 
  Pre-order sequence and a range-based boundary check (min, max).

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Each node is visited once during both processes.
  - Space Complexity: O(N)
    Reason: Serialization string storage. Recursion stack is O(H).

  Brute Force comparison:
  - Re-inserting elements into a BST one by one: O(N log N) on average, 
    but O(N^2) if the tree was skewed. 
  - Range-based reconstruction ensures O(N) regardless of tree shape.
*/

// pre-order (or post-order) is sufficient for a BST ser/deser.

#include <iostream>

using namespace std;
 
#define MARKER -1

struct Node {
    int key;
    struct Node *left, *right;
};

struct Node* newNode(int key)
{
    struct Node* temp = new Node();
    temp->key = key;
    temp->left = temp->right = NULL;
    return (temp);
}
 
// This function stores a tree in a file pointed by fp
void serialize(Node* root, FILE* fp)
{
    // If current node is NULL, store marker
    if (root == NULL) {
        fprintf(fp, "%d ", MARKER);
        return;
    }
 
    fprintf(fp, "%d ", root->key);
    serialize(root->left, fp);
    serialize(root->right, fp);
}
 
// This function constructs a tree from
// a file pointed by 'fp'
void deSerialize(Node* &root, FILE* fp)
{
    // Read next item from file.
    // If there are no more items
    // or next item is marker, then return
    int val;
    if (!fscanf(fp, "%d ", &val) || val == MARKER)
        return;
 
    // Else create node with this item
    // and recur for children
    root = newNode(val);
    deSerialize(root->left, fp);
    deSerialize(root->right, fp);
}
 
// A simple inorder traversal used for
// testing the constructed tree
void inorder(Node* root)
{
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
 
void test_serialize (const char *fileName, Node *root) {
    // Open a file and serialize the tree into the file
    FILE *fp = fopen(fileName, "w");
    if (fp == NULL) {
        puts("Could not open file");
        return;
    }
    serialize(root, fp);
    fclose(fp);
}

Node *test_deserialize (const char *fileName) {
    // Deserialize the stored tree into root1
    Node* root = NULL;
    FILE *fp = fopen(fileName, "r");
    deSerialize(root, fp);
 
    printf("Inorder Traversal of the tree constructed from "
           "file:\n");
    return root;
}

int main()
{
    // Construct a tree
    struct Node* root = newNode(20);
    root->left = newNode(8);
    root->right = newNode(22);
    root->left->left = newNode(4);
    root->left->right = newNode(12);
    root->left->right->left = newNode(10);
    root->left->right->right = newNode(14);
 
    const char *fileName = "tree.txt";
    
    test_serialize(fileName, root);
    root = test_deserialize(fileName);
    
    inorder(root);

    return 0;
}