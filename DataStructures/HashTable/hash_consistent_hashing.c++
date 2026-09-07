#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <vector>

using namespace std;

/*
  Problem: Consistent Hashing Implementation

  Problem Description:
  Consistent hashing is a technique used in distributed systems to 
  distribute keys across a changing set of nodes with minimal 
  re-mapping when nodes are added or removed.

  Algorithm: Hash Ring
  1. Map both nodes and keys to a large circular identifier space 
     (the "hash ring").
  2. Use a sorted map (`hashRing`) to store `node_hash -> node_name`.
  3. To find the node for a `key`:
     - Calculate `key_hash`.
     - Find the first node in the map with `node_hash >= key_hash` 
       (using `lower_bound`).
     - If no such node exists, wrap around to the first node in the map.
  4. Adding/Removing nodes: Only a fraction of keys (roughly 1/N) 
     need to be re-mapped.

  Complexity Analysis:
  - Find Node: O(log N) where N is the number of nodes.
    Reason: Binary search on the sorted map.
  - Add/Remove Node: O(log N).
  - Space Complexity: O(N) to store node hashes.
*/

class ConsistentHashing {
    // Map hash value to node name
    map<size_t, string> hashRing;

public:
    void addNode(const string& nodeName) {
        size_t h = hash<string>{}(nodeName);
        hashRing[h] = nodeName;
    }

    void removeNode(const string& nodeName) {
        size_t h = hash<string>{}(nodeName);
        hashRing.erase(h);
    }

    string getNode(const string& key) {
        if (hashRing.empty()) return "";
        size_t h = hash<string>{}(key);
        
        // Find first node with hash >= h
        auto it = hashRing.lower_bound(h);
        if (it == hashRing.end()) {
            it = hashRing.begin(); // Wrap around
        }
        return it->second;
    }
};

void test() {
    ConsistentHashing ch;
    ch.addNode("NodeA");
    ch.addNode("NodeB");
    ch.addNode("NodeC");

    cout << "Testing Consistent Hashing" << endl;
    string keys[] = {"user1", "user2", "user3", "data_point_1"};
    for (const string& k : keys) {
        cout << "  Key \"" << k << "\" -> " << ch.getNode(k) << endl;
    }

    cout << "\nRemoving NodeB..." << endl;
    ch.removeNode("NodeB");
    for (const string& k : keys) {
        cout << "  Key \"" << k << "\" -> " << ch.getNode(k) << endl;
    }
}

int main() {
    test();
    return 0;
}

/*
  -------------------------------------------------------------------------
  OBSERVED PROBLEM: Hotspotting & Unbalanced Distribution
  -------------------------------------------------------------------------
  When running this code, we observe the following execution output:

  Testing Consistent Hashing
    Key "user1" -> NodeC
    Key "user2" -> NodeA
    Key "user3" -> NodeA
    Key "data_point_1" -> NodeA

  Removing NodeB...
    Key "user1" -> NodeC
    Key "user2" -> NodeA
    Key "user3" -> NodeA
    Key "data_point_1" -> NodeA

  Notice that NodeB received exactly 0 keys. This is because with only 3 nodes 
  mapped onto the ring once (1 hash per physical node), the ring partitions 
  are highly unequal, leading to severe hotspotting and poor load balance.
  
  This limitation is solved in `hash_consistent_hashing_2.c++` by introducing 
  Virtual Nodes (Vnodes).
*/
