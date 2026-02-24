/*

Implement a MyCalendarThree class to store your events. A new event can always be added.

Your class will have one method, book(int start, int end). Formally, this
represents a booking on the half open interval [start, end), the range of real
numbers x such that start <= x < end.

A K-booking happens when K events have some non-empty intersection (ie., there
is some time that is common to all K events.)

For each call to the method MyCalendar.book, return an integer K representing
the largest integer such that there exists a K-booking in the calendar. Your
class will be called like this: MyCalendarThree cal = new MyCalendarThree();
MyCalendarThree.book(start, end)

Example 1:

MyCalendarThree();
MyCalendarThree.book(10, 20); // returns 1
MyCalendarThree.book(50, 60); // returns 1
MyCalendarThree.book(10, 40); // returns 2
MyCalendarThree.book(5, 15); // returns 3
MyCalendarThree.book(5, 10); // returns 3
MyCalendarThree.book(25, 55); // returns 3
Explanation: 
The first two events can be booked and are disjoint, so the maximum K-booking is a 1-booking.
The third event [10, 40) intersects the first event, and the maximum K-booking is a 2-booking.
The remaining events cause the maximum K-booking to be only a 3-booking.
Note that the last event locally causes a 2-booking, but the answer is still 3 because
eg. [10, 20), [10, 40), and [5, 15) are still triple booked.

Note:

    The number of calls to MyCalendarThree.book per test case will be at most 400.
    In calls to MyCalendarThree.book(start, end), start and end are integers in the range [0, 10^9].

*/

#include <map>
#include <iostream>
using namespace std;

/*
 * Approach: Boundary Counting (Sweep-Line Algorithm)
 *
 * This problem asks for the maximum number of concurrent events (the "K-booking")
 * at any point in time after a new event is added. This is a classic application
 * of the sweep-line algorithm, and is very similar to LeetCode problem 253,
 * "Meeting Rooms II".
 *
 * How it works:
 * 1. We use an ordered map (`calMap`) to store the "boundary points" of all events.
 *    The map's key is the time, and the value is the change in the number of
 *    active events at that time.
 *
 * 2. For each new event `book(start, end)`, we do two things:
 *    - `calMap[start]++`: Increment the count at the start time, signifying a new event has begun.
 *    - `calMap[end]--`: Decrement the count at the end time, signifying an event has ended.
 *
 * 3. After adding the new event's boundaries, we "sweep" through the timeline by
 *    iterating through our ordered map. We keep a running count of active events (`count`).
 *    As we iterate from one time point to the next, `count` will increase or decrease.
 *    The maximum value that `count` reaches at any point is our answer, K.
 *
 * Example: book(10, 20), then book(10, 40)
 * - After book(10, 20): calMap = { 10: 1, 20: -1 }
 *   - Sweep:
 *     - At t=10, count becomes 1. maxK = 1.
 *     - At t=20, count becomes 0. maxK = 1.
 *   - Return 1.
 *
 * - After book(10, 40): calMap = { 10: 2, 20: -1, 40: -1 }
 *   - Sweep:
 *     - At t=10, count becomes 2. maxK = 2.
 *     - At t=20, count becomes 1. maxK = 2.
 *     - At t=40, count becomes 0. maxK = 2.
 *   - Return 2.
 *
 * Time Complexity: O(N) per `book()` call.
 * - The map insertions/updates (`calMap[start]++`, `calMap[end]--`) each take O(log N) time.
 * - The subsequent sweep (`calculateMaxK`) iterates through the entire map, which can
 *   have up to 2*N entries. This takes O(N) time.
 * - The O(N) sweep dominates, so the overall complexity is O(N) per call.
 *   (Note: The problem constraints state N <= 400, so an N^2 solution might also pass, but this is much better).
 *
 * Space Complexity: O(N)
 * - The map stores up to two boundary points for each of the N events.
 */
class MyCalendarThree {
    // map key: time point, value: change in active events (+1 for start, -1 for end)
    map <int, int> calMap;
    
    /*
     * This function executes the "sweep-line" part of the algorithm.
     * It iterates through the boundary points in chronological order, calculating
     * the number of active events at each step and returning the maximum
     * number found.
     */
    int calculateMaxK () {
        int activeEvents = 0; // Represents the number of concurrent events at the current time
        int maxActive = 0;    // The maximum number of concurrent events found so far
        
        // Iterate through the map, which is sorted by time
        for (auto const& [time, change] : calMap) {
            // Update the count of active events
            activeEvents += change;
            // Update the maximum if the current count is greater
            maxActive = max(maxActive, activeEvents);
        }
        return maxActive;
    }
public:
    MyCalendarThree() {
    }
   
    int book(int start, int end) {
        // Mark the start of a new event
        calMap[start]++;
        // Mark the end of an event
        calMap[end]--;

        // The K-booking is the maximum number of overlapping events found
        // by sweeping across the entire timeline.
        return calculateMaxK();
    }
};

void bookIt (class MyCalendarThree &cal, int start, int end) {
  int ret;
  ret = cal.book(start, end);
  cout << "Start: " << start << " End: " << end << " maxK:" << ret << endl;
}

void test_cal () {
  class MyCalendarThree my;
   
  bookIt(my, 10, 20); 
  bookIt(my, 50, 60);
  bookIt(my, 10, 40); 
  bookIt(my, 5, 15); 
  bookIt(my, 5, 10);
  bookIt(my, 25, 55); 
}

int main () {

  test_cal();

  return 0;
}
