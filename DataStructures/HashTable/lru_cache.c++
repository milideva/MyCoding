#include <map>
#include <list>
#include <iostream>
#include <unordered_map>

/*
  Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:
  
  LRUCache (int capacity) Initialize the LRU cache with positive size capacity.
 
  int get (int key) Return the value of the key if the key exists, otherwise return -1.
  
  void put (int key, int value) Update the value of the key if the key exists. 

  Otherwise, add the key-value pair to the cache. 
  If the number of keys exceeds the capacity from this operation, evict the least recently used key.
  
  get and put should be in O(1) time complexity
*/

using namespace std;

enum class LruCacheReturnCodes {
    NotFound,
    Success
};

// very clear logic
class LRUCache2 {

  int size;
  list <int> lru;                              //  holds keys : front() has MRU ... LRU at the back()
  unordered_map <int, list<int>::iterator> k2itr; // key -> iterator
  unordered_map <int, int> k2v;                 // key -> value
  
  // lru insert or erase - the beauty is, for List - all other iterators and references unaffected
  void updateLRU (int key) {
    if (k2v.count(key)) 
      lru.erase(k2itr[key]);  // erase directly using iterator without walking the list, O(1)
    lru.push_front(key);      // front() has MRU O(1)
    k2itr[key] = lru.begin();
  }
  void evict () {
    int key = lru.back();
    k2itr.erase(key);
    k2v.erase(key);
    lru.pop_back();
  }

public:
  
  LRUCache2 (int capacity) : size(capacity) {}
  
  LruCacheReturnCodes get (int key, int &val) {
    if (k2v.count(key) == 0) {
      return LruCacheReturnCodes::NotFound;
    }
    updateLRU(key);
    val = k2v[key];
    return LruCacheReturnCodes::Success;
  }

  void put (int key, int value) {
    if (k2v.size() == size && k2v.count(key) == 0)
      evict();
    updateLRU(key);
    k2v[key] = value;
  }

};

class LRUCache {
    int cap;
    unordered_map <int, pair<int, list <int>::iterator>> hashtable; // key <--> { data, itr}
    list <int> listcache; // key @ itr
    
public:
  LRUCache(int capacity) {
    cap = capacity;
  }
  
  int get(int key) {
    if (hashtable.find(key) == hashtable.end()) 
      return -1;
    
    listcache.erase(hashtable[key].second);
    listcache.push_back(key);
    hashtable[key].second = --listcache.end();
    
    return hashtable[key].first;
  }
  
  void put(int key, int value) {
    if (hashtable.find(key) != hashtable.end()) {
      // found key - remove, update the value, and LRU location
      
      listcache.erase(hashtable[key].second); // remove from listCache using iterator
      listcache.push_back(key); // update LRU location in listCache to the end

      hashtable[key].second = --listcache.end();
      hashtable[key].first = value;
      return;
    }
    
    // Not found, allocate
    if (listcache.size() == cap) {
      // evict the front of lru
      hashtable.erase(listcache.front()); // evict from hashtable, using iterator from front of listcache
      listcache.pop_front(); // evict the front of listcache now
    }            
    listcache.push_back(key);
    hashtable[key] = make_pair(value, --listcache.end()); // save key --->  pair {value, itr} 
    
  }
};

void test_LRUCache () {
  LRUCache *lRUCache = new LRUCache(2);
  int val;

  lRUCache->put(1, 1); // cache is {1=1}
  lRUCache->put(2, 2); // cache is {1=1, 2=2}
  val = lRUCache->get(1);    // return 1
  cout << "val : " << val << endl;

  lRUCache->put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
  val = lRUCache->get(2);    // returns -1 (not found)
  cout << "val : " << val << endl;

  lRUCache->put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
  val = lRUCache->get(1);    // return -1 (not found)

  cout << "val : " << val << endl;

  val = lRUCache->get(3);    // return 3
  cout << "val : " << val << endl;

  val = lRUCache->get(4);    // return 4
  cout << "val : " << val << endl;
}

void test_LRUCache2 () {
 
  LRUCache2 *lRUCache = new LRUCache2(2);
  int val;

  lRUCache->put(1, 1); // cache is {1=1}
  lRUCache->put(2, 2); // cache is {1=1, 2=2}
  lRUCache->get(1, val);    // return 1
  cout << "val : " << val << endl;

  lRUCache->put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
  lRUCache->get(2, val);    // returns -1 (not found)
  cout << "val : " << val << endl;

  lRUCache->put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
  lRUCache->get(1, val);    // return -1 (not found)

  cout << "val : " << val << endl;

  lRUCache->get(3, val);    // return 3
  cout << "val : " << val << endl;

  lRUCache->get(4, val);    // return 4
  cout << "val : " << val << endl;

}

int main () {

  test_LRUCache();

  test_LRUCache2();

  return 0;
}
