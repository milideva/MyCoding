#include <stdio.h>
#include <stdlib.h>

/*
  LeetCode 108: Convert Sorted Array to Binary Search Tree

  Problem Description:
  Given an integer array `nums` where the elements are sorted in 
  ascending order, convert it to a height-balanced BST.

  Algorithm: Recursive Midpoint Split
  1. Pick the middle element of the array as the root.
  2. Recursively build the left subtree from the left half of the array.
  3. Recursively build the right subtree from the right half of the array.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(log N) for recursion stack.
*/

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

Node* sortedArrayToBST(int nums[], int start, int end) {
    if (start > end) return NULL;

    int mid = start + (end - start) / 2;
    Node* root = createNode(nums[mid]);

    root->left = sortedArrayToBST(nums, start, mid - 1);
    root->right = sortedArrayToBST(nums, mid + 1, end);

    return root;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->val);
        inorder(root->right);
    }
}

void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    int nums[] = {-10, -3, 0, 5, 9};
    int n = 5;
    Node* root = sortedArrayToBST(nums, 0, n - 1);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    freeTree(root);
    return 0;
}
