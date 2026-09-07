#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>

using namespace std;

/*
  Consistent Hashing with Virtual Nodes (Vnodes)

  Problem:
  In basic consistent hashing (where each physical node has only 1 position on 
  the hash ring), we suffer from severe load imbalance (hotspotting). Because 
  there are so few points on the circle, some nodes get allocated much larger 
  sectors of the ring than others, leaving some servers idle (e.g., NodeB 
  receiving 0 keys in our basic test).

  Solution: Virtual Nodes (Vnodes)
  - Instead of mapping each physical node to the ring once, we map multiple 
    virtual copies (replicas) of each node (e.g., NodeA#0, NodeA#1, NodeA#2, etc.).
  - This disperses the partition boundaries uniformly across the ring.
  - As a result, the keys are distributed extremely evenly across all physical 
    nodes.
  - When we add or remove a physical node, we add/remove all of its virtual replicas, 
    maintaining minimal re-mapping with balanced distribution.

  Complexity Analysis:
  - Time Complexity:
    - getNode: O(log (N * V)) where N is the number of physical nodes and V is 
      the number of virtual nodes per physical node.
      Reason: Binary search (lower_bound) on the sorted map of size N * V.
    - addNode / removeNode: O(V log (N * V)). We perform V insertions/erasures 
      on the sorted map.
  - Space Complexity:
    - O(N * V) to store the virtual node hash keys on the ring.
*/

class ConsistentHashingVNodes {
    // Map virtual node hash to physical node name
    map<size_t, string> hashRing;
    int vnodesCount;

public:
    ConsistentHashingVNodes(int vnodes = 50) : vnodesCount(vnodes) {}

    void addNode(const string& nodeName) {
        for (int i = 0; i < vnodesCount; i++) {
            // Generate a unique identifier for each virtual node replica
            string vnodeName = nodeName + "#" + to_string(i);
            size_t h = hash<string>{}(vnodeName);
            hashRing[h] = nodeName; // Map virtual hash to physical node name
        }
    }

    void removeNode(const string& nodeName) {
        for (int i = 0; i < vnodesCount; i++) {
            string vnodeName = nodeName + "#" + to_string(i);
            size_t h = hash<string>{}(vnodeName);
            hashRing.erase(h);
        }
    }

    string getNode(const string& key) {
        if (hashRing.empty()) return "";
        size_t h = hash<string>{}(key);
        
        // Find the first virtual node with hash >= h
        auto it = hashRing.lower_bound(h);
        if (it == hashRing.end()) {
            it = hashRing.begin(); // Wrap around the circular ring
        }
        return it->second; // Return the associated physical node
    }
};

void runDistributionTest(int numVnodes) {
    cout << "---------------------------------------------------------" << endl;
    cout << "Testing Consistent Hashing with Vnodes = " << numVnodes << endl;
    cout << "---------------------------------------------------------" << endl;

    ConsistentHashingVNodes ch(numVnodes);
    ch.addNode("NodeA");
    ch.addNode("NodeB");
    ch.addNode("NodeC");

    // Track how many keys are routed to each server
    unordered_map<string, int> serverCounts;

    // We will distribute 60 test keys and observe the distribution
    vector<string> keys;
    for (int i = 1; i <= 60; i++) {
        keys.push_back("user_session_id_" + to_string(i));
    }

    // Route keys
    for (const string& k : keys) {
        string node = ch.getNode(k);
        serverCounts[node]++;
    }

    // Print key distribution results
    cout << "Server utilization (out of 60 keys):" << endl;
    for (const string& s : {"NodeA", "NodeB", "NodeC"}) {
        cout << "  " << s << ": " << serverCounts[s] << " keys (" 
             << (serverCounts[s] * 100.0 / 60.0) << "%)" << endl;
    }
}

int main() {
    cout << "=========================================================" << endl;
    cout << "         CONSISTENT HASHING WITH VIRTUAL NODES           " << endl;
    cout << "=========================================================" << endl;

    // Test with 5 virtual nodes (better, but still some variance)
    runDistributionTest(5);
    cout << endl;

    // Test with 100 virtual nodes (should be very evenly balanced!)
    runDistributionTest(100);

    cout << "=========================================================" << endl;
    return 0;
}
