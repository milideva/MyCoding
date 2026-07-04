# Arrays: Algorithms and Techniques

Arrays are the most fundamental data structure, representing a contiguous block of memory. This directory covers essential array-based patterns and algorithms.

## 🚀 Key Patterns

### 1. Two Pointers
The two-pointer technique is used to search for pairs or triplets in a sorted array, or to manipulate elements in-place.
- **Opposite ends**: `left` starts at 0, `right` at `n-1`. Used in `two_sum` (sorted), `valid_palindrome`.
- **Fast & Slow**: One pointer moves faster than the other. Used for cycle detection or finding the middle.
- **Problem examples**: `twopointers_container_with_most_water`, `twopointers_three_sum`.

### 2. Sliding Window
Used to perform operations on a specific window (subarray) of the data. The window can be of fixed or variable size.
- **Fixed Size**: Maintain a sum or property of the first $K$ elements, then slide by adding the next and removing the first.
- **Variable Size**: Expand the window until a condition is met, then contract from the left.
- **Problem examples**: `slidingwindow_min_size_subarray_sum`, `slidingwindow_maximum_points_you_can_obtain_from_cards`.

### 3. Binary Search
An efficient $O(\log N)$ algorithm for finding an element in a **sorted** array by repeatedly dividing the search interval in half.
- **Variations**: Searching in rotated sorted arrays, finding the first/last occurrence.
- **Problem examples**: `binarysearch_search_rotated_sorted_array`, `binarysearch_first_bad_version`.

### 4. Prefix Sum
A pre-computation technique where `prefix[i]` stores the sum of elements from `0` to `i`. This allows $O(1)$ range sum queries.
- **Problem examples**: `prefixsum_hashmap_subarray_sum_equals_k`, `prefixsum_product_of_array_except_self`.

### 5. Sweep Line
Involves sorting intervals (like start and end times) and "sweeping" across them to solve intersection or overlap problems.
- **Problem examples**: `sweepline_meeting_rooms_ii`, `sweepline_merge_intervals`.

---

## 📈 Complexity Analysis

| Operation | Time Complexity | Space Complexity |
| :--- | :--- | :--- |
| **Access** | $O(1)$ | $O(1)$ |
| **Search (Unsorted)** | $O(N)$ | $O(1)$ |
| **Search (Sorted)** | $O(\log N)$ | $O(1)$ |
| **Insertion/Deletion** | $O(N)$ (due to shifting) | $O(1)$ |

---

## 🔗 Useful Resources
- [LeetCode Explore: Arrays 101](https://leetcode.com/explore/learn/card/fun-with-arrays/)
- [GeeksforGeeks: Array Data Structure](https://www.geeksforgeeks.org/array-data-structure/)
- [Visualgo: Array Visualization](https://visualgo.net/en/list)
