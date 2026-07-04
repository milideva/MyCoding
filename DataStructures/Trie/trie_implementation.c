#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
  Problem: Basic Trie (Prefix Tree) Implementation in C

  Problem Description:
  Implement a Trie data structure that supports:
  - `insert(word)`: Adds a word to the Trie.
  - `countWords(word)`: Returns the number of times a word exists.
  - `countPrefixes(prefix)`: Returns the number of words starting 
    with the given prefix.

  Algorithm: Array-based Nodes
  1. Each node contains:
     - `wordCount`: Number of words ending at this node.
     - `prefixCount`: Number of words passing through this node.
     - `children[26]`: Pointers to children for 'a' to 'z'.
  2. Initially, the Trie root is empty.

  Complexity Analysis:
  - Insert: O(L) where L is the word length.
  - Search/Count: O(L).
  - Space Complexity: O(Total characters * 26 * sizeof(Node*)).
*/

typedef struct Node {
    int wordCount;
    int prefixCount;
    struct Node* children[26];
} Node;

Node* createNode() {
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    return newNode;
}

void insert(Node* root, const char* word) {
    Node* curr = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int idx = word[i] - 'a';
        if (!curr->children[idx]) {
            curr->children[idx] = createNode();
        }
        curr = curr->children[idx];
        curr->prefixCount++;
    }
    curr->wordCount++;
}

int countWords(Node* root, const char* word) {
    Node* curr = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int idx = word[i] - 'a';
        if (!curr->children[idx]) return 0;
        curr = curr->children[idx];
    }
    return curr->wordCount;
}

int countPrefixes(Node* root, const char* prefix) {
    Node* curr = root;
    for (int i = 0; prefix[i] != '\0'; i++) {
        int idx = prefix[i] - 'a';
        if (!curr->children[idx]) return 0;
        curr = curr->children[idx];
    }
    return curr->prefixCount;
}

void freeTrie(Node* node) {
    if (!node) return;
    for (int i = 0; i < 26; i++) {
        freeTrie(node->children[i]);
    }
    free(node);
}

int main() {
    Node* root = createNode();
    
    insert(root, "apple");
    insert(root, "apple");
    insert(root, "app");
    
    printf("Count words \"apple\": %d (Expected: 2)\n", countWords(root, "apple"));
    printf("Count words \"app\":   %d (Expected: 1)\n", countWords(root, "app"));
    printf("Count prefix \"ap\":   %d (Expected: 3)\n", countPrefixes(root, "ap"));
    printf("Count prefix \"bat\":  %d (Expected: 0)\n", countPrefixes(root, "bat"));

    freeTrie(root);
    return 0;
}
