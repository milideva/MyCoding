# Heaps: Priority Queues and Selection

A Heap is a specialized tree-based data structure that satisfies the **heap property**:
- **Min-Heap**: The value of each node is greater than or equal to the value of its parent (root is smallest).
- **Max-Heap**: The value of each node is less than or equal to the value of its parent (root is largest).

## 🏗️ Implementation Details

Heaps are usually implemented using an **array** because they are complete binary trees.
- For index $i$:
  - `parent(i) = (i-1)/2`
  - `left(i) = 2*i + 1`
  - `right(i) = 2*i + 2`

---

## 🚀 Key Patterns

### 1. K-Size Heap (Top K Elements)
To find the $K$ smallest elements, use a **Max-Heap** of size $K$. To find the $K$ largest, use a **Min-Heap**.
- **Problem examples**: `maxheap_k_closest_points`, `minheap_top_k_frequent_numbers`.

### 2. Two Heaps (Running Median)
Maintain a max-heap for the smaller half and a min-heap for the larger half of the numbers. The median is the root of the larger heap (or average of roots).
- **Problem examples**: `maxheap_minheap_find_median`.

### 3. Merge K Sorted Lists
Use a min-heap to keep track of the smallest element across $K$ lists.
- **Problem examples**: `minheap_merge_k_sorted_lists`.

---

## 📈 Complexity Analysis

| Operation | Time Complexity | Space Complexity |
| :--- | :--- | :--- |
| **Get Max/Min** | $O(1)$ | $O(1)$ |
| **Insert** | $O(\log N)$ | $O(1)$ |
| **Delete (Pop)** | $O(\log N)$ | $O(1)$ |
| **Heapify** | $O(\log N)$ | $O(1)$ |
| **Build Heap** | $O(N)$ | $O(1)$ |

---

## 🔗 Useful Resources
- [GeeksforGeeks: Binary Heap](https://www.geeksforgeeks.org/binary-heap/)
- [Visualgo: Heap Visualization](https://visualgo.net/en/heap)
- [LeetCode Explore: Heap](https://leetcode.com/explore/learn/card/heap/)
