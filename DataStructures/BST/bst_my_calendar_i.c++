#include <set>
#include <iostream>

using namespace std;

/*
  LeetCode 729: My Calendar I

  Problem Description:
  Implement a `MyCalendar` class to store your events. A new event 
  can be added if adding the event will not cause a double booking.
  An event is represented as `[start, end)`.

  Algorithm: Binary Search Tree (std::set)
  1. Use a `std::set<pair<int, int>>` to store existing events.
  2. To book `[start, end)`:
     - Find the first event that starts AFTER or AT the current 
       start time (`lower_bound`).
     - If this next event overlaps with current (i.e., `next->start < end`), 
       return false.
     - If the previous event overlaps with current (i.e., `prev->end > start`), 
       return false.
     - Otherwise, insert the new event and return true.

  Complexity Analysis:
  - Time Complexity: O(log N) per `book` call.
    Reason: Binary search (lower_bound) and insertion in `std::set`.
  - Space Complexity: O(N) to store all events.

  Brute Force comparison:
  - Check every existing event for overlap: O(N) per call.
  - The BST approach reduces this to logarithmic time.
*/

class MyCalendar {
    set<pair<int, int>> events;

public:
    bool book(int start, int end) {
        auto it = events.lower_bound({start, end});

        // Check overlap with next event
        if (it != events.end() && it->first < end) return false;

        // Check overlap with previous event
        if (it != events.begin() && prev(it)->second > start) return false;

        events.insert({start, end});
        return true;
    }
};

void test(int start, int end, bool expected) {
    static MyCalendar cal;
    bool result = cal.book(start, end);
    cout << "Book [" << start << ", " << end << ") -> " << boolalpha << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    test(10, 20, true);
    test(15, 25, false);
    test(20, 30, true);
    return 0;
}
