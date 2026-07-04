# Stacks: Last-In, First-Out (LIFO)

A Stack is a linear data structure that follows the **LIFO** principle. The last element added is the first one to be removed.

## 🏗️ Implementations

- **Array-based**: Faster access but fixed size (unless using dynamic arrays).
- **Linked List-based**: Dynamic size but slightly higher memory overhead per element.

---

## 🚀 Key Patterns

### 1. Expression Evaluation
Stacks are used to convert and evaluate infix, prefix, and postfix expressions.
- **Problem examples**: `stack_basic_calculator`.

### 2. Monotonic Stack
A stack that maintains elements in a specific order (increasing or decreasing). Useful for finding the "next greater" or "next smaller" element in $O(N)$ time.
- **Problem examples**: `stack_remove_all_adjacent_duplicates_in_string_ii`.

### 3. Parentheses Matching
Using a stack to ensure every opening bracket has a corresponding closing bracket in the correct order.
- **Problem examples**: `stack_valid_parentheses`.

### 4. Recursion Simulation
Any recursive algorithm can be implemented iteratively using an explicit stack.

---

## 📈 Complexity Analysis

| Operation | Time Complexity | Space Complexity |
| :--- | :--- | :--- |
| **Push** | $O(1)$ | $O(1)$ |
| **Pop** | $O(1)$ | $O(1)$ |
| **Peek** | $O(1)$ | $O(1)$ |
| **Search** | $O(N)$ | $O(1)$ |

---

## 🔗 Useful Resources
- [GeeksforGeeks: Stack Data Structure](https://www.geeksforgeeks.org/stack-data-structure/)
- [Visualgo: Stack Visualization](https://visualgo.net/en/list?subset=Stack)
- [LeetCode Explore: Queue & Stack](https://leetcode.com/explore/learn/card/queue-stack/)
