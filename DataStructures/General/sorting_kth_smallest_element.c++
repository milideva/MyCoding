/**
 * Problem: Kth Smallest Element
 * Given an array and a number k where k is smaller than the size of the array, 
 * find the k'th smallest element in the given array.
 * 
 * Strategy 1: Sorting
 * - Time: O(N log N)
 * - Space: O(1)
 * 
 * Strategy 2: Max Heap (Priority Queue of size K)
 * - Build a max-heap of the first k elements.
 * - For the remaining elements, if an element is smaller than the top, 
 *   replace the top and heapify.
 * - Time: O(N log K)
 * - Space: O(K)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/**
 * Strategy 1: Sorting
 */
int kthSmallestSorting(vector<int> arr, int k) {
    sort(arr.begin(), arr.end());
    return arr[k - 1];
}

/**
 * Strategy 2: Max Heap
 */
int kthSmallestMaxHeap(const vector<int>& arr, int k) {
    if (k <= 0 || k > (int)arr.size()) return -1;

    priority_queue<int> maxHeap;
    for (int i = 0; i < (int)arr.size(); i++) {
        if (i < k) {
            maxHeap.push(arr[i]);
        } else if (arr[i] < maxHeap.top()) {
            maxHeap.pop();
            maxHeap.push(arr[i]);
        }
    }
    return maxHeap.top();
}

int main() {
    vector<int> arr = {12, 3, 5, 7, 19};
    int k = 2;

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nk = " << k << endl;

    cout << "Kth smallest (Sorting): " << kthSmallestSorting(arr, k) << endl;
    cout << "Kth smallest (Max Heap): " << kthSmallestMaxHeap(arr, k) << endl;

    return 0;
}
