#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
  Problem: Optimized Trie Implementation in C

  Description:
  A slightly more optimized version of a Trie node that uses a 
  single allocation for the node and its children pointers.

  Complexity Analysis:
  - Time Complexity: O(L) for insert and search.
  - Space Complexity: O(N * 26) where N is the total number of nodes.
*/

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    bool isEndOfWord;
    struct TrieNode* children[ALPHABET_SIZE];
} TrieNode;

TrieNode* createNode() {
    TrieNode* newNode = (TrieNode*)malloc(sizeof(TrieNode));
    newNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

void insert(TrieNode* root, const char* key) {
    TrieNode* curr = root;
    for (int i = 0; key[i] != '\0'; i++) {
        int index = key[i] - 'a';
        if (!curr->children[index]) {
            curr->children[index] = createNode();
        }
        curr = curr->children[index];
    }
    curr->isEndOfWord = true;
}

bool search(TrieNode* root, const char* key) {
    TrieNode* curr = root;
    for (int i = 0; key[i] != '\0'; i++) {
        int index = key[i] - 'a';
        if (!curr->children[index]) return false;
        curr = curr->children[index];
    }
    return curr != NULL && curr->isEndOfWord;
}

void freeTrie(TrieNode* node) {
    if (!node) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freeTrie(node->children[i]);
    }
    free(node);
}

int main() {
    TrieNode* root = createNode();
    char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};

    for (int i = 0; i < 8; i++) {
        insert(root, keys[i]);
    }

    printf("Search \"the\":   %s\n", search(root, "the") ? "Found" : "Not Found");
    printf("Search \"these\": %s\n", search(root, "these") ? "Found" : "Not Found");
    printf("Search \"their\": %s\n", search(root, "their") ? "Found" : "Not Found");
    printf("Search \"thaw\":  %s\n", search(root, "thaw") ? "Found" : "Not Found");

    freeTrie(root);
    return 0;
}
