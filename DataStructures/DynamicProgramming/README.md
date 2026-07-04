# Dynamic Programming: Optimization through Subproblems

Dynamic Programming (DP) is a method for solving complex problems by breaking them down into simpler subproblems. It is applicable when the problem has **Overlapping Subproblems** and **Optimal Substructure**.

## 🏗️ Two Approaches

### 1. Top-Down (Memoization)
Solve the problem recursively and store the results of subproblems in a hash map or array to avoid redundant calculations.
- **Pros**: Intuitive, only solves necessary subproblems.
- **Cons**: Recursion overhead, risk of stack overflow.

### 2. Bottom-Up (Tabulation)
Solve the problem iteratively by filling up a table (usually an array or matrix) from the smallest subproblems to the largest.
- **Pros**: No recursion overhead, often more space-efficient (via space optimization).
- **Cons**: Less intuitive, solves all subproblems.

---

## 🚀 Key Patterns

### 1. 0/1 Knapsack
Choosing items with weights and values to maximize total value without exceeding capacity.
- **Variants**: Unbounded Knapsack, Partition Sum.

### 2. Fibonacci Sequence
The simplest DP example.
- **Problem examples**: `dp_fibonacci`, `dp_climbing_stairs_variation`.

### 3. Longest Common Subsequence (LCS)
Finding the longest sequence of characters that appear in the same relative order in two strings.

### 4. Paths in a Grid
Finding the number of ways or the minimum/maximum cost to reach a cell in a matrix.
- **Problem examples**: `dp_unique_paths`, `dp_minimum_path_sum`.

---

## 📈 Complexity Analysis

| Approach | Time Complexity | Space Complexity |
| :--- | :--- | :--- |
| **Naive Recursion** | Exponential ($O(2^N)$) | $O(N)$ (stack) |
| **DP (Memo/Tab)** | Polynomial ($O(N \cdot M)$) | $O(N \cdot M)$ or $O(M)$ |

---

## 🔗 Useful Resources
- [GeeksforGeeks: Dynamic Programming](https://www.geeksforgeeks.org/dynamic-programming/)
- [LeetCode Explore: Dynamic Programming](https://leetcode.com/explore/learn/card/dynamic-programming/)
- [MIT 6.006: Dynamic Programming Lectures](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-19-dynamic-programming-i-fibonacci-shortest-paths/)
