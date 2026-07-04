#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 731: My Calendar II

  Problem Description:
  Implement a `MyCalendarTwo` class to store your events. A new event 
  can be added if it does not cause a TRIPLE booking.

  Algorithm: Sweep-Line with Boundary Counting
  1. Use a `std::map<int, int>` to store the change in active events 
     at each boundary time.
  2. For `book(start, end)`:
     - Increment `delta[start]` and decrement `delta[end]`.
     - Perform a "sweep" across the timeline by summing up values in 
       the map.
     - If the running count exceeds 2 at any point, a triple booking 
       occurred.
     - If invalid: Revert the changes to the map and return false.
     - Otherwise, return true.

  Complexity Analysis:
  - Time Complexity: O(N) per `book` call.
    Reason: We iterate through the entire map (max 2N entries).
  - Space Complexity: O(N) to store the boundary points.
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
