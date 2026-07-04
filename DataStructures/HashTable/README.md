# Hash Tables: Efficient Lookup and Caching

A Hash Table (or Hash Map) is a data structure that maps keys to values using a **hash function** to compute an index into an array of buckets or slots.

## 🗝️ Core Concepts

### 1. Hash Function
A function that transforms a key into an integer index. A good hash function:
- Distributes keys uniformly.
- Is efficient to compute.
- Is deterministic (same key always gives same index).

### 2. Collision Handling
When two keys hash to the same index, a collision occurs. Common methods to resolve it:
- **Chaining**: Each bucket stores a linked list (or another structure) of entries.
- **Open Addressing**: Find another empty slot (e.g., Linear Probing, Quadratic Probing, Double Hashing).

---

## 🚀 Advanced Applications

### 1. LRU and LFU Caches
- **LRU (Least Recently Used)**: Evicts the item that hasn't been accessed for the longest time. Typically implemented with a **Hash Map + Doubly Linked List**.
- **LFU (Least Frequently Used)**: Evicts the item with the lowest access frequency.
- **Problem examples**: `cache_lru_implementation`, `cache_lfu_implementation`.

### 2. Consistent Hashing
Used in distributed systems to distribute data across multiple servers while minimizing re-mapping when nodes are added or removed.
- **Problem example**: `hash_consistent_hashing`.

---

## 📈 Complexity Analysis

| Operation | Average Case | Worst Case | Space Complexity |
| :--- | :--- | :--- | :--- |
| **Search** | $O(1)$ | $O(N)$ (rare with good hash) | $O(N)$ |
| **Insertion** | $O(1)$ | $O(N)$ | $O(N)$ |
| **Deletion** | $O(1)$ | $O(N)$ | $O(N)$ |

---

## 🔗 Useful Resources
- [GeeksforGeeks: Hashing Data Structure](https://www.geeksforgeeks.org/hashing-data-structure/)
- [Visualgo: Hash Table Visualization](https://visualgo.net/en/hashtable)
- [Consistent Hashing Guide](https://www.toptal.com/big-data/consistent-hashing)
