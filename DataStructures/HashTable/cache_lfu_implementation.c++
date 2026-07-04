#include <unordered_map>
#include <list>
#include <iostream>

using namespace std;

/*
  LeetCode 460: LFU Cache

  Problem Description:
  Design a Least Frequently Used (LFU) cache.
  - `get(key)`: Return value if exists, else -1.
  - `put(key, value)`: Update/insert. Evict least frequently used key 
     on overflow. If there's a tie, evict the least recently used key.

  Algorithm: Hash Map + Frequency Groups
  1. Maintain `minFreq`, the current minimum frequency in the cache.
  2. Use `unordered_map<int, pair<int, int>> cache`: `key -> {value, frequency}`.
  3. Use `unordered_map<int, list<int>> freqMap`: `frequency -> doubly linked list of keys`.
  4. Use `unordered_map<int, list<int>::iterator> iterMap`: `key -> iterator in freqMap`.
  5. `updateFrequency(key)`:
     - Get current frequency `f`.
     - Remove `key` from `freqMap[f]`.
     - If `freqMap[f]` is empty and `f == minFreq`, increment `minFreq`.
     - Increment frequency to `f+1`.
     - Add `key` to `freqMap[f+1]` (front is most recent).
  6. `get(key)`: If exists, `updateFrequency(key)` and return value.
  7. `put(key, value)`:
     - If exists, update value and `updateFrequency(key)`.
     - If new:
       - If at capacity, evict the back of `freqMap[minFreq]` and remove from all maps.
       - Add new key with `frequency = 1`.
       - `minFreq = 1`.

  Complexity Analysis:
  - Time Complexity: O(1) for both `get` and `put`.
    Reason: Hash map and list operations (erase/push_front) are O(1).
  - Space Complexity: O(Capacity).
*/

class LFUCache {
    int capacity;
    int minFreq;
    unordered_map<int, pair<int, int>> keyToValFreq; // key -> {value, freq}
    unordered_map<int, list<int>> freqToKeys;        // freq -> list of keys
    unordered_map<int, list<int>::iterator> keyToIter; // key -> iterator in freq list

    void updateFreq(int key) {
        int f = keyToValFreq[key].second;
        freqToKeys[f].erase(keyToIter[key]);
        if (freqToKeys[f].empty() && f == minFreq) {
            minFreq++;
        }
        keyToValFreq[key].second++;
        freqToKeys[f + 1].push_front(key);
        keyToIter[key] = freqToKeys[f + 1].begin();
    }

public:
    LFUCache(int cap) : capacity(cap), minFreq(0) {}

    int get(int key) {
        if (keyToValFreq.find(key) == keyToValFreq.end()) return -1;
        updateFreq(key);
        return keyToValFreq[key].first;
    }

    void put(int key, int value) {
        if (capacity <= 0) return;

        if (keyToValFreq.find(key) != keyToValFreq.end()) {
            keyToValFreq[key].first = value;
            updateFreq(key);
            return;
        }

        if (keyToValFreq.size() == capacity) {
            // Evict LFU
            int evictKey = freqToKeys[minFreq].back();
            freqToKeys[minFreq].pop_back();
            keyToValFreq.erase(evictKey);
            keyToIter.erase(evictKey);
        }

        keyToValFreq[key] = {value, 1};
        freqToKeys[1].push_front(key);
        keyToIter[key] = freqToKeys[1].begin();
        minFreq = 1;
    }
};

void test() {
    cout << "Testing LFU Cache" << endl;
    LFUCache lfu(2);
    lfu.put(1, 1);
    lfu.put(2, 2);
    cout << "  Get(1): " << lfu.get(1) << " (Expected: 1)" << endl;
    lfu.put(3, 3); // Evicts key 2
    cout << "  Get(2): " << lfu.get(2) << " (Expected: -1)" << endl;
    cout << "  Get(3): " << lfu.get(3) << " (Expected: 3)" << endl;
    lfu.put(4, 4); // Evicts key 1 (both 1 and 3 have freq 2, but 1 was LRU)
    cout << "  Get(1): " << lfu.get(1) << " (Expected: -1)" << endl;
}

int main() {
    test();
    return 0;
}
