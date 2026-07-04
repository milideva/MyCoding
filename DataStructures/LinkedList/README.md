# Linked Lists: Concepts and Operations

Linked lists are linear data structures where elements (nodes) are not stored in contiguous memory. Each node contains data and a pointer to the next node.

## 🏗️ Types of Linked Lists

1.  **Singly Linked List**: Each node points to the next node.
2.  **Doubly Linked List**: Each node points to both the next and the previous node.
3.  **Circular Linked List**: The last node points back to the first node.

---

## 🚀 Key Techniques

### 1. Dummy Head Pattern
Using a dummy node at the start of the list simplifies code for insertion and deletion, especially when the operation involves the head of the list.
- **Problem examples**: `iterative_partition_list`, `iterative_delete_duplicates_sorted_list`.

### 2. Slow and Fast Pointers (Runner Technique)
- **Cycle Detection**: If a fast pointer (moving 2 steps) meets a slow pointer (moving 1 step), a cycle exists (Floyd's Cycle-Finding Algorithm).
- **Finding Middle**: When the fast pointer reaches the end, the slow pointer is at the middle.

### 3. In-place Reversal
Reversing pointers without using extra space.
- **Pattern**: `next = curr->next; curr->next = prev; prev = curr; curr = next;`
- **Problem examples**: `iterative_reverse_linked_list_ii`.

---

## ⚖️ Array vs. Linked List

| Feature | Array | Linked List |
| :--- | :--- | :--- |
| **Memory** | Contiguous | Non-contiguous (Heap) |
| **Access** | $O(1)$ | $O(N)$ |
| **Insertion/Deletion** | $O(N)$ (due to shifting) | $O(1)$ (if node is known) |
| **Cache Locality** | Excellent | Poor |

---

## 📈 Complexity Analysis

| Operation | Average/Worst Case | Space Complexity |
| :--- | :--- | :--- |
| **Search** | $O(N)$ | $O(1)$ |
| **Insertion** | $O(1)$ | $O(1)$ |
| **Deletion** | $O(1)$ | $O(1)$ |

---

## 🔗 Useful Resources
- [LeetCode Explore: Linked List](https://leetcode.com/explore/learn/card/linked-list/)
- [GeeksforGeeks: Linked List Data Structure](https://www.geeksforgeeks.org/data-structures/linked-list/)
