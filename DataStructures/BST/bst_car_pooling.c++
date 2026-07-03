/*
LeetCode 1094: Car Pooling

There is a car with 'capacity' empty seats. The vehicle only drives east.
You are given an array 'trips' where trips[i] = [numPassengers, from, to].
Return true if it is possible to pick up and drop off all passengers.

Example:
Input: trips = [[2,1,5],[3,3,7]], capacity = 4
Output: false (At time 3, we need 2+3=5 seats, but capacity is 4)
*/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        // We use a map (Red-Black Tree) to keep timestamps sorted.
        // Key: Time, Value: Net change in passenger count at that stop
        map<int, int> timeline;
        
        for (const auto& trip : trips) {
            int numPassengers = trip[0];
            int start = trip[1];
            int end = trip[2];
            
            timeline[start] += numPassengers;
            timeline[end] -= numPassengers;
        }
        
        int currentPassengers = 0;
        // In-order traversal of the BST (map)
        // nPassengers represents the net difference at a specific stop.
        // Example:
        // - If 5 people get on: nPassengers = +5
        // - If 3 people get off: nPassengers = -3
        // - If 2 get on and 2 get off at same time: nPassengers = 0
        for (auto const& [time, nPassengers] : timeline) {
            currentPassengers += nPassengers;
            if (currentPassengers > capacity) {
                return false;
            }
        }
        
        return true;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Over capacity
    vector<vector<int>> trips1 = {{2, 1, 5}, {3, 3, 7}};
    int cap1 = 4;
    cout << "Test 1 (Over Cap): " << (sol.carPooling(trips1, cap1) ? "Success" : "Failed") << " (Expected: Failed)" << endl;

    // Test Case 2: Within capacity
    int cap2 = 5;
    cout << "Test 2 (Exact Cap): " << (sol.carPooling(trips1, cap2) ? "Success" : "Failed") << " (Expected: Success)" << endl;

    // Test Case 3: Multiple boarding at same time
    vector<vector<int>> trips3 = {{2, 1, 5}, {3, 1, 5}}; // 5 people at time 1
    cout << "Test 3 (Concurrent Boarding): " << (sol.carPooling(trips3, 4) ? "Success" : "Failed") << " (Expected: Failed)" << endl;
    cout << "Test 4 (Concurrent Boarding): " << (sol.carPooling(trips3, 5) ? "Success" : "Failed") << " (Expected: Success)" << endl;

    // Test Case 5: Drop off and pick up at same time
    vector<vector<int>> trips5 = {{2, 1, 5}, {2, 5, 8}}; // Drop 2 at 5, pick 2 at 5
    cout << "Test 5 (Same-stop Transfer): " << (sol.carPooling(trips5, 2) ? "Success" : "Failed") << " (Expected: Success)" << endl;
         
    return 0;
}
