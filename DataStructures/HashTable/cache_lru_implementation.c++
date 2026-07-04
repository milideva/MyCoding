#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;

/*
  LeetCode 146: LRU Cache

  Problem Description:
  Design a data structure that follows the constraints of a Least 
  Recently Used (LRU) cache.
  - `LRUCache(int capacity)`: Initialize with positive capacity.
  - `int get(int key)`: Return the value if key exists, else -1.
  - `void put(int key, int value)`: Update or add key-value pair. 
     Evict the least recently used key if capacity exceeded.

  Algorithm: Hash Map + Doubly Linked List
  1. Use an `unordered_map<int, list<int>::iterator>` to store 
     `key -> iterator` to the node in the doubly linked list.
  2. Use a `std::list<pair<int, int>>` to store `{key, value}`. 
     - Front of the list: Most Recently Used (MRU).
     - Back of the list: Least Recently Used (LRU).
  3. `get(key)`:
     - If key not found, return -1.
     - Move the node to the front (MRU) and return value.
  4. `put(key, value)`:
     - If key exists, update value and move to front.
     - If key not found:
       - If at capacity, evict the back of the list and remove 
         from hash map.
       - Insert new `{key, value}` at the front and add to hash map.

  Complexity Analysis:
  - Time Complexity: O(1) for both `get` and `put`.
    Reason: Hash map and doubly linked list operations (splice/push_front) 
    are constant time.
  - Space Complexity: O(Capacity).
*/

class LRUCache {
    int capacity;
    // List stores {key, value}
    list<pair<int, int>> cache;
    // Map stores key -> iterator to list node
    unordered_map<int, list<pair<int, int>>::iterator> m;

    void makeMostRecent(int key) {
        // Move the node to the front of the list
        cache.splice(cache.begin(), cache, m[key]);
    }

public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        if (m.find(key) == m.end()) return -1;
        makeMostRecent(key);
        return m[key]->second;
    }

    void put(int key, int value) {
        if (m.find(key) != m.end()) {
            m[key]->second = value;
            makeMostRecent(key);
            return;
        }

        if (cache.size() == capacity) {
            // Evict LRU (last element)
            int lruKey = cache.back().first;
            m.erase(lruKey);
            cache.pop_back();
        }

        cache.push_front({key, value});
        m[key] = cache.begin();
    }
};

void test() {
    cout << "Testing LRU Cache" << endl;
    LRUCache lru(2);
    lru.put(1, 1);
    lru.put(2, 2);
    cout << "  Get(1): " << lru.get(1) << " (Expected: 1)" << endl;
    lru.put(3, 3); // Evicts key 2
    cout << "  Get(2): " << lru.get(2) << " (Expected: -1)" << endl;
    lru.put(4, 4); // Evicts key 1
    cout << "  Get(1): " << lru.get(1) << " (Expected: -1)" << endl;
    cout << "  Get(3): " << lru.get(3) << " (Expected: 3)" << endl;
    cout << "  Get(4): " << lru.get(4) << " (Expected: 4)" << endl;
}

int main() {
    test();
    return 0;
}
