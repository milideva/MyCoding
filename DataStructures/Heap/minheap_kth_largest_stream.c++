#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
  LeetCode 703: Kth Largest Element in a Stream

  Problem Description:
  Design a class to find the kth largest element in a stream. Note that 
  it is the kth largest element in the sorted order, not the kth 
  distinct element.

  Implement KthLargest class:
  - KthLargest(int k, int[] nums) Initializes the object with the 
    integer k and the stream of integers nums.
  - int add(int val) Appends the integer val to the stream and returns 
    the kth largest element.

  Algorithm: Min-Heap of size K
  1. Use a Min-Heap to store the current top `k` largest elements.
  2. The smallest of these `k` elements (the root of the min-heap) 
     is the `k`-th largest element overall.
  3. For each incoming value in the stream:
     - Push the value into the min-heap.
     - If the heap size exceeds `k`, pop the smallest element.
     - *Optimization Note:* If the heap is already full (size is k), we could optimize 
       and skip pushing elements entirely if the incoming value is <= minHeap.top(). 
       This avoids redundant O(log K) heap operations.
  4. This ensures that the heap always contains the `k` largest values 
     seen so far, and `heap.top()` is exactly the `k`-th largest.

  Complexity Analysis:
  - Time Complexity:
    - Constructor: O(N log K) where N is the initial size of nums.
    - add: O(log K).
  - Space Complexity: O(K) to store the `k` largest elements in the heap.

  Comparison:
  - Max-Heap: To find the k-th largest using a Max-Heap of size N, 
    you would need to pop `k` times and then push those back. 
    This is O(N + K log N) for each query, which is much slower 
    than O(log K) for a stream.
  - Sorting: Sorting the whole stream on every add would be O(N log N), 
    which is impractical.
*/

class KthLargest {
    int k;
    priority_queue<int, vector<int>, greater<int>> minHeap;
public:
    KthLargest(int k, vector<int>& nums) : k(k) {
        for (int n : nums) {
            add(n);
        }
    }
    
    // Adds a new value to the stream and returns the kth largest.
    // Optimization Note: To keep the code extremely simple and highly readable,
    // we push every element and pop if needed. In a production environment, we could
    // optimize this to O(1) time when val <= minHeap.top() by checking:
    //   if (minHeap.size() < k) { minHeap.push(val); }
    //   else if (val > minHeap.top()) { minHeap.pop(); minHeap.push(val); }
    int add(int val) {
        minHeap.push(val);
        if (minHeap.size() > k) {
            minHeap.pop();
        }
        return minHeap.top();
    }
};

void test(const string& label, int k, vector<int> nums, vector<int> stream, vector<int> expected) {
    cout << "Testing: " << label << endl;
    KthLargest sol(k, nums);
    for (int i = 0; i < stream.size(); ++i) {
        int result = sol.add(stream[i]);
        if (result == expected[i]) {
            cout << "  [PASS] Added " << stream[i] << " -> Kth: " << result << endl;
        } else {
            cout << "  [FAIL] Added " << stream[i] << " -> Result: " << result << " (Expected: " << expected[i] << ")" << endl;
        }
    }
}

int main() {
    test("Example 1", 3, {4, 5, 8, 2}, {3, 5, 10, 9, 4}, {4, 5, 5, 8, 8});
    return 0;
}
