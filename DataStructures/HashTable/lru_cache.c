#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
  Problem: Least Recently Used (LRU) Cache

  Problem Description:
  Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

  Implement the LRUCache:
  - LRUCache* createLRUCache(int capacity) Initialize the LRU cache with positive size capacity.
  - int get(LRUCache* cache, int key) Return the value of the key if the key exists, otherwise return -1.
  - void put(LRUCache* cache, int key, int value) Update the value of the key if the key exists.
    Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity,
    evict the least recently used key.

  Algorithm:
  - We use a Doubly Linked List to keep track of the access order (MRU at front, LRU at tail).
  - We use a Hash Map (using chaining for collisions) to achieve O(1) key-to-node lookup.
  - To minimize dynamic allocations, each node in the doubly linked list also contains the collision
    chaining pointer for the hash map bucket.

  Complexity Analysis:
  - Time Complexity: O(1) for both get and put operations on average.
  - Space Complexity: O(Capacity) to store the capacity-sized cache.
*/

typedef enum {
    NotFound,
    Success
} LruCacheReturnCodes;

typedef struct LRUNode {
    int key;
    int value;
    struct LRUNode* prev;       // Doubly linked list previous node
    struct LRUNode* next;       // Doubly linked list next node
    struct LRUNode* hash_next;  // Hash bucket collision chaining
} LRUNode;

typedef struct LRUCache {
    int capacity;
    int size;
    int num_buckets;
    LRUNode** buckets;
    LRUNode* head;              // Dummy head node of the doubly linked list (MRU)
    LRUNode* tail;              // Dummy tail node of the doubly linked list (LRU)
} LRUCache;

// Simple hash function for integer keys
unsigned int hash(int key, int num_buckets) {
    unsigned int h = (unsigned int)key;
    return h % num_buckets;
}

// Locate node in the hash map
LRUNode* find_node(LRUCache* cache, int key) {
    unsigned int bucket = hash(key, cache->num_buckets);
    LRUNode* curr = cache->buckets[bucket];
    while (curr) {
        if (curr->key == key) {
            return curr;
        }
        curr = curr->hash_next;
    }
    return NULL;
}

// Move an existing node to the front of the list (making it Most Recently Used)
void move_to_front(LRUCache* cache, LRUNode* node) {
    // 1. Unlink node from its current position
    node->prev->next = node->next;
    node->next->prev = node->prev;

    // 2. Insert node at the front (immediately after dummy head)
    node->next = cache->head->next;
    node->prev = cache->head;
    cache->head->next->prev = node;
    cache->head->next = node;
}

// Initialize the LRU cache with the specified capacity
LRUCache* createLRUCache(int capacity) {
    if (capacity <= 0) {
        capacity = 1; // Fallback to minimum positive capacity
    }
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->num_buckets = capacity * 2;
    cache->buckets = (LRUNode**)calloc(cache->num_buckets, sizeof(LRUNode*));

    // Allocate dummy head and tail nodes
    cache->head = (LRUNode*)malloc(sizeof(LRUNode));
    cache->tail = (LRUNode*)malloc(sizeof(LRUNode));

    cache->head->key = -1;
    cache->head->value = -1;
    cache->head->prev = NULL;
    cache->head->next = cache->tail;
    cache->head->hash_next = NULL;

    cache->tail->key = -1;
    cache->tail->value = -1;
    cache->tail->prev = cache->head;
    cache->tail->next = NULL;
    cache->tail->hash_next = NULL;

    return cache;
}

// Get the value of the key (API 1)
int get(LRUCache* cache, int key) {
    LRUNode* node = find_node(cache, key);
    if (!node) {
        return -1;
    }
    move_to_front(cache, node);
    return node->value;
}

// Get the value of the key (API 2 style)
LruCacheReturnCodes get2(LRUCache* cache, int key, int* val) {
    LRUNode* node = find_node(cache, key);
    if (!node) {
        return NotFound;
    }
    move_to_front(cache, node);
    *val = node->value;
    return Success;
}

