#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 731: My Calendar Two

  Problem Description:
  Implement a `MyCalendarTwo` class to store your events. A new event 
  can be added if it does not cause a TRIPLE booking.

  -------------------------------------------------------------------------
  WHY `std::set` (FROM MY CALENDAR I) CANNOT BE USED HERE:
  -------------------------------------------------------------------------
  1. In My Calendar I, no overlaps of any kind are allowed. This means every 
     interval is strictly disjoint. Because they are disjoint, we can find the 
     exact position of any new interval using binary search (`lower_bound`) 
     in O(log N) time, and we only need to check the IMMEDIATE left and right 
     neighbors to guarantee there is no overlap anywhere in the entire tree.

  2. In My Calendar II, double bookings (single overlaps) are fully allowed. 
     Because intervals can overlap, they are no longer disjoint. This breaks the 
     single-neighbor property. A single new booking could simultaneously 
     overlap with multiple distinct, already-overlapping intervals spread across 
     different parts of the tree. 

     If we used a `std::set`, checking only the adjacent left and right neighbors 
     would fail to detect overlaps with other overlapping intervals further up or 
     down the tree. Finding and verifying all overlapping sets would require 
     traversing multiple nodes, making standard O(log N) set binary neighbor-searching 
     mathematically insufficient.

  -------------------------------------------------------------------------
  HOW THE SWEEP-LINE ALGORITHM WORKS:
  -------------------------------------------------------------------------
  The Sweep-Line algorithm simplifies managing intervals by treating the timeline 
  as a continuous horizontal line from left to right.

  1. We only care about the specific discrete timestamps where state changes occur:
     - At a start time: Active bookings increase by 1.
     - At an end time: Active bookings decrease by 1.

  2. We record these state changes as deltas in a sorted map (`std::map<int, int> delta`):
     - `delta[start]++` (Booking starts)
     - `delta[end]--`   (Booking ends)

  3. To validate a booking `[start, end)`:
     - We temporarily record its start and end deltas in the map.
     - We perform a "sweep" (a chronological iteration) from left to right across 
       all sorted boundary keys in the map, accumulating the running active sum:
       `active += count`
     - If `active >= 3` at any point during the sweep, we have detected a triple 
       booking. We backtrack (revert the map deltas) and return false.
     - If the sweep finishes and `active < 3` everywhere, the booking is valid.

  -------------------------------------------------------------------------
  Complexity Analysis:
  -------------------------------------------------------------------------
  - Time Complexity:
    - Best Case: O(N) per booking.
    - Average Case: O(N).
    - Worst Case: O(N).
    Reason: We must sweep/iterate through the entire map (which contains at 
    most 2N entries) to accumulate and verify the running active sum.
  - Space Complexity:
    - O(N) auxiliary space to store the boundary delta points in the map.
*/

class MyCalendarTwo {
    map<int, int> delta;

public:
    bool book(int start, int end) {
        delta[start]++;
        delta[end]--;

        int active = 0;
        for (auto const& [time, count] : delta) {
            active += count;
            if (active >= 3) {
                // Triple booking detected, backtrack
                delta[start]--;
                delta[end]++;
                return false;
            }
        }
        return true;
    }
};

void test(int start, int end, bool expected) {
    static MyCalendarTwo cal;
    bool result = cal.book(start, end);
    cout << "Book [" << start << ", " << end << ") -> " << boolalpha << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    test(10, 20, true);
    test(50, 60, true);
    test(10, 40, true); // Double booking OK
    test(5, 15, false); // Triple booking
    test(5, 10, true);
    test(25, 55, true);
    return 0;
}
