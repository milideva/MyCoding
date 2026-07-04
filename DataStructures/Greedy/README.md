# Greedy Algorithms: Locally Optimal Choices

A greedy algorithm builds up a solution piece by piece, always choosing the next piece that offers the most obvious and immediate benefit.

## 🗝️ Core Properties

For a greedy algorithm to be correct, the problem must exhibit two properties:
1.  **Greedy Choice Property**: A global optimum can be arrived at by selecting a local optimum.
2.  **Optimal Substructure**: An optimal solution to the problem contains optimal solutions to its subproblems.

---

## 🚀 Common Examples

- **Fractional Knapsack**: Items can be broken. Always pick the item with the highest value-to-weight ratio.
- **Huffman Coding**: Used for lossless data compression. Always merge the two least frequent symbols.
  - **Problem example**: `greedy_huffman_coding`.
- **Dijkstra's Algorithm**: Finding the shortest path. Always pick the unvisited node with the smallest distance.
- **Minimum Spanning Tree**: Prim's and Kruskal's algorithms.
- **Standard Denomination Coin Change**: In systems like the US dollar, greedy works. For arbitrary systems, it fails (requires DP).
  - **Problem example**: `greedy_coin_change`.

---

## ⚖️ Greedy vs. Dynamic Programming

| Feature | Greedy | Dynamic Programming |
| :--- | :--- | :--- |
| **Strategy** | Local optimum at each step. | Global optimum by considering all subproblems. |
| **Correctness** | Must be proven. | Guaranteed if subproblems are defined correctly. |
| **Efficiency** | Usually faster and simpler. | More complex and potentially slower. |

---

## 🔗 Useful Resources
- [GeeksforGeeks: Greedy Algorithms](https://www.geeksforgeeks.org/greedy-algorithms/)
- [Brilliant: Greedy Algorithms](https://brilliant.org/wiki/greedy-algorithm/)
- [Topcoder: Greedy Algorithms Guide](https://www.topcoder.com/thrive/articles/Greedy%20Algorithms)
