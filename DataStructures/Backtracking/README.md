# Backtracking: Systematic Exploration

Backtracking is an algorithmic technique for solving problems recursively by trying to build a solution incrementally, one piece at a time, removing those solutions that fail to satisfy the constraints of the problem at any point in time.

## 🗝️ The Backtracking Template

A typical backtracking algorithm follows this structure:

```text
void backtrack(candidate) {
    if (goal reached) {
        add candidate to results;
        return;
    }

    for (next_option in possible_options) {
        if (is_valid(next_option)) {
            make_move(next_option);   // Choose
            backtrack(next_candidate); // Explore
            undo_move(next_option);   // Backtrack
        }
    }
}
```

---

## 🚀 Key Patterns

### 1. Permutations and Combinations
Generating all possible arrangements or subsets of a set.
- **Problem examples**: `backtracking_permutations_string`, `backtracking_combinations`.

### 2. Constraint Satisfaction
Solving puzzles where each move must satisfy specific rules.
- **Problem examples**: `backtracking_solve_sudoku`, `backtracking_knight_tour`.

### 3. Pruning
The process of cutting off branches in the search tree that cannot possibly lead to a valid solution. This is what makes backtracking more efficient than pure brute force.

---

## 📈 Complexity Analysis

| Operation | Typical Complexity | Space Complexity |
| :--- | :--- | :--- |
| **Permutations** | $O(N!)$ | $O(N)$ |
| **Subsets/Combinations** | $O(2^N)$ | $O(N)$ |
| **N-Queens/Sudoku** | $O(K^N)$ | $O(N)$ |

---

## 🔗 Useful Resources
- [GeeksforGeeks: Backtracking Algorithms](https://www.geeksforgeeks.org/backtracking-algorithms/)
- [LeetCode Explore: Recursion II (Backtracking)](https://leetcode.com/explore/learn/card/recursion-ii/)
- [Backtracking Visualization](https://www.cs.usfca.edu/~galles/visualization/RecursiveBacktrack.html)