// Put/update the key-value pair in the cache
void put(LRUCache* cache, int key, int value) {
    LRUNode* node = find_node(cache, key);
    if (node) {
        node->value = value;
        move_to_front(cache, node);
        return;
    }

    // Key not found. Evict least recently used if cache is at capacity.
    if (cache->size == cache->capacity) {
        LRUNode* lru_node = cache->tail->prev;
        if (lru_node != cache->head) {
            // 1. Unlink lru_node from doubly linked list
            lru_node->prev->next = lru_node->next;
            lru_node->next->prev = lru_node->prev;

            // 2. Remove lru_node from hash table
            unsigned int lru_bucket = hash(lru_node->key, cache->num_buckets);
            LRUNode* prev_hash = NULL;
            LRUNode* curr_hash = cache->buckets[lru_bucket];
            while (curr_hash) {
                if (curr_hash == lru_node) {
                    if (prev_hash) {
                        prev_hash->hash_next = curr_hash->hash_next;
                    } else {
                        cache->buckets[lru_bucket] = curr_hash->hash_next;
                    }
                    break;
                }
                prev_hash = curr_hash;
                curr_hash = curr_hash->hash_next;
            }

            free(lru_node);
            cache->size--;
        }
    }

    // Allocate and insert the new node
    LRUNode* new_node = (LRUNode*)malloc(sizeof(LRUNode));
    new_node->key = key;
    new_node->value = value;

    // Insert at the front of doubly linked list (MRU)
    new_node->next = cache->head->next;
    new_node->prev = cache->head;
    cache->head->next->prev = new_node;
    cache->head->next = new_node;

    // Insert at front of hash bucket chaining
    unsigned int bucket = hash(key, cache->num_buckets);
    new_node->hash_next = cache->buckets[bucket];
    cache->buckets[bucket] = new_node;

    cache->size++;
}

// Free all resources allocated for the cache
void freeLRUCache(LRUCache* cache) {
    if (!cache) return;

    LRUNode* curr = cache->head->next;
    while (curr != cache->tail) {
        LRUNode* next = curr->next;
        free(curr);
        curr = next;
    }

    free(cache->head);
    free(cache->tail);
    free(cache->buckets);
    free(cache);
}

void test_LRUCache() {
    LRUCache* lRUCache = createLRUCache(2);
    int val;

    put(lRUCache, 1, 1); // cache is {1=1}
    put(lRUCache, 2, 2); // cache is {1=1, 2=2}
    val = get(lRUCache, 1);    // return 1
    printf("val : %d\n", val);

    put(lRUCache, 3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    val = get(lRUCache, 2);    // returns -1 (not found)
    printf("val : %d\n", val);

    put(lRUCache, 4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    val = get(lRUCache, 1);    // return -1 (not found)
    printf("val : %d\n", val);

    val = get(lRUCache, 3);    // return 3
    printf("val : %d\n", val);

    val = get(lRUCache, 4);    // return 4
    printf("val : %d\n", val);

    freeLRUCache(lRUCache);
}

void test_LRUCache2() {
    LRUCache* lRUCache = createLRUCache(2);
    int val = 0;

    put(lRUCache, 1, 1); // cache is {1=1}
    put(lRUCache, 2, 2); // cache is {1=1, 2=2}
    get2(lRUCache, 1, &val);    // return Success, val is 1
    printf("val : %d\n", val);

    put(lRUCache, 3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    get2(lRUCache, 2, &val);    // returns NotFound, val remains 1
    printf("val : %d\n", val);

    put(lRUCache, 4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    get2(lRUCache, 1, &val);    // returns NotFound, val remains 1
    printf("val : %d\n", val);

    get2(lRUCache, 3, &val);    // return Success, val is 3
    printf("val : %d\n", val);

    get2(lRUCache, 4, &val);    // return Success, val is 4
    printf("val : %d\n", val);

    freeLRUCache(lRUCache);
}

int main() {
    test_LRUCache();
    test_LRUCache2();
    return 0;
}
