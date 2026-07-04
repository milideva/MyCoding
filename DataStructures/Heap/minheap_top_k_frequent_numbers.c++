#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

/*
  LeetCode 347: Top K Frequent Elements

  Problem Description:
  Given an integer array `nums` and an integer `k`, return the `k` 
  most frequent elements. You may return the answer in any order.

  Algorithm: Min-Heap of size K
  1. Count the frequency of each number using a hash map (`unordered_map`).
  2. Use a Min-Heap to store pairs of `(frequency, number)`.
  3. Iterate through the hash map:
     - Push the current `(freq, num)` pair into the min-heap.
     - If the heap size exceeds `k`, pop the smallest frequency element.
  4. After processing all elements, the heap contains the `k` most 
     frequent elements.
  5. The use of a Min-Heap ensures that the "top" of the heap is the 
     smallest among the frequent elements, making it easy to replace 
     when a more frequent element is found.

  Complexity Analysis:
  - Time Complexity: O(N log K)
    Reason: Counting frequencies takes O(N). Iterating through unique 
    elements (up to N) and performing heap operations takes O(N log K).
  - Space Complexity: O(N)
    Reason: To store the frequencies in a hash map and `k` elements in 
    the heap.

  Alternative Approaches:
  - Bucket Sort:
    - Logic: Use an array where the index represents frequency and 
      the value is a list of numbers with that frequency.
    - Time Complexity: O(N), Space Complexity: O(N).
    - Comparison: Bucket sort is theoretically faster but uses more 
      memory if frequencies are sparse.
  - QuickSelect:
    - Average Time: O(N).

  Brute Force comparison:
  - Sort the unique elements by frequency.
  - Time: O(N log N).
  - Comparison: The Min-Heap approach is better when `k` is small.
*/

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        if (k == 0) return {};
        
        unordered_map<int, int> counts;
        for (int n : nums) counts[n]++;

        // Min-Heap to store top k elements
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

        for (auto const& [num, freq] : counts) {
            minHeap.push({freq, num});
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }

        vector<int> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        return result;
    }
};

void test(const string& label, vector<int> nums, int k, vector<int> expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    vector<int> result = sol.topKFrequent(nums, k);
    sort(result.begin(), result.end());
    sort(expected.begin(), expected.end());

    if (result == expected) {
        cout << "  [PASS]" << endl;
    } else {
        cout << "  [FAIL] Result: ";
        for (int n : result) cout << n << " ";
        cout << endl;
    }
}

int main() {
    test("Example 1", {1, 1, 1, 2, 2, 3}, 2, {1, 2});
    test("Example 2", {1}, 1, {1});
    test("Multiple items same freq", {1, 2, 3}, 2, {2, 3}); 
    return 0;
}
