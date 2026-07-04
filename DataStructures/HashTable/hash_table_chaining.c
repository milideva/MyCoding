#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
  Problem: Hash Table with Chaining (Singly Linked List)

  Problem Description:
  Implement a basic hash table that stores string keys and associated 
  values. Handle collisions using chaining (linked list at each bucket).

  Algorithm:
  1. Use an array of pointers to `Node` structures.
  2. Hash Function: A simple sum of ASCII values or DJB2.
  3. Insert:
     - Hash the key to find the bucket.
     - Add new node at the head of the linked list in that bucket.
  4. Lookup:
     - Hash the key.
     - Traverse the linked list in that bucket to find the key.

  Complexity Analysis:
  - Time Complexity:
    - Average: O(1) for Insert and Lookup.
    - Worst: O(N) if all keys hash to the same bucket.
  - Space Complexity: O(N + Buckets).
*/

#define BUCKETS 10

typedef struct Node {
    char* key;
    int value;
    struct Node* next;
} Node;

unsigned int hash(const char* key) {
    unsigned int h = 0;
    while (*key) h = (h << 5) + *key++;
    return h % BUCKETS;
}

Node* createNode(const char* key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void insert(Node* table[], const char* key, int value) {
    unsigned int idx = hash(key);
    Node* newNode = createNode(key, value);
    newNode->next = table[idx];
    table[idx] = newNode;
}

int lookup(Node* table[], const char* key) {
    unsigned int idx = hash(key);
    Node* curr = table[idx];
    while (curr) {
        if (strcmp(curr->key, key) == 0) return curr->value;
        curr = curr->next;
    }
    return -1; // Not found
}

void freeTable(Node* table[]) {
    for (int i = 0; i < BUCKETS; i++) {
        Node* curr = table[i];
        while (curr) {
            Node* next = curr->next;
            free(curr->key);
            free(curr);
            curr = next;
        }
    }
}

int main() {
    Node* table[BUCKETS] = {NULL};

    insert(table, "apple", 10);
    insert(table, "banana", 20);
    insert(table, "cherry", 30);

    printf("Lookup apple: %d\n", lookup(table, "apple"));
    printf("Lookup banana: %d\n", lookup(table, "banana"));
    printf("Lookup cherry: %d\n", lookup(table, "cherry"));
    printf("Lookup mango: %d\n", lookup(table, "mango"));

    freeTable(table);
    return 0;
}
