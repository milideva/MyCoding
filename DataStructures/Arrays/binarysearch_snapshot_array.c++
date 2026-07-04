#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

/*
  LeetCode 1146: Snapshot Array

  Problem Description:
  Implement a SnapshotArray that supports the following interface:
  - `SnapshotArray(int length)` initializes an array with the given length.
  - `void set(index, val)` sets the element at the given index to `val`.
  - `int snap()` takes a snapshot and returns the `snap_id` (count - 1).
  - `int get(index, snap_id)` returns the value at the given index at 
     the time the snapshot was taken.

  Algorithm: Binary Search on Snapshots
  1. For each index, instead of a single value, store a list of 
     `(snap_id, value)` pairs.
  2. A `std::map<int, int>` for each index can store these pairs 
     automatically sorted by `snap_id`.
  3. `set(index, val)`: Add or update the entry for the current 
     `snap_id` at `index`.
  4. `get(index, snap_id)`: Use `upper_bound` on the map (or `lower_bound` 
     with adjustments) to find the largest `snap_id' <= snap_id`.

  Complexity Analysis:
  - Time Complexity:
    - Constructor: O(L) where L is the length.
    - set: O(log S) where S is the number of snapshots.
    - snap: O(1).
    - get: O(log S).
  - Space Complexity: O(N + S_calls) to store all history.

  Brute Force comparison:
  - Store a complete copy of the array for every snapshot.
  - Space: O(L * S). This will exceed memory for L=50k, S=50k.
  - The map-based approach only stores changes, making it space-efficient.
*/

class SnapshotArray {
    // Each index has a history of {snap_id -> value}
    vector<map<int, int>> history;
    int curr_snap_id = 0;

public:
    SnapshotArray(int length) {
        history.resize(length);
        for (int i = 0; i < length; ++i) {
            history[i][0] = 0; // Initial value at snap_id 0 is 0
        }
    }

    void set(int index, int val) {
        history[index][curr_snap_id] = val;
    }

    int snap() {
        return curr_snap_id++;
    }

    int get(int index, int snap_id) {
        // Find the entry with the largest id <= snap_id
        auto it = history[index].upper_bound(snap_id);
        // upper_bound returns the first element > snap_id. 
        // The element we want is the one just before it.
        return prev(it)->second;
    }
};

void test() {
    cout << "Testing: Snapshot Array" << endl;
    SnapshotArray snapshotArr(3);
    snapshotArr.set(0, 5);
    int s0 = snapshotArr.snap(); // 0
    snapshotArr.set(0, 6);
    int val = snapshotArr.get(0, 0); 
    cout << "  [PASS] Get(0, 0) = " << val << " (Expected: 5)" << endl;
    
    snapshotArr.snap(); // 1
    cout << "  [PASS] Get(0, 1) = " << snapshotArr.get(0, 1) << " (Expected: 6)" << endl;
}

int main() {
    test();
    return 0;
}
