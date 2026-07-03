/*

Implement a MyCalendarTwo class to store your events. A new event can be added
if adding the event will not cause a triple booking.

Your class will have one method, book(int start, int end). Formally, this
represents a booking on the half open interval [start, end), the range of real
numbers x such that start <= x < end.

A triple booking happens when three events have some non-empty intersection
(ie., there is some time that is common to all 3 events.)

For each call to the method MyCalendar.book, return true if the event can be
added to the calendar successfully without causing a triple booking. Otherwise,
return false and do not add the event to the calendar.

Your class will be called like this: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)

Example 1:

MyCalendar();
MyCalendar.book(10, 20); // returns true
MyCalendar.book(50, 60); // returns true
MyCalendar.book(10, 40); // returns true
MyCalendar.book(5, 15); // returns false
MyCalendar.book(5, 10); // returns true
MyCalendar.book(25, 55); // returns true
Explanation: 
The first two events can be booked.  The third event can be double booked.
The fourth event (5, 15) can't be booked, because it would result in a triple booking.
The fifth event (5, 10) can be booked, as it does not use time 10 which is already double booked.
The sixth event (25, 55) can be booked, as the time in [25, 40) will be double booked with the third event;
the time [40, 50) will be single booked, and the time [50, 55) will be double booked with the second event.

Note:

    The number of calls to MyCalendar.book per test case will be at most 1000.
    In calls to MyCalendar.book(start, end), start and end are integers in the range [0, 10^9].

*/

#include <set>
#include <map>
#include <iostream>
using namespace std;

/*
 * Approach: Boundary Counting (Sweep-Line Algorithm)
 *
 * This problem is a variation of "Meeting Rooms II". We need to determine if a
 * new event causes a "triple booking", meaning three or more events overlap at
 * some point in time.
 *
 * The sweep-line algorithm is a perfect fit for this. We treat the start and end
 * points of each event as critical "boundary" points on a timeline.
 *
 * How it works:
 * 1. We use a map (`calMap`) to store the change in the number of active events
 *    at each boundary point.
 * 2. For an event `[start, end)`, we increment the count at `start` (`calMap[start]++`)
 *    and decrement the count at `end` (`calMap[end]--`).
 * 3. To check for a triple booking, we "sweep" through the timeline by iterating
 *    through the sorted keys of the map. We maintain a running `count` of active events.
 * 4. At each boundary point, we add its value to `count`. If `count` ever exceeds 2,
 *    it signifies a point in time where three or more events are active, i.e., a
 *    triple booking.
 *
 * Why this is better than direct interval comparison:
 * With direct interval comparison (like in MyCalendar I), we would need to keep
 * two lists: one for single-booked intervals and one for double-booked intervals.
 * When a new event comes in, we would have to check for overlaps with both lists,
 * calculate new double-booked intervals, and then check if the new event creates
 * a triple booking by overlapping with an existing double-booked interval. This
 * logic is significantly more complex to implement correctly. The sweep-line
 * approach elegantly handles any number of overlapping events by simply changing
 * the threshold (`nRooms`).
 *
 * Time Complexity: O(N) per `book()` call.
 * - In the `book` method, we perform two map insertions (`calMap[start]++` and
 *   `calMap[end]--`), which are O(log N).
 * - The `canAdd` check then iterates through the entire map, which has up to 2*N
 *   entries, making it O(N), where N is the number of events booked so far.
 * - Since O(N) dominates O(log N), the overall complexity per call is O(N).
 *
 * Space Complexity: O(N)
 * - The map stores up to two boundary points for each of the N events.
 */
class MyCalendarMap {
  map <int, int> calMap;
  
  /*
   * This function uses a sweep-line algorithm to detect triple bookings. It
   * iterates through the time points (boundaries) in chronological order and
   * keeps a running count of active events. A triple booking occurs if the
   * number of active events ever exceeds 2.
   *
   * For example, if we have bookings (10, 40) and (25, 55), and we want to book (5, 15):
   *
   * Boundaries for (10, 40): calMap[10]++, calMap[40]--
   * Boundaries for (25, 55): calMap[25]++, calMap[55]--
   *
   * Pre-existing calMap: { 10:1, 25:1, 40:-1, 55:-1 }
   *
   * Now, try to book (5, 15):
   *   - Tentatively add boundaries: calMap[5]++, calMap[15]--
   *   - New calMap for check: { 5:1, 10:1, 15:-1, 25:1, 40:-1, 55:-1 }
   *
   * Sweep-line process:
   * - At time 5,  active events become 1. (count=1)
   * - At time 10, active events become 2. (count=2)
   * - At time 15, active events become 1. (count=1)
   * - At time 25, active events become 2. (count=2)
   * ... and so on.
   *
   * Since `count` never exceeds 2, the booking is allowed.
   *
   * If we then tried to book (10, 20), `count` at time 10 would become 3,
   * `canAdd` would return false, and the booking would be rejected.
   */
  bool canAdd (int numMeetingRooms) {
    int count = 0;
    for (auto const& [time, change] : calMap) {
      count += change;
      if (count > numMeetingRooms) {
        return false;
      }
    }
    return true;
  }

public:
  MyCalendarMap() {   
  }
  
  bool book(int start, int end) {
    // Tentatively add the new event's boundaries
    calMap[start]++;
    calMap[end]--;

    // The maximum number of concurrent events allowed is 2 (no triple booking)
    int nRooms = 2;

    // Check if this new state is valid
    if (canAdd(nRooms)) {
      return true;
    }
    
    // If not valid, revert the changes and return false
    calMap[start]--;
    calMap[end]++;
    
    return false;
  }
};

void bookIt (class MyCalendarMap &cal, int start, int end) {
  bool ret;
  ret = cal.book(start, end);
  cout << "Start: " << start << " End: " << end << " Booked:" << ret << endl;
}

void test_map () {
  class MyCalendarMap my;
  bool ret;
  
  bookIt(my, 10, 20); 
  bookIt(my, 50, 60);
  bookIt(my, 10, 40); 
  bookIt(my, 5, 15); 
  bookIt(my, 5, 10);
  bookIt(my, 25, 55); 
}

int main () {

  test_map();

  return 0;
}
