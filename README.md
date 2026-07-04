# MyCoding: Data Structures, Algorithms, and System Design

A comprehensive repository of standard data structure implementations, LeetCode problem solutions, system design notes, and interview preparation materials.

## 🚀 Standardization Effort
The repository has undergone a significant standardization process to ensure high-quality code and documentation. Key improvements include:
- **Strategy-Based Naming**: Files are prefixed with their primary algorithmic strategy (e.g., `bfs_`, `dfs_`, `dp_`, `twopointers_`).
- **Complexity Analysis**: Every implementation includes detailed Time and Space complexity headers.
- **Verification**: All source files have been compiled and executed to verify behavioral correctness.
- **Modern C++**: Transitions from legacy C to modern C++ (C++20 standards) where appropriate for better readability and performance.

---

## 📂 Repository Structure

### 🏗️ Data Structures & Algorithms
The core of the repository is organized by data structure type. Each directory contains a `README.md` explaining the fundamental concepts and listing key implementations.

| Directory | Description |
| :--- | :--- |
| [Arrays](./DataStructures/Arrays) | Sorting, Searching (Binary Search), Two Pointers, Sliding Window, Sweep Line. |
| [LinkedList](./DataStructures/LinkedList) | Singly, Doubly, and Circular linked list operations. |
| [BinaryTree](./DataStructures/BinaryTree) | Traversals (BFS/DFS), Reconstruction, Path-based problems. |
| [BST](./DataStructures/BST) | Binary Search Tree properties, validation, and balancing. |
| [Graph](./DataStructures/Graph) | BFS, DFS, Topological Sort, Union-Find, Cycle Detection. |
| [Greedy](./DataStructures/Greedy) | Huffman coding, standard denomination coin change. |
| [HashTable](./DataStructures/HashTable) | Hashing techniques, LRU/LFU cache designs. |
| [Heap](./DataStructures/Heap) | Priority Queue implementations and applications. |
| [DynamicProgramming](./DataStructures/DynamicProgramming) | Classic DP problems (Knapsack, LCS, etc.). |
| [Backtracking](./DataStructures/Backtracking) | Recursive search and constraint satisfaction. |
| [Trie](./DataStructures/Trie) | Prefix tree operations and word matching. |
| [Recursion](./DataStructures/Recursion) | Fundamental recursive patterns. |
| [BitMagic](./DataStructures/BitMagic) | Low-level bit manipulation tricks. |
| [General](./DataStructures/General) | Math, Geometry, and Design-based problems. |

### 🌐 System Design & Architecture
Notes on building scalable distributed systems.
- [SystemDesign](./SystemDesign): Cache strategies (Redis vs Memcached), Timer designs.
- [ApiDesign](./ApiDesign): RESTful principles and best practices.
- [LockSemaphoreRCU](./LockSemaphoreRCU): Concurrency primitives, distributed locks, and barriers.

### 📝 Technical Notes
- [Notes](./Notes): Brief summaries on Kubernetes, CAP Theorem, Big Data, Microservices, and OS concepts.
- [Memory](./Memory): Notes on memory management and architecture.

### 🤝 Interview Preparation
- [Interviews](./Interviews): Study topics, negotiation tips, and practice resources.

---

## 🛠️ Usage
To compile and run any C++ implementation:
```bash
g++ -std=c++20 <filename>.c++ -o output
./output
```

For C implementations:
```bash
gcc <filename>.c -o output
./output
```

---

## 📈 Complexity Cheat Sheet
| Category | Search | Insert | Delete |
| :--- | :--- | :--- | :--- |
| **Array (Sorted)** | $O(\log N)$ | $O(N)$ | $O(N)$ |
| **LinkedList** | $O(N)$ | $O(1)$ | $O(1)$ |
| **BST (Balanced)** | $O(\log N)$ | $O(\log N)$ | $O(\log N)$ |
| **Hash Table** | $O(1)$ | $O(1)$ | $O(1)$ |
| **Heap** | $O(1)$ (peek) | $O(\log N)$ | $O(\log N)$ (pop) |
