# Binary Tree: Concepts and Techniques

This directory contains implementations of fundamental binary tree algorithms, ranging from basic traversals to complex reconstruction and path-based problems.

---

## 1. Anatomy of a Binary Tree

A binary tree is a hierarchical data structure where each node has at most two children, referred to as the **left child** and the **right child**.

### ASCII Visualization
```text
        [1]             <-- Root (Level 0)
       /   \
     [2]   [3]          <-- Level 1
    /   \     \
  [4]   [5]   [6]       <-- Level 2 (Leaves: 4, 5, 6)
```

---

## 2. Core Traversals

Traversals are the backbone of all tree algorithms. They are categorized into **Depth-First Search (DFS)** and **Breadth-First Search (BFS)**.

### Depth-First Search (DFS)
| Traversal | Order | Common Use Case |
| :--- | :--- | :--- |
| **Pre-order** | Root, Left, Right | Creating a copy of the tree, Serialization. |
| **In-order** | Left, Root, Right | Sorted sequence in BST, Validating BST property. |
| **Post-order** | Left, Right, Root | Deleting a tree (Bottom-up), Computing height/tilt. |

### Breadth-First Search (BFS)
*   **Level-order:** Visits nodes level-by-level from left to right.
*   **Use Case:** Shortest path, finding the "next" pointer at the same level.

---

## 3. Complexity Analysis

| Operation | Average Case | Worst Case (Skewed) | Space Complexity (Auxiliary) |
| :--- | :--- | :--- | :--- |
| **Traversal (DFS/BFS)** | $O(N)$ | $O(N)$ | $O(H)$ for DFS, $O(W)$ for BFS |
| **Search** | $O(\log N)$ | $O(N)$ | $O(H)$ |
| **Insertion** | $O(\log N)$ | $O(N)$ | $O(H)$ |
| **Deletion** | $O(\log N)$ | $O(N)$ | $O(H)$ |

*   **$N$**: Total number of nodes.
*   **$H$**: Height of the tree ($\log N$ for balanced, $N$ for skewed).
*   **$W$**: Maximum width of the tree (up to $N/2$).

---

## 4. General Techniques & Patterns

### A. Bottom-Up Recursion (Post-order)
Used when a node's result depends on its children's results.
*   **Examples:** Calculating tree height, diameter, or checking if a tree is balanced.
*   **Pattern:** `return 1 + max(dfs(left), dfs(right))`

### B. Top-Down Recursion (Pre-order)
Used when information is passed from the parent to children.
*   **Examples:** Path sum, root-to-leaf paths, updating node values based on ancestors.

### C. Level-Order Processing (BFS)
Uses a queue to process nodes level by level.
*   **Pattern:** Use a `for` loop inside the `while(!queue.empty())` to process exactly one level at a time.

### D. Tree Reconstruction
Rebuilding a tree from traversal sequences (e.g., Inorder + Preorder).
*   **Key Insight:** Preorder/Postorder tells you the **Root**; Inorder tells you the **Boundaries** of left/right subtrees.

### E. Monotonic Stack
Optimized $O(N)$ approach for building a Maximum Binary Tree (LeetCode 654).

---

## 5. Implementation Standards in this Repo

1.  **MARKER = -1**: Used in level-order construction to represent `NULL` nodes.
2.  **Explicit Memory Management**: Every `createTree` has a corresponding `destroyTree`.
3.  **Snake Case**: Filenames follow `snake_case.c++` (e.g., `invert_binary_tree.c++`).
4.  **Complexity Headers**: Every source file contains a detailed Time/Space analysis and comparison with brute-force approaches.

---

## 6. References
*   Stanford CS Library: [Binary Trees](http://cslibrary.stanford.edu/110/BinaryTrees.html)
*   LeetCode: [Tree Explore Card](https://leetcode.com/explore/learn/card/data-structure-tree/)
