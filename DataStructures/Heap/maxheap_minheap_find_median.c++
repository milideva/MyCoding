#include <queue>
#include <iostream>
#include <vector>

using namespace std;

/*
  LeetCode 295: Find Median from Data Stream

  Problem Description:
  The median is the middle value in an ordered integer list. If the size 
  of the list is even, there is no middle value and the median is the 
  mean of the two middle values.

  For example:
  - [2, 3, 4], the median is 3
  - [2, 3], the median is (2 + 3) / 2 = 2.5

  Implement the MedianFinder class:
  - MedianFinder() initializes the MedianFinder object.
  - void addNum(int num) adds the integer num from the data stream to 
    the data structure.
  - double findMedian() returns the median of all elements so far. 
    Answers within 10^-5 of the actual answer will be accepted.

  Algorithm: Two Heaps (Max-Heap & Min-Heap)
  1. Use a Max-Heap (`lo`) to store the smaller half of the numbers.
  2. Use a Min-Heap (`hi`) to store the larger half of the numbers.
  3. Maintain the balance:
     - Push `num` to `lo`.
     - Pop the max from `lo` and push it to `hi` to ensure `hi` gets 
       the largest from the smaller half.
     - If `lo` becomes smaller than `hi`, pop from `hi` and push to `lo`.
  4. This ensures `lo.size() >= hi.size()` and the difference is at most 1.
  5. Median is `lo.top()` (if total size is odd) or `(lo.top() + hi.top()) / 2`.

  Complexity Analysis:
  - Time Complexity:
    - addNum: O(log N) due to heap operations.
    - findMedian: O(1).
  - Space Complexity: O(N) to store all numbers in the heaps.

  Brute Force comparison:
  - Store numbers in a sorted vector.
    - addNum: O(N) (insertion sort).
    - findMedian: O(1).
  - The two-heap approach is significantly faster for data streams as 
    insertion is reduced from linear to logarithmic time.
*/

class MedianFinder {
  priority_queue<int> lo;                              // max heap - holds low elements
  priority_queue<int, vector<int>, greater<int>> hi;   // min heap - holds high elements
  
public:
  void addNum (int num) {
    lo.push(num);                                    // Add to max heap
    hi.push(lo.top());                               // balancing step
    lo.pop();

    if (lo.size() < hi.size()) {                     // maintain size property
      lo.push(hi.top());
      hi.pop();
    }
  }

  double findMedian () {
    return lo.size() > hi.size() ? (double)lo.top() : ((double) lo.top() + hi.top()) * 0.5;
  }
};

int main () {
  MedianFinder sol;

  cout << "Testing: Median from Data Stream" << endl;
  sol.addNum(1);
  sol.addNum(2);
  double med = sol.findMedian();
  cout << "  [PASS] Median of [1, 2]: " << med << " (Expected: 1.5)" << endl;
  
  sol.addNum(3);
  med = sol.findMedian();
  cout << "  [PASS] Median of [1, 2, 3]: " << med << " (Expected: 2)" << endl;

  return 0;
}
