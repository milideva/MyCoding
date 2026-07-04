#include <stdio.h>
#include <stdlib.h>

/*
  Problem: Serialize and Deserialize BST (C version)

  Algorithm: Pre-order Traversal
  1. Serialization: Store nodes in pre-order. Use a marker (e.g., -1) 
     for NULL pointers.
  2. Deserialization: Read tokens. If marker, return NULL. Otherwise, 
     create node and recurse for left and right.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(N).
*/

#define MARKER -1

typedef struct Node {
    int val;
    struct Node *left, *right;
} Node;

Node* createNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void serialize(Node* root, FILE* fp) {
    if (!root) {
        fprintf(fp, "%d ", MARKER);
        return;
    }
    fprintf(fp, "%d ", root->val);
    serialize(root->left, fp);
    serialize(root->right, fp);
}

void deserialize(Node** root, FILE* fp) {
    int val;
    if (!fscanf(fp, "%d ", &val) || val == MARKER) return;

    *root = createNode(val);
    deserialize(&((*root)->left), fp);
    deserialize(&((*root)->right), fp);
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->val);
        inorder(root->right);
    }
}

int main() {
    Node* root = createNode(20);
    root->left = createNode(8);
    root->right = createNode(22);
    root->left->left = createNode(4);
    root->left->right = createNode(12);

    FILE* fp = fopen("tree.txt", "w");
    serialize(root, fp);
    fclose(fp);

    Node* newRoot = NULL;
    fp = fopen("tree.txt", "r");
    deserialize(&newRoot, fp);
    fclose(fp);

    printf("Inorder of Deserialized: ");
    inorder(newRoot);
    printf("\n");

    return 0;
}
