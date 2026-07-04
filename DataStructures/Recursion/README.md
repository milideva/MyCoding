# Recursion: Function Self-Reference

Recursion is a process in which a function calls itself as a subroutine. This allows the function to be repeated several times, as it solves the problem by breaking it into smaller versions of itself.

## 🏗️ The Anatomy of Recursion

Every recursive function must have:
1.  **Base Case**: The condition under which the function stops calling itself. Without this, recursion would be infinite.
2.  **Recursive Step**: The part where the function calls itself with a modified (smaller) argument.

---

## 🚀 Key Patterns

### 1. Mathematical Induction
Solving problems like factorials, power functions, or Fibonacci numbers.
- **Problem examples**: `math_pow_x_n`, `dp_factorial`.

### 2. Divide and Conquer
Breaking a problem into two or more subproblems of the same or related type, until these become simple enough to be solved directly.
- **Examples**: Merge Sort, Quick Sort, Binary Search.

### 3. Tree and Graph Traversals
Recursion is the natural way to traverse hierarchical structures like trees.
- **Examples**: In-order, Pre-order, and Post-order traversals.

---

## ⚠️ Common Pitfalls

- **Stack Overflow**: Caused by too many nested calls (recursion depth too high).
- **Redundant Calculations**: Solved by using **Memoization** (see Dynamic Programming).
- **Missing Base Case**: Leads to infinite recursion.

---

## ⚖️ Recursion vs. Iteration

| Feature | Recursion | Iteration |
| :--- | :--- | :--- |
| **Logic** | Solves subproblems. | Uses loops. |
| **Space** | Uses Stack space ($O(H)$). | Uses $O(1)$ auxiliary space. |
| **Readability** | Often more elegant and shorter. | Can be more verbose. |

---

## 🔗 Useful Resources
- [GeeksforGeeks: Recursion](https://www.geeksforgeeks.org/recursion/)
- [LeetCode Explore: Recursion I](https://leetcode.com/explore/learn/card/recursion-i/)
- [Visualizing Recursion](https://visualgo.net/en/recursion)
