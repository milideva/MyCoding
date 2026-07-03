/*
Problem: Restaurant Booking (Variation of Meeting Rooms II)

A restaurant has 'maxTables' available. Given a list of reservations 
where bookings[i] = [startTime, endTime], return the maximum number of 
tables occupied at any given time to see if the restaurant can accommodate all.

Example:
Input: bookings = [[12, 14], [13, 15], [17, 20]], maxTables = 2
Output: Max Tables Needed: 2 (Possible)
*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class RestaurantManager {
public:
    int minTablesRequired(vector<vector<int>>& bookings) {
        // Map (BST) stores the difference at each time point.
        map<int, int> delta;
        
        for (const auto& booking : bookings) {
            delta[booking[0]]++; // Table occupied
            delta[booking[1]]--; // Table freed
        }
        
        int maxTables = 0;
        int currentTables = 0;
        
        // In-order traversal of the map
        for (auto const& [time, count] : delta) {
            currentTables += count;
            maxTables = max(maxTables, currentTables);
        }
        
        return maxTables;
    }
};

int main() {
    RestaurantManager rm;
    
    // Test Case 1: Overlapping lunch rush
    vector<vector<int>> bookings1 = {{12, 14}, {13, 15}, {12, 15}};
    cout << "Test 1 (Lunch Rush): " << rm.minTablesRequired(bookings1) << " (Expected: 3)" << endl;

    // Test Case 2: Non-overlapping
    vector<vector<int>> bookings2 = {{10, 11}, {12, 13}, {14, 15}};
    cout << "Test 2 (Sequential): " << rm.minTablesRequired(bookings2) << " (Expected: 1)" << endl;

    // Test Case 3: Bookings starting when others end
    vector<vector<int>> bookings3 = {{12, 14}, {14, 16}};
    cout << "Test 3 (Handover): " << rm.minTablesRequired(bookings3) << " (Expected: 1)" << endl;

    // Test Case 4: Multiple simultaneous bookings
    vector<vector<int>> bookings4 = {{12, 14}, {12, 14}, {12, 14}};
    cout << "Test 4 (Same Time): " << rm.minTablesRequired(bookings4) << " (Expected: 3)" << endl;

    return 0;
}
