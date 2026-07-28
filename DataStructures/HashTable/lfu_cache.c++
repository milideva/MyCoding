#include <map>
#include <list>
#include <iostream>
#include <unordered_map>

/*
Design a data structure that follows the constraints of a Least Frequently Used (LFU) cache.

Implement the LFUCache class:

    LFUCache(int capacity) 
    Initializes the object with the capacity of the data structure.

    int get(int key) 
    Gets the value of the key if the key exists in the cache. Otherwise, returns -1.

    void put(int key, int value) 
    Sets or inserts the value if the key is not already present. When the cache
    reaches its capacity, it should invalidate the least frequently used item
    before inserting a new item. For this problem, when there is a tie (i.e.,
    two or more keys with the same frequency), the least recently used key would
    be evicted.

Notice that the number of times an item is used is the number of calls to the
get and put functions for that item since it was inserted. This number is set to
zero when the item is removed.

    get and put should be in O(1) time complexity
*/

using namespace std;


class LFUCache {
    int cap;
    int timestamp;
    
    unordered_map <int, int> key2freq;
    unordered_map <int, int> key2time;
    unordered_map <int, int> key2val;

    //map is ordered, lowest {f, t} at front to highest at the back, for evict, erase the front()
    map <pair<int, int>, int> freqTime2Key; 

    void tick (void) {
        timestamp++;
    }

public:

    LFUCache (int capacity) {
        cap = capacity;
        timestamp = 0;
    }
    
    int get (int key) {
        tick();
        
        if (key2val.find(key) == key2val.end()) {
            return -1;
        }
        // first erase from freqTime2Key since time and freq needs to be updated
        freqTime2Key.erase({key2freq[key], key2time[key]});
        
        // Found it, update timestamp, freq in the cache
        key2time[key] = timestamp;
        key2freq[key]++;
        
        // Re-insert in freqTime2Key with new time and new freq : new { f, t } => key
        freqTime2Key[{key2freq[key], key2time[key]}] = key;
        
        return key2val[key];
    }
    
    void put (int key, int value) {
        tick();
        
        if (cap == 0) return;
        
        if (key2val.count(key)) {
          // Found it
            
          // first erase from freqTime2Key since time and freq needs to be updated
          freqTime2Key.erase({key2freq[key], key2time[key]});
          
          // update timestamp, freq in the cache
          key2time[key] = timestamp;
          key2freq[key]++;
          
          // Re-insert in freqTime2Key with new time and new freq
          freqTime2Key[{key2freq[key], key2time[key]}] = key;
          
          key2val[key] = value;
          return;
        }

        // Not found, need to add to cache, check if there is space
        
        if (key2val.size() < cap) {
            // update timestamp, freq in the cache
            key2time[key] = timestamp;
            key2freq[key] = 1;
        
            // Insert in freqTime2Key with new time and new freq
            freqTime2Key[{key2freq[key], key2time[key]}] = key;
        
            key2val[key] = value;
            return;
        }
        
        // We've reached the cap, need to evict a cache line
        int oldkey = (*freqTime2Key.begin()).second;
        key2val.erase(oldkey);
        freqTime2Key.erase(freqTime2Key.begin());
        
        // update timestamp, freq in the cache
        key2time[key] = timestamp;
        key2freq[key] = 1;
        
        // Re-insert in freqTime2Key with new time and new freq
        freqTime2Key[{key2freq[key], key2time[key]}] = key;
        
        key2val[key] = value;
        return;
    }
};

int main () {

  LFUCache *lfuCache = new LFUCache(2);
  int val;

  lfuCache->put(1, 1); // cache is {1=1}
  lfuCache->put(2, 2); // cache is {1=1, 2=2}
  val = lfuCache->get(1);    // return 1
  cout << "val : " << val << endl;

  lfuCache->put(3, 3); // LFU key was 2, evicts key 2, cache is {1=1, 3=3}
  val = lfuCache->get(2);    // returns -1 (not found)
  cout << "val : " << val << endl;

  val = lfuCache->get(3);    // return 3
  cout << "val : " << val << endl;


  lfuCache->put(4, 4);    

  val = lfuCache->get(1);    // return -1
  cout << "val : " << val << endl;

  val = lfuCache->get(3);    // return 3
  cout << "val : " << val << endl;

  val = lfuCache->get(4);    // return 4
  cout << "val : " << val << endl;
  
  return 0;
}
