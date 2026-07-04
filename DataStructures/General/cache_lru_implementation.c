/**
 * Problem: LRU Cache Implementation
 * Design and implement a data structure for Least Recently Used (LRU) cache. 
 * It should support the following operations: get and put.
 * 
 * Strategy: Doubly Linked List + Hash Map (simplified with O(N) search for this C version)
 * - Doubly Linked List: To maintain the order of elements (Most Recently Used at head, LRU at tail).
 * - Hash Map: To achieve O(1) lookup (For simplicity in this C version, we use O(N) traversal).
 * 
 * Time Complexity: 
 * - get: O(N) in this implementation (O(1) with real hash map)
 * - put: O(N) in this implementation (O(1) with real hash map)
 * Space Complexity: O(Capacity)
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int value;
    struct Node *prev, *next;
} Node;

typedef struct LRUCache {
    int capacity;
    int count;
    Node *head, *tail;
} LRUCache;

/**
 * Creates a new node.
 */
static Node* createNode(int key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

/**
 * Initializes the LRU Cache.
 */
LRUCache* createCache(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->count = 0;
    cache->head = cache->tail = NULL;
    return cache;
}

/**
 * Removes a node from the doubly linked list.
 */
static void removeNode(LRUCache* cache, Node* node) {
    if (node->prev) node->prev->next = node->next;
    else cache->head = node->next;

    if (node->next) node->next->prev = node->prev;
    else cache->tail = node->prev;
}

/**
 * Adds a node to the front (Most Recently Used).
 */
static void addToFront(LRUCache* cache, Node* node) {
    node->next = cache->head;
    node->prev = NULL;
    if (cache->head) cache->head->prev = node;
    cache->head = node;
    if (!cache->tail) cache->tail = node;
}

/**
 * Gets the value of the key if it exists in the cache, otherwise returns -1.
 */
int get(LRUCache* cache, int key) {
    Node* curr = cache->head;
    while (curr) {
        if (curr->key == key) {
            // Move to front (Most Recently Used)
            removeNode(cache, curr);
            addToFront(cache, curr);
            return curr->value;
        }
        curr = curr->next;
    }
    return -1;
}

/**
 * Adds a key-value pair to the cache. If the cache is full, removes the LRU item.
 */
void put(LRUCache* cache, int key, int value) {
    Node* curr = cache->head;
    while (curr) {
        if (curr->key == key) {
            // Key exists, update value and move to front
            curr->value = value;
            removeNode(cache, curr);
            addToFront(cache, curr);
            return;
        }
        curr = curr->next;
    }

    // Key doesn't exist
    Node* newNode = createNode(key, value);
    if (cache->count < cache->capacity) {
        addToFront(cache, newNode);
        cache->count++;
    } else {
        // Cache full, remove tail (LRU)
        Node* lru = cache->tail;
        removeNode(cache, lru);
        free(lru);
        addToFront(cache, newNode);
    }
}

/**
 * Prints the current state of the cache.
 */
void printCache(LRUCache* cache) {
    printf("Cache (MRU -> LRU): ");
    Node* curr = cache->head;
    while (curr) {
        printf("[%d: %d] ", curr->key, curr->value);
        curr = curr->next;
    }
    printf("\n");
}

/**
 * Frees the cache memory.
 */
void freeCache(LRUCache* cache) {
    Node* curr = cache->head;
    while (curr) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
    free(cache);
}

int main() {
    LRUCache* cache = createCache(3);

    printf("Put (1, 10), (2, 20), (3, 30)\n");
    put(cache, 1, 10);
    put(cache, 2, 20);
    put(cache, 3, 30);
    printCache(cache);

    printf("Get(1): %d\n", get(cache, 1));
    printCache(cache);

    printf("Put (4, 40) - should evict key 2\n");
    put(cache, 4, 40);
    printCache(cache);

    printf("Get(2): %d (should be -1)\n", get(cache, 2));

    printf("Put (5, 50) - should evict key 3\n");
    put(cache, 5, 50);
    printCache(cache);

    freeCache(cache);
    return 0;
}
