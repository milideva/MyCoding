#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 732: My Calendar III

  Problem Description:
  Implement a `MyCalendarThree` class. Return an integer `k` 
  representing the maximum number of concurrent events (k-booking) 
  at any point in time after the new event is added.

  Algorithm: Sweep-Line
  1. Use a `std::map<int, int>` to store boundary points.
  2. For `book(start, end)`:
     - Increment `delta[start]`, decrement `delta[end]`.
     - Maintain a `maxK` variable.
     - Sweep through the entire timeline (ordered map) to find 
       the global maximum of the running sum.
     - Return the global `maxK`.

  Complexity Analysis:
  - Time Complexity: O(N) per `book` call.
  - Space Complexity: O(N).
*/

class MyCalendarThree {
    map<int, int> delta;

public:
    int book(int start, int end) {
        delta[start]++;
        delta[end]--;

        int maxK = 0;
        int active = 0;
        for (auto const& [time, count] : delta) {
            active += count;
            maxK = max(maxK, active);
        }
        return maxK;
    }
};

void test(int start, int end, int expected) {
    static MyCalendarThree cal;
    int result = cal.book(start, end);
    cout << "Book [" << start << ", " << end << ") -> MaxK: " << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    test(10, 20, 1);
    test(50, 60, 1);
    test(10, 40, 2);
    test(5, 15, 3);
    test(5, 10, 3);
    test(25, 55, 3);
    return 0;
}
