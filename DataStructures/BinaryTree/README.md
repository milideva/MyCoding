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

### D. Tree Reconstruction & Serialization

#### 1. Reconstruction WITHOUT Markers (Standard Traversals)
To uniquely reconstruct a general binary tree without markers or null-node placeholders, we need **two traversals**, where at least one provides structural anchoring:
*   **In-order + Pre-order or Post-order:** $\rightarrow$ **Unique Reconstruction**. (Pre-order or Post-order identifies the root node, and In-order uses that root node to split the sequence into left and right subtrees).
*   **Pre-order + Post-order:** $\rightarrow$ **Ambiguous / Multiple Trees**. (Only works uniquely if the binary tree is **full**, where every node has either $0$ or $2$ children).

#### 2. Reconstruction WITH Markers (Serialization)
If the traversal is augmented with explicit markers/placeholders (`#` or `null`) representing empty (`nullptr`) child positions:
*   **Pre-order + Markers:** $\rightarrow$ **Unique Reconstruction**. (Recursively deserialize from left to right, where the first node is always the root).
*   **Post-order + Markers:** $\rightarrow$ **Unique Reconstruction**. (Recursively deserialize from right to left, processing in the order of `Root -> Right -> Left`).
*   **In-order + Markers:** $\rightarrow$ **Ambiguous (Cannot uniquely reconstruct)**.

##### Mathematical Proof by Counter-Example for In-order + Markers:
Consider the following two structurally distinct binary trees:

**Tree 1 (Root is 2, Left is 1, Right is Null):**
```text
    2
   /
  1
```
*   In-order traversal with markers: `[#, 1, #, 2, #]`

**Tree 2 (Root is 1, Left is Null, Right is 2):**
```text
  1
   \
    2
```
*   In-order traversal with markers: `[#, 1, #, 2, #]`

Since both structurally distinct trees produce the *exact same* serialized sequence `[#, 1, #, 2, #]`, unique reconstruction from an in-order traversal with markers is **mathematically impossible**.

### E. Monotonic Stack
Optimized $O(N)$ approach for building a Maximum Binary Tree (LeetCode 654).

---

## 5. Implementation Standards in this Repo

1.  **MARKER = -1**: Used in level-order construction to represent `NULL` nodes.
2.  **Explicit Memory Management**: Every `createTree` has a corresponding `destroyTree`.
3.  **Search Prefixes**: Filenames are prefixed with `dfs_` or `bfs_` to indicate the primary algorithm used (e.g., `dfs_invert_binary_tree.c++`).

4.  **Complexity Headers**: Every source file contains a detailed Time/Space analysis and comparison with brute-force approaches.

---

## 6. References
*   Stanford Computer Science Library: [Binary Trees](http://cslibrary.stanford.edu/110/BinaryTrees.html)
*   GeeksforGeeks: [Serialize and Deserialize Binary Tree](https://www.geeksforgeeks.org/serialize-deserialize-binary-tree/)
*   LeetCode: [Tree Explore Card](https://leetcode.com/explore/learn/card/data-structure-tree/)
