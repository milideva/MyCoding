#include <stdio.h>
#include <stdlib.h>

/*
  Problem: Distance between two nodes in a BST

  Problem Description:
  Given a list of unique integers nums, construct a BST from it and 
  find the distance between two nodes node1 and node2. Distance is 
  the number of edges between two nodes.

  Algorithm: LCA Property + Path Length
  1. Find the Lowest Common Ancestor (LCA) of the two nodes.
  2. Distance = distance(LCA to n1) + distance(LCA to n2).

  Complexity Analysis:
  - Time Complexity: O(H)
  - Space Complexity: O(H).
*/

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

Node* createNode(int key) {
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    newNode->key = key;
    return newNode;
}

Node* insert(Node* root, int key) {
    if (!root) return createNode(key);
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    return root;
}

Node* findLCA(Node* root, int n1, int n2) {
    if (!root) return NULL;
    if (n1 < root->key && n2 < root->key) return findLCA(root->left, n1, n2);
    if (n1 > root->key && n2 > root->key) return findLCA(root->right, n1, n2);
    return root;
}

int getPathLength(Node* root, int key) {
    if (!root || root->key == key) return 0;
    if (key < root->key) return 1 + getPathLength(root->left, key);
    return 1 + getPathLength(root->right, key);
}

int findDistance(Node* root, int n1, int n2) {
    Node* lca = findLCA(root, n1, n2);
    if (!lca) return -1;
    return getPathLength(lca, n1) + getPathLength(lca, n2);
}

void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    Node* root = NULL;
    int keys[] = {20, 10, 30, 5, 15, 25, 35};
    for (int i = 0; i < 7; i++) root = insert(root, keys[i]);

    printf("Distance(5, 35): %d (Expected: 4)\n", findDistance(root, 5, 35));
    printf("Distance(10, 15): %d (Expected: 1)\n", findDistance(root, 10, 15));
    printf("Distance(20, 20): %d (Expected: 0)\n", findDistance(root, 20, 20));

    freeTree(root);
    return 0;
}
